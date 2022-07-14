#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
#include <vector>
using namespace std;
#define ll long long 
#define il inline
const int maxn = 210;
const int maxm = 11000;
const ll INF = 0x3f3f3f3f3f3f3f3f;
struct line{
    int to;
    ll cap, flow;
};
vector<line> edge;
vector<int> G[maxn];
void addedge(int from, int to, int cap) {
    edge.push_back((line){to, cap, 0});
    edge.push_back((line){from, 0, 0});
    int m = edge.size();
    G[from].push_back(m - 2);
    G[to].push_back(m - 1);
}
int n, m, S, T, SS, TT;
ll dflow[maxn], totflow;
ll minflow[maxm];
int dep[maxn], vis[maxn], cur[maxn];
bool bfs(int tmpS, int tmpT) {
    memset(vis, 0, sizeof(vis));
    dep[tmpS] = 0; vis[tmpS] = 1;
    queue<int> q; q.push(tmpS);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = 0; i < G[u].size(); ++i) {
            line &e = edge[G[u][i]];
            if (!vis[e.to] && e.cap > e.flow) {
                dep[e.to] = dep[u] + 1;
                vis[e.to] = 1;
                q.push(e.to);
            }
        }
    }
    return vis[tmpT];
}
ll dfs(int x, ll a, int tmpT) {
    if (x == tmpT || !a) return a;
    ll flow = 0, f;
    for (int &i = cur[x]; i < G[x].size(); ++i) {
        line &e = edge[G[x][i]];
        if (dep[e.to] == dep[x] + 1 && 
            (f = dfs(e.to, min(e.cap - e.flow, a), tmpT)) > 0) {
                flow += f; a -= f;
                e.flow += f;
                edge[G[x][i] ^ 1].flow -= f;
                if (!a) break;
            }
    }
    return flow;
}
ll dinic(int tmpS, int tmpT) {
    ll flow = 0;
    while (bfs(tmpS, tmpT)) {
        memset(cur, 0, sizeof(cur));
        flow += dfs(tmpS, INF, tmpT);
    }
    return flow;
}
int main() {
    scanf("%d%d", &n, &m);
    SS = n + 1; TT = n + 2;
    int ru, rv; ll rr;
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d%lld%lld", &ru, &rv, &minflow[i], &rr);
        addedge(ru, rv, rr - minflow[i]);
        dflow[ru] -= minflow[i]; 
        dflow[rv] += minflow[i];
    }
    for (int i = 1; i <= n; ++i) {
        if (!dflow[i]) continue;
        if (dflow[i] > 0) {
            addedge(SS, i, dflow[i]);
            totflow += dflow[i];
        } else {
            addedge(i, TT, -dflow[i]);
        }
    }
    if (totflow == dinic(SS, TT)) {
        printf("YES\n");
        for (int i = 1; i <= m; ++i) {
            printf("%lld\n", edge[(i - 1) * 2].flow + minflow[i]);
        }
    } else {
        printf("NO");
    }
    return 0;
}