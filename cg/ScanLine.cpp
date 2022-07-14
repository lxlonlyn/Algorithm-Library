const int maxn = 100010;
struct ScanLine {
    #define ls o << 1
    #define rs ls | 1
    int n;
    struct ScanLineNode {
        int x, y1, y2;
        int flag;
        bool operator < (const ScanLineNode o) {
            return x < o.x;
        }
    } p[maxn << 1];
    int mp[maxn << 1];
    int mpcnt;
    struct SegTreeNode {
        int dl, dr, sum;
        int cnt; 
    } tree[maxn << 4]; 
    // attention: 16 times is preffered
    void readIn() {
        scanf("%d", &n);
        int rx, rxx, ry, ryy; 
        for (int i = 1; i <= (n << 1); i += 2) {
            scanf("%d%d%d%d", &rx, &ry, &rxx, &ryy);
            p[i].x = rx; p[i].y1 = ry; p[i].y2 = ryy;
            p[i].flag = 1;
            p[i + 1].x = rxx; p[i + 1].y1 = ry; p[i + 1].y2 = ryy;
            p[i + 1].flag = -1;
            mp[i] = ry; mp[i + 1] = ryy;
        }
    }

    void build(int o, int l, int r) {
        tree[o].dl = mp[l];
        tree[o].dr = mp[r];
        tree[o].sum = 0; 
        tree[o].cnt = 0;
        if (r - l > 1) {
            int mid = (l + r) >> 1;
            build(ls, l, mid);
            build(rs, mid, r);
        } 
    }

    void init() {
        sort(mp + 1, mp + 1 + (n << 1));
        mpcnt = unique(mp + 1, mp + 1 + (n << 1)) - mp - 1;
        sort(p + 1, p + 1 + (n << 1));
        build(1, 1, mpcnt);
    }

    void pushup(int o) {
        if (tree[o].cnt > 0) {
            tree[o].sum = tree[o].dr - tree[o].dl;
        } else {
            tree[o].sum = tree[ls].sum + tree[rs].sum;
        }
    }

    void update(int o, int ql, int qr, int v) {
        // cout << o << " " << ql << " " << qr << endl; 
        if (tree[o].dl >= ql && tree[o].dr <= qr) {
            tree[o].cnt += v;
            pushup(o);
        } else {
            if (tree[ls].dr > ql) update(ls, ql, qr, v);
            if (tree[rs].dl < qr) update(rs, ql, qr, v);
            pushup(o);
        }
    }

    ll calc() {
        ll ans = 0;
        update(1, p[1].y1, p[1].y2, p[1].flag);
        for (int i = 2; i <= (n << 1); ++i) {
            ans += 1ll * (p[i].x - p[i - 1].x) * tree[1].sum;
            update(1, p[i].y1, p[i].y2, p[i].flag);
        }
        return ans;
    }
    #undef ls
    #undef rs
} S;
int main() {
    S.readIn();
    S.init();
    printf("%lld", S.calc());
    return 0;
}
