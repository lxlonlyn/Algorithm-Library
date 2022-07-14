const int maxn = 50010;
struct Q {
    int l, r, id;
} q[maxn];
int n, m, k;
ll ans, ans_array[maxn];
int block;
bool cmp(const Q a, const Q b) {
    return (a.l / block) ^ (b.l / block) ? 
        a.l < b.l : (a.l / block) & 1 ? 
            a.r < b.r : a.r > b.r;
}
int a[maxn], cnt[maxn];
il void add(int x) {
    ans += 2 * cnt[x] + 1;
    ++cnt[x];
}
il void del(int x) {
    ans -= 2 * cnt[x] - 1;
    --cnt[x];
}
int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d", &q[i].l, &q[i].r);
        q[i].id = i;
    }
    block = n / sqrt(m * 2 / 3);
    sort(q + 1, q + 1 + m, cmp);
    int l = 1, r = 0;
    for (int i = 1; i <= m; ++i) {
        int ql = q[i].l, qr = q[i].r;
        while (l > ql) add(a[--l]);
        while (r < qr) add(a[++r]);
        while (l < ql) del(a[l++]);
        while (r > qr) del(a[r--]);
        ans_array[q[i].id] = ans;
    }
    for (int i = 1; i <= m; ++i) {
        printf("%lld\n", ans_array[i]);
    }
    return 0;
}