struct line{
    int from,to;
    int cap,cost;
}; 
vector<line> edge;
vector<int> G[maxn];
void addedge(int from,int to,int cap,int cost){
    edge.push_back((line){from,to,cap,cost});
    edge.push_back((line){to,from,0,-cost});
    int m=edge.size();
    G[from].push_back(m-2);
    G[to].push_back(m-1);
}
int n,m,s,t,mcost,mflow;
int u,v,w,f;
int dis[maxn],a[maxn],pre[maxn];
bool vis[maxn];
bool spfa(){
    memset(vis,false,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    a[s]=2000000000; dis[s]=0;
    vis[s]=true; pre[s]=0;
    queue<int> q; q.push(s);
    while (!q.empty()){
        int u=q.front(); q.pop();
        vis[u]=false;
        for (int i=0;i<G[u].size();++i){
            line e=edge[G[u][i]];
            if (e.cap>0&&dis[e.to]>dis[u]+e.cost){
                dis[e.to]=dis[u]+e.cost;
                pre[e.to]=G[u][i];
                a[e.to]=min(a[u],e.cap);
                if (!vis[e.to]){
                    vis[e.to]=true; q.push(e.to);
                }
            }
        }
    }
    if (dis[t]==dis[maxn-1]) return false;
    mflow+=a[t]; mcost+=dis[t]*a[t];
    int u=t;
    while (u!=s){
        edge[pre[u]].cap-=a[t];
        edge[pre[u]^1].cap+=a[t];
        u=edge[pre[u]].from;
    }
    return true;
}
int main(){
    scanf("%d%d%d%d",&n,&m,&s,&t);
    while (m--){
        scanf("%d%d%d%d",&u,&v,&w,&f);
        addedge(u,v,w,f);
    }
    while (spfa());
    printf("%d %d",mflow,mcost);
    return 0;
}