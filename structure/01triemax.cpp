const int maxn = 100010;
int T, n, k;
int a[maxn], sum[maxn];
int ansl, ansr;
int tree[maxn * 30][2], cnt;
int rt[maxn * 30];
void add(int pos) {
    int cur = 0, tmp;
    for (int i = 29; i >= 0; --i) {
        tmp = (sum[pos] >> i) & 1;
        if (!tree[cur][tmp]) {
            tree[cur][tmp] = ++cnt;
            tree[cnt][0] = tree[cnt][1] = 0;
        }
        cur = tree[cur][tmp];
        rt[cur] = max(rt[cur], pos);
    }
}
int query(int x) {
    int cur = 0, tmp, pos = -1;
    for (int i = 29; i >= 0; --i) {
        tmp = (x >> i) & 1;
        if ((k >> i) & 1) {
            // k[i]=1: must different
            cur = tree[cur][tmp^1];
        } else {
            // k[i]=0: different>k, same continue
            if (tree[cur][tmp^1]) {
                pos = max(pos, rt[tree[cur][tmp^1]]);
            }
            cur = tree[cur][tmp];
        }
        if (!cur) break;
    }
    // same to end
    if (cur) pos = max(pos, rt[cur]);
    return pos;
}
int main() {
    T = read();
    while (T--) {
        memset(rt, -1, sizeof(rt));
        cnt = 0; 
        tree[0][0] = tree[0][1] = 0;
        n = read(); k = read();
        ansl = -1; ansr = n;
        for (int i = 1; i <= n; ++i) {
            a[i] = read();
            sum[i] = sum[i-1] ^ a[i];
        }
        if (k == 0) {
            printf("1 1\n");
            continue;
        }
        add(0);
        for (int i = 1; i <= n; ++i) {
            int r = query(sum[i]);
            if (r >= 0 && i - r < ansr - ansl) {
                ansr = i;
                ansl = r;
            }
            add(i);
        }
        if (ansl >= 0) {
            printf("%d %d\n", ansl+1, ansr);
        } else {
            printf("-1\n");
        }
    }
    return 0;
}