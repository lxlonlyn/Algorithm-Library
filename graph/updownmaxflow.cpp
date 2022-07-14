struct line{
    int to;
    ll cap,flow;
};
vector<line> edge;
vector<int> G[maxn];
inline void addedge(int from,int to,int cap){
    edge.push_back((line){to,cap,0});
    edge.push_back((line){from,0,0});
    int m=edge.size();
    G[from].push_back(m-2);
    G[to].push_back(m-1);
}
int n,m,S,T,SS,TT;
int ru,rv; ll rl,rr;
ll dflow[maxn],totflow;
int vis[maxn],dep[maxn],cur[maxn];
bool bfs(int tmps,int tmpt){
    memset(vis,0,sizeof(vis));
    dep[tmps]=0; vis[tmps]=1; 
    queue<int> q; q.push(tmps);
    while (!q.empty()){
        int x=q.front(); q.pop();
        for (int i=0;i<G[x].size();++i){
            line &e=edge[G[x][i]];
            if (!vis[e.to]&&e.cap>e.flow){
                dep[e.to]=dep[x]+1;
                vis[e.to]=1; q.push(e.to);
            }
        }
    }
    return vis[tmpt];
}
ll dfs(int x,ll a,int tmpt){
    if (x==tmpt||!a) return a;
    ll flow=0,f;
    for (int &i=cur[x];i<G[x].size();++i){
        line &e=edge[G[x][i]];
        if (dep[e.to]==dep[x]+1&&
            (f=dfs(e.to,min(e.cap-e.flow,a),tmpt))>0){
            flow+=f; a-=f;
            e.flow+=f;
            edge[G[x][i]^1].flow-=f;
            if (!a) break;
        }
    }
    return flow;
}
ll dinic(int tmps,int tmpt){
    ll flow=0;
    while (bfs(tmps,tmpt)){
        memset(cur,0,sizeof(cur));
        flow+=dfs(tmps,inf,tmpt);
    }
    return flow;
}
int main(){
    scanf("%d%d%d%d",&n,&m,&S,&T);
    SS=n+1; TT=n+2;
    for (int i=1;i<=m;++i){
        scanf("%d%d%lld%lld",&ru,&rv,&rl,&rr);
        addedge(ru,rv,rr-rl);
        dflow[ru]-=rl; dflow[rv]+=rl;
    }
    addedge(T,S,inf);
    for (int i=1;i<=n;++i){
        if (!dflow[i]) continue;
        if (dflow[i]>0){
            addedge(SS,i,dflow[i]);
            totflow+=dflow[i];
        }else{
            addedge(i,TT,-dflow[i]);
        }
    }
    if (totflow==dinic(SS,TT)){
        printf("%lld",dinic(S,T));
    }else{
        printf("please go home to sleep"); //no answer
    }
} 