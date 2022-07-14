const int inf=0x3f3f3f3f;
int n,m;
namespace hlpp{
    int S,T;
    struct line{
        int u,v; ll f;
    };
    vector<line> edge;
    vector<int> G[maxn];
    void AddFlow(int u,int v,ll f){
        edge.push_back((line){u,v,f});
        edge.push_back((line){v,u,0});
        int m=edge.size();
        G[u].push_back(m-2);
        G[v].push_back(m-1);
    }
    int ht[maxn],gap[maxn]; ll ex[maxn];
    bool bfs(){
        memset(ht,0x3f,sizeof(ht));
        queue<int> q;
        q.push(T); ht[T]=0;
        while (q.size()){
            int u=q.front(); q.pop();
            for (unsigned int i=0;i<G[u].size();++i){
                int v=edge[G[u][i]].v;
                if (edge[G[u][i]^1].f&&ht[v]>ht[u]+1){
                    ht[v]=ht[u]+1; q.push(v);
                }
            }
        }
        return ht[S]!=inf;
    }
    struct cmp{
        bool operator () (int a,int b) const {
            return ht[a]<ht[b];
        }
    };
    priority_queue<int,vector<int>,cmp> pq;
    bool inq[maxn];
    int push(int u){
        for (unsigned int i=0;i<G[u].size();++i){
            line &e=edge[G[u][i]];
            int v=e.v; ll w=e.f;
            if (!w||ht[u]!=ht[v]+1) continue;
            int k=min(w,ex[u]);
            ex[u]-=k; ex[v]+=k;
            e.f-=k; edge[G[u][i]^1].f+=k;
            if (v!=S&&v!=T&&!inq[v]){
                pq.push(v); inq[v]=1;
            }
            if (!ex[u]) return 0;
        }
        return 1;
    }
    void relable(int u){
        ht[u]=inf;
        for (unsigned int i=0;i<G[u].size();++i){
            line e=edge[G[u][i]];
            if (e.f) ht[u]=min(ht[u],ht[e.v]);
        }
        ++ht[u];
    }
    ll hlpp(){
        if (!bfs()) return 0;
        ht[S]=n;
        memset(gap,0,sizeof(gap));
        for (int i=1;i<=n;++i){
            if (ht[i]!=inf) ++gap[ht[i]];
        }
        for (unsigned int i=0;i<G[S].size();++i){
            line &e=edge[G[S][i]];
            int v=e.v; ll w=e.f;
            if (!w) continue;
            ex[S]-=w; ex[v]+=w;
            e.f-=w; edge[G[S][i]^1].f+=w;
            if (v!=S&&v!=T&&!inq[v]){
                pq.push(v);
            }
        }
        while (pq.size()){
            int u=pq.top();
            pq.pop(); inq[u]=0;
            while (push(u)){
                if (!--gap[ht[u]]){
                    for (int i=1;i<=n;++i){
                        if (i!=S&&i!=T&&ht[i]>ht[u]&&ht[i]<n+1){
                            ht[i]=n+1;
                        }
                    }
                }
                relable(u); ++gap[ht[u]];
            }
        }
        return ex[T];
    }
}