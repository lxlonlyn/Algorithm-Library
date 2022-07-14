void get_root(int x,int fa){
    sz[x]=1; mxs[x]=0;
    for (int i=0;i<G[x].size();++i){
        line e=edge[G[x][i]];
        if (e.to==fa||vis[e.to]) continue;
        get_root(e.to,x);
        sz[x]+=sz[e.to];
        mxs[x]=max(mxs[x],sz[e.to]);
    }
    mxs[x]=max(mxs[x],sum-mxs[x]);
    if (mxs[x]<mxs[root]){
        root=x;
    }
}
void get_data(int x,int fa,int dis){
    sta[++top]=dis;
    for (int i=0;i<G[x].size();++i){
        line e=edge[G[x][i]];
        if (e.to==fa||vis[e.to]) continue;
        get_data(e.to,x,dis+e.val);
    }
}
void calc(int x,int flag,int dis){
    top=0; get_data(x,0,dis);
    for (int i=1;i<top;++i){
        for (int j=i+1;j<=top;++j){
            if (sta[i]+sta[j]>10000000) continue;
            ans[sta[i]+sta[j]]+=flag;
        }
    }
}
void solve(int x){
    calc(x,1,0); vis[x]=1;
    for (int i=0;i<G[x].size();++i){
        line e=edge[G[x][i]];
        if (vis[e.to]) continue;
        calc(e.to,-1,e.val);
        root=0; sum=sz[e.to];
        get_root(e.to,x); solve(root);
    }
}