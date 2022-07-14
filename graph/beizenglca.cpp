vector<int> G[maxn];
int anc[maxn][20];
int dep[maxn];
void dfs(int x,int fa,int d){
    dep[x]=d; anc[x][0]=fa;
    for (int i=0;i<G[x].size();++i){
        if (G[x][i]==fa) continue;
        dfs(G[x][i],x,d+1);
    }
}
void lca_prework(){
    dfs(1,0,1);
    for (int j=1;j<20;++j){
        for (int i=1;i<=n;++i){
            anc[i][j]=anc[anc[i][j-1]][j-1];
        }
    }
}
int single_up(int x,int k){ 
    for (int j=0;k;++j){
        if (k&1) x=anc[x][j];
        k>>=1;
    }
    return x;
}
int lca(int x,int y){
    if (dep[x]<dep[y]) swap(x,y);
    x=single_up(x,dep[x]-dep[y]);
    if (x==y) return x;
    for (int j=19;j>=0;--j){
        if (anc[x][j]!=anc[y][j]){
            x=anc[x][j]; y=anc[y][j];
        }
    }
    return anc[x][0];
}