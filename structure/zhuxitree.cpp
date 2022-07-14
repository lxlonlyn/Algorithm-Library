#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
#include <vector>
using namespace std;
const int maxn = 200010;
int n, m;
int len;
int a[maxn], b[maxn];

struct treenode {
    int ls, rs;
    int sum;
} tree[maxn << 5];
int root[maxn];
int cnt, tmp;
int rl, rr, rk;

void pushup(int o) {
    tree[o].sum = tree[tree[o].ls].sum + tree[tree[o].rs].sum;
}

void build(int &o, int l, int r) {
    o = ++cnt;
    if (l == r) {
        tree[o].sum = 0;
        return;
    }
    int mid = (l + r) >> 1;
    build(tree[o].ls, l, mid);
    build(tree[o].rs, mid+1, r);
    pushup(o);
}

void update(int &o, int l, int r, int lst, int val) {
    o = ++cnt;
    tree[o].ls = tree[lst].ls;
    tree[o].rs = tree[lst].rs;
    if (l == r) {
        tree[o].sum = tree[lst].sum + 1;
        return;
    }
    int mid = (l + r) >> 1;
    if (val <= mid) 
        update(tree[o].ls, l, mid, tree[lst].ls, val);
    else 
        update(tree[o].rs, mid+1, r, tree[lst].rs, val);
    pushup(o);
}

int query(int oL, int oR, int l, int r, int val) {
    if (l == r) {
        return l;
    }
    int mid = (l + r) >> 1;
    int tot = tree[tree[oR].ls].sum - tree[tree[oL].ls].sum;
    if (val <= tot)
        return query(tree[oL].ls, tree[oR].ls, l, mid, val);
    else 
        return query(tree[oL].rs, tree[oR].rs, mid+1, r, val-tot);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    sort(b+1, b+1+n);
    len = unique(b+1, b+1+n) - (b+1);

    build(root[0], 1, len);
    for (int i = 1; i <= n; ++i) {
        tmp = lower_bound(b+1, b+1+len, a[i]) - b;
        update(root[i], 1, len, root[i-1], tmp);
    }
    while (m--) {
        scanf("%d%d%d", &rl, &rr, &rk);
        printf("%d\n", b[query(root[rl-1], root[rr], 1, len, rk)]);
    }
    return 0;
}