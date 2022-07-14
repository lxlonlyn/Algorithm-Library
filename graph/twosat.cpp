namespace TwoSat{
    vector<int> G[maxn<<1];
    void addedge(int from,int to){
        G[from].push_back(to);
    }
    int dfn[maxn<<1],low[maxn<<1],dfncnt;
    int sta[maxn<<1],tp;
    int scc[maxn<<1],scc_tot;
    int siz[maxn<<1];
    int in_stack[maxn<<1];
    //if there are multi problem don't forget
    void init(){
        for (int i=0;i<(n<<1);++i) G[i].clear();
        dfncnt=tp=scc_tot=0;
        memset(dfn,0,sizeof(dfn));
        memset(low,0,sizeof(low));
        memset(sta,0,sizeof(sta));
        memset(scc,0,sizeof(scc));
        memset(siz,0,sizeof(siz));
        memset(in_stack,0,sizeof(in_stack));
    }
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
    bool solve(){
        //adjust the range if necessary
        for (int i=0;i<(n<<1);++i){
            if (!dfn[i]) tarjan(i);
        }
        for (int i=0;i<(n<<1);i+=2){
            if (scc[i]==scc[i+1]) return false;
        }
        return true;
    }
}