#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
using namespace std;
#define ll long long 
#define il inline
const int maxn=100010;
struct treenode{
    ll sum,lazy;
}tree[maxn<<2];
vector<int> G[maxn];
int n,m,root; ll mod;
ll val[maxn],n_val[maxn]; 
int opt,rx,ry; ll rz;
int fa[maxn],dep[maxn],son[maxn];
int siz[maxn],top[maxn],dfn[maxn],tot;
/*
treenode:sgt val[]->n_val[]:turn the order 
first:dfs_getson(). then dfs_getlink()
*/
void dfs_getson(int u){
    siz[u]=1;
    for (int i=0;i<G[u].size();++i){
        int v=G[u][i];
        if (v==fa[u]) continue;
        fa[v]=u; dep[v]=dep[u]+1;
        dfs_getson(v); siz[u]+=siz[v];
        if (siz[v]>siz[son[u]]) son[u]=v; 
    }
}
void dfs_getlink(int u,int tp){
    top[u]=tp; dfn[u]=++tot; n_val[tot]=val[u];
    if (son[u]) dfs_getlink(son[u],tp);
    for (int i=0;i<G[u].size();++i){
        int v=G[u][i];
        if (v==fa[u]||v==son[u]) continue;
        dfs_getlink(v,v);
    }
}
#define ls o<<1
#define rs ls|1
void sgt_build(int o,int l,int r){
    if (l==r){
        tree[o].sum=n_val[l];
        return;
    } 
    int mid=(l+r)>>1;
    sgt_build(ls,l,mid); sgt_build(rs,mid+1,r);
    tree[o].sum=(tree[ls].sum+tree[rs].sum)%mod;
}
void sgt_pushdown(int o,int l,int r){
    tree[ls].lazy=(tree[ls].lazy+tree[o].lazy)%mod;
    tree[rs].lazy=(tree[rs].lazy+tree[o].lazy)%mod;
    int mid=(l+r)>>1;
    tree[ls].sum=(tree[ls].sum+tree[o].lazy*(mid-l+1)%mod)%mod;
    tree[rs].sum=(tree[rs].sum+tree[o].lazy*(r-mid)%mod)%mod;
    tree[o].lazy=0;
}
void sgt_add(int o,int l,int r,int ql,int qr,ll k){
    if (l>=ql&&r<=qr){
        tree[o].lazy=(tree[o].lazy+k)%mod;
        tree[o].sum=(tree[o].sum+(r-l+1)*k%mod)%mod;
        return;
    }
    if (tree[o].lazy) sgt_pushdown(o,l,r);
    int mid=(l+r)>>1;
    if (ql<=mid) sgt_add(ls,l,mid,ql,qr,k);
    if (qr>mid) sgt_add(rs,mid+1,r,ql,qr,k);
    tree[o].sum=(tree[ls].sum+tree[rs].sum)%mod;
}
ll sgt_querysum(int o,int l,int r,int ql,int qr){
    if (l>=ql&&r<=qr){
        return tree[o].sum;
    }
    int mid=(l+r)>>1;
    if (tree[o].lazy) sgt_pushdown(o,l,r);
    ll res=0;
    if (ql<=mid) res=(res+sgt_querysum(ls,l,mid,ql,qr))%mod;
    if (qr>mid) res=(res+sgt_querysum(rs,mid+1,r,ql,qr))%mod;
    return res;
}
#undef ls
#undef rs
void link_add(){
    while (top[rx]!=top[ry]){
        if (dep[top[rx]]>dep[top[ry]]) swap(rx,ry);
        sgt_add(1,1,tot,dfn[top[ry]],dfn[ry],rz);
        ry=fa[top[ry]];
    }
    if (dep[rx]>dep[ry]) swap(rx,ry);
    sgt_add(1,1,tot,dfn[rx],dfn[ry],rz);
}
ll link_query(){
    ll res=0;
    while (top[rx]!=top[ry]){
        if (dep[top[rx]]>dep[top[ry]]) swap(rx,ry);
        res=(res+sgt_querysum(1,1,tot,dfn[top[ry]],dfn[ry]))%mod;
        ry=fa[top[ry]];
    }
    if (dep[rx]>dep[ry]) swap(rx,ry);
    res=(res+sgt_querysum(1,1,tot,dfn[rx],dfn[ry]))%mod;
    return res;
}
void subtree_add(){
    sgt_add(1,1,tot,dfn[rx],dfn[rx]+siz[rx]-1,rz);
}
ll subtree_query(){
    return sgt_querysum(1,1,tot,dfn[rx],dfn[rx]+siz[rx]-1)%mod;
}
int main(){
    scanf("%d%d%d%lld",&n,&m,&root,&mod);
    for (int i=1;i<=n;++i){
        scanf("%lld",&val[i]);
    }
    for (int i=1;i<n;++i){
        scanf("%d%d",&rx,&ry);
        G[rx].push_back(ry);
        G[ry].push_back(rx);
    }
    dfs_getson(root); dfs_getlink(root,root);
    sgt_build(1,1,tot); 
    for (int i=1;i<=m;++i){
        scanf("%d",&opt);
        if (opt==1){
            scanf("%d%d%lld",&rx,&ry,&rz);
            link_add();
        }
        if (opt==2){
            scanf("%d%d",&rx,&ry);
            printf("%lld\n",link_query());
        }
        if (opt==3){
            scanf("%d%lld",&rx,&rz);
            subtree_add();
        }
        if (opt==4){
            scanf("%d",&rx);
            printf("%lld\n",subtree_query());
        }
    }
    return 0;
}