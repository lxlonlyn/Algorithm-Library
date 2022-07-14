#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
using namespace std;
#define ll long long 
#define il inline
const int maxn = 310;
const int INF = 0x3f3f3f3f;
struct line {
    int from, to;
    int cap, cost;
};
vector<line> edge;
vector<int> G[maxn];
void addedge(int from, int to, int cap, int cost) {
    edge.push_back((line){from, to, cap, cost});
    edge.push_back((line){to, from, 0, -cost});
    int m = edge.size();
    G[from].push_back(m - 2);
    G[to].push_back(m - 1);
}
int dis[maxn], a[maxn], pre[maxn];
bool vis[maxn];
int mflow, mcost;
bool spfa(int tmpS, int tmpT) {
    memset(vis, 0, sizeof(vis));
    memset(dis, 0x3f, sizeof(dis));
    a[tmpS] = INF; dis[tmpS] = 0;
    vis[tmpS] = true; pre[tmpS] = 0;
    queue<int> q; q.push(tmpS);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        vis[u] = false;
        for (int i = 0; i < G[u].size(); ++i) {
            line e = edge[G[u][i]];
            if (e.cap > 0 && dis[e.to] > dis[u] + e.cost) {
                dis[e.to] = dis[u] + e.cost;
                pre[e.to] = G[u][i];
                a[e.to] = min(a[u], e.cap);
                if (!vis[e.to]) {
                    vis[e.to] = true;
                    q.push(e.to);
                }
            }
        }
    }
    if (dis[tmpT] == INF) return false;
    mflow += a[tmpT];
    mcost += dis[tmpT] * a[tmpT];
    int u = tmpT;
    while (u != tmpS) {
        edge[pre[u]].cap -= a[tmpT];
        edge[pre[u] ^ 1].cap += a[tmpT];
        u = edge[pre[u]].from;
    }
    return true;
}
int n, S, T, SS, TT;
int dflow[maxn];
int totcost;
int main() {
    scanf("%d", &n);
    S = 1; T = n + 1;
    SS = T + 1; TT = SS + 1;
    int rk, rb, rt;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &rk);
        while (rk--) {
            scanf("%d%d", &rb, &rt);
            addedge(i, rb, INF, rt);
            --dflow[i]; ++dflow[rb];
            // dflow is always 1 this place
            // change dflow when necessary
            totcost += rt * 1;
            // totcost = lowestflow * cost;
            // change when necessary
        }
    }
    for (int i = 1; i <= n; ++i) {
        addedge(i, T, INF, 0);
    }
    addedge(T, S, INF, 0);
    for (int i = 1; i <= n + 1; ++i) {
        if (!dflow[i]) continue;
        if (dflow[i] > 0) {
            addedge(SS, i, dflow[i], 0);
        } else {
            addedge(i, TT, -dflow[i], 0);
        }
    }
    while (spfa(SS, TT));
    totcost += mcost;
    printf("%d", totcost);
    return 0;
}