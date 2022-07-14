namespace hungarian{
    vector<int> G[maxn];
    int vis[maxn];
    int p[maxn]; //p[right]=left
    bool match(int u){
        for (int i=0;i<G[u].size();++i){
            int v=G[u][i];
            if (vis[v]) continue;
            vis[v]=1;
            if (!p[v]||match(p[v])){
                p[v]=u; return true;
            }
        }
        return false;
    }
    int hungarian(){
        int cnt=0;
        for (int i=1;i<=n;++i){
            memset(vis,0,sizeof(vis));
            if (match(i)){
                ++cnt;
            }
        }
        return cnt;
    }
}