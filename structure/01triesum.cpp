const int maxn = 525020;
namespace Trie {
    const int maxh = 25;
    int root[maxn];
    int ch[maxn * maxh][2];
    int w[maxn * maxh];
    int xorval[maxn * maxh];
    int nodecnt = 0;
    void maintain(int o) {
        w[o] = xorval[o] = 0;
        if (ch[o][0]) {
            w[o] += w[ch[o][0]];
            xorval[o] ^= xorval[ch[o][0]] << 1;
        }
        if (ch[o][1]) {
            w[o] += w[ch[o][1]];
            xorval[o] ^= (xorval[ch[o][1]] << 1) | (w[ch[o][1]] & 1);
        }
        w[o] &= 1;
    }
    void insert(int &o, int x, int dep) {
        if (!o) {
            o = ++nodecnt;
            ch[o][0] = ch[o][1] = 0;
            w[o] = 0;
            xorval[o] = 0;
        }
        if (dep >= maxh) {
            ++w[o]; return;
        }
        insert(ch[o][x & 1], x >> 1, dep + 1);
        maintain(o);
    }
    void erase(int o, int x, int dep) {
        if (dep > 20) {
            --w[o];
            return;
        }
        erase(ch[o][x & 1], x >> 1, dep + 1);
        maintain(o);
    }
    void addallone(int o) {
        // add one for all nodes
        swap(ch[o][1], ch[o][0]);
        if (ch[o][0]) addallone(ch[o][0]);
        maintain(o);
    }
    int merge(int a, int b) {
        // merge b to a
        if (!a) return b;
        if (!b) return a;
        w[a] += w[b]; w[a] &= 1;
        xorval[a] ^= xorval[b];
        ch[a][0] = merge(ch[a][0], ch[b][0]);
        ch[a][1] = merge(ch[a][1], ch[b][1]);
        return a;
    }
}
int n;
int v[maxn];
int rf;
int root[maxn];
vector<int> G[maxn];
ll ans;
void work(int u) {
    for (int i = 0; i < G[u].size(); ++i) {
        int v = G[u][i];
        work(v);
        root[u] = Trie::merge(root[u], root[v]);
    }
    Trie::addallone(root[u]);
    Trie::insert(root[u], v[u], 0);
    ans += Trie::xorval[root[u]];
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &v[i]);
    }
    for (int i = 2; i <= n; ++i) {
        scanf("%d", &rf);
        G[rf].push_back(i);
    }
    work(1);
    printf("%lld\n", ans);
    return 0;
}