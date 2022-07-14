namespace km{
    int px[maxn],py[maxn];
    int pre[maxn];
    int visx[maxn],visy[maxn];
    ll lx[maxn],ly[maxn];
    ll slack[maxn];
    ll g[maxn][maxn];
    queue<int> q;
    void init(){
        for (int i=0;i<maxn;++i){
            for (int j=0;j<maxn;++j){
                g[i][j]=-inf;
            }
        }
        memset(px,-1,sizeof(px));
        memset(py,-1,sizeof(py));
        memset(pre,0,sizeof(pre));
        memset(visx,0,sizeof(visx));
        memset(visy,0,sizeof(visy));
        memset(slack,0x3f,sizeof(slack));
    }
    void addedge(int u,int v,ll w){
        g[u][v]=w;
    }
    bool match(int v){
        visy[v]=1;
        if (py[v]!=-1){
            q.push(py[v]);
            visx[py[v]]=1;
            return false;
        }
        while (v!=-1){
            py[v]=pre[v];
            swap(v,px[pre[v]]);
        }
        return true;
    }
    void bfs(int x){
        while (!q.empty()) q.pop();
        q.push(x); visx[x]=1;
        while (true){
            while (!q.empty()){
                int u=q.front(); q.pop();
                for (int v=1;v<=n;++v){
                    if (visy[v]) continue;
                    ll delta=lx[u]+ly[v]-g[u][v];
                    if (slack[v]>=delta){
                        pre[v]=u;
                        if (delta){
                            slack[v]=delta;
                        }else{
                            if (match(v)) return;
                        }
                    }
                }
            }
            ll a=inf;
            for (int j=1;j<=n;++j){
                if (!visy[j]){
                    a=min(a,slack[j]);
                }
            }
            for (int j=1;j<=n;++j){
                if (visx[j]) lx[j]-=a;
                if (visy[j]) ly[j]+=a;
                else slack[j]-=a;
            }
            for (int j=1;j<=n;++j){
                if (!visy[j]&&!slack[j]&&match(j)) return;
            }
        }
    }
    ll solve(){
        for (int i=1;i<=n;++i) lx[i]=-inf;
        memset(ly,0,sizeof(ly));
        for (int i=1;i<=n;++i){
            for (int j=1;j<=n;++j){
                lx[i]=max(lx[i],g[i][j]);
            }
        }
        for (int i=1;i<=n;++i){
            memset(slack,0x3f,sizeof(slack));
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            bfs(i);
        }
        ll res=0;
        for (int i=1;i<=n;++i){
            res+=lx[i]+ly[i];
        }
        return res;
    }
}