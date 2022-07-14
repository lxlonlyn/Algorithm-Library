int dfn[maxn],low[maxn],dfncnt;
int ans[maxn],anstot; 
//anstot:tot of ans,ans[]=1 means ge dian
int vis[maxn];
vector<int> G[maxn];
void tarjan(int u,int fa){
    dfn[u]=low[u]=++dfncnt; vis[u]=1;
    int totchild=0;
    for (int i=0;i<G[u].size();++i){
        int v=G[u][i];
        if (!vis[v]){
            ++totchild; tarjan(v,u);
            low[u]=min(low[u],low[v]);
            if (u!=fa&&low[v]>=dfn[u]&&!ans[u]){
                anstot++; ans[u]=1;
            }
        }else{
            if (v==fa) continue;
            low[u]=min(low[u],dfn[v]);
        }
    }
    if (u==fa&&totchild>=2&&!ans[u]){
        ++anstot; ans[u]=1;
    }
}