void addpath(int a,int b,int k){
    cnt[a]+=k; cnt[b]+=k;
    int f=lca(a,b);
    cnt[f]-=k; cnt[anc[f][0]]-=k;
}
void dfs_sum(int x,int fa){
    for (int i=0;i<G[x].size();++i){
        if (G[x][i]==fa) continue;
        dfs_sum(G[x][i],x);
        cnt[x]+=cnt[G[x][i]];
    }
}