struct line{
    int to;
    int cap,flow;
};
vector<line> edge;
vector<int> G[maxn];
int cur[maxn];
bool vis[maxn];
int dis[maxn];
int n,m,s,t,ans;
int ru,rv,rw;
void addedge(int from,int to,int cap){
    edge.push_back((line){to,cap,0});
    edge.push_back((line){from,0,0});
    int m=edge.size();
    G[from].push_back(m-2);
    G[to].push_back(m-1);
}
bool bfs(){
    memset(vis,false,sizeof(vis));
    queue<int> q;
    vis[s]=true;
    dis[s]=0;
    q.push(s);
    while (!q.empty()){
        int now=q.front();
        q.pop();
        for (int i=0;i<G[now].size();++i){
            line e=edge[G[now][i]];
            if (!vis[e.to]&&e.cap>e.flow){
                vis[e.to]=true;
                dis[e.to]=dis[now]+1;
                q.push(e.to);
            }
        }
    }
    return vis[t];
}
int dfs(int x,int a){
    if (a==0||x==t) return a;
    int flow=0,f;
    for (int &i=cur[x];i<G[x].size();++i){
        line &e=edge[G[x][i]];
        if (dis[e.to]==dis[x]+1&&(f=dfs(e.to,min(e.cap-e.flow,a)))){
            flow+=f;
            a-=f;
            e.flow+=f;
            edge[G[x][i]^1].flow-=f;
            if (!a) break;
        }
    }
    return flow;
}
int dinic(){
    while (bfs()){
        memset(cur,0,sizeof(cur));
        ans+=dfs(s,1<<30);
    }
}