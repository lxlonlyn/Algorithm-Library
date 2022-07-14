int dfn[maxn],low[maxn],dfncnt; 
int sta[maxn],tp; //stack
int scc[maxn],scc_tot; 
//scc[]:every point belongs to which scc 
int siz[maxn]; //the siz of each scc
int in_stack[maxn];
void tarjan(int u){
    dfn[u]=low[u]=++dfncnt; 
    sta[++tp]=u; in_stack[u]=1;
    for (int i=0;i<G[u].size();++i){
        int v=G[u][i];
        if (!dfn[v]){
            tarjan(v); low[u]=min(low[u],low[v]);
        }else{
            if (in_stack[v]) low[u]=min(low[u],dfn[v]);
        }
    }
    if (dfn[u]==low[u]){
        ++scc_tot;
        while (sta[tp]!=u){
            scc[sta[tp]]=scc_tot; ++siz[scc_tot]; 
            in_stack[sta[tp--]]=0;
        }
        scc[sta[tp]]=scc_tot; ++siz[scc_tot]; 
        in_stack[sta[tp--]]=0;
    }
}
//to be used
for (int i=1;i<=n;++i){
    if (!dfn[i]) tarjan(i);
}