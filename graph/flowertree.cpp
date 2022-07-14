namespace FlowerTree{
    vector<int> G[maxn];
    int lk[maxn];
    int tag[maxn],pre[maxn];
    int fa[maxn];
    int dfn[maxn],dfncnt;
    queue<int> q;
    void addedge(int u,int v){
        G[u].push_back(v);
        G[v].push_back(u);
        if (!lk[u]&&!lk[v]){
            lk[u]=v; lk[v]=u; ++ans;
        }
    }
    int findx(int x){
        return (fa[x]==x)?x:fa[x]=findx(fa[x]);
    }
    void aug(int x){
        int nxt;
        while (x){
            nxt=lk[pre[x]];
            lk[x]=pre[x];
            lk[pre[x]]=x;
            x=nxt;
        }
    }
    int lca(int x,int y){
        ++dfncnt;
        while (dfn[x=findx(x)]!=dfncnt){
            if (x) dfn[x]=dfncnt;
            x=pre[lk[x]]; swap(x,y);
        }
        return x;
    }
    void shrink(int u,int v,int p){
        while (findx(u)!=p){
            pre[u]=v; v=lk[u];
            fa[u]=fa[v]=p;
            if (tag[v]==2){
                tag[v]=1; q.push(v);
            }
            u=pre[v];
        }
    }
    int blossom(int u){
        memset(tag,0,sizeof(tag));
        memset(pre,0,sizeof(pre));
        for (int i=1;i<=n;++i) fa[i]=i;
        while (!q.empty()) q.pop();
        q.push(u); tag[u]=1;
        while (!q.empty()){
            int u=q.front(); q.pop();
            for (int i=0;i<G[u].size();++i){
                int v=G[u][i];
                if (tag[v]==1){
                    int p=lca(u,v);
                    shrink(u,v,p);
                    shrink(v,u,p);
                }
                else if (tag[v]==0){
                    pre[v]=u; tag[v]=2;
                    if (!lk[v]){
                        aug(v); return 1;
                    }else{
                        tag[lk[v]]=1;
                        q.push(lk[v]);
                    }
                }
            }
        }
        return 0;
    }
    int solve(){
        for (int i=1;i<=n;++i){
            if (!lk[i]){
                ans+=FlowerTree::blossom(i);
            }
        }
        return ans;
    }
}