#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
#define ll long long
#define il inline
const int maxn=100010;
const ll mod=51061;
struct LinkCutTree{
    #define lc ch[x][0]
    #define rc ch[x][1]
    int ch[maxn][2],fa[maxn];
    ll val[maxn],siz[maxn],sum[maxn];
    int revtag[maxn];
    ll addtag[maxn],multag[maxn];
    int getch(int x){return ch[fa[x]][1]==x;}
    int isroot(int x){return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;}
    void pushrev(int x){
        swap(lc,rc); revtag[x]^=1;
    }
    void pushadd(int x,ll a){
        val[x]=(val[x]+a)%mod;
        sum[x]=(sum[x]+a*siz[x])%mod;
        addtag[x]=(addtag[x]+a)%mod;
    }
    void pushmul(int x,ll a){
        val[x]=(val[x]*a)%mod;
        sum[x]=(sum[x]*a)%mod;
        multag[x]=(multag[x]*a)%mod;
        addtag[x]=(addtag[x]*a)%mod;
    }
    void pushdown(int x){
        if (multag[x]!=1){
            pushmul(lc,multag[x]);
            pushmul(rc,multag[x]);
            multag[x]=1;
        }
        if (addtag[x]){
            pushadd(lc,addtag[x]);
            pushadd(rc,addtag[x]);
            addtag[x]=0;
        }
        if (revtag[x]){
            if (lc) pushrev(lc);
            if (rc) pushrev(rc);
            revtag[x]^=1;
        }
    }
    void pushup(int x){
        sum[x]=(sum[lc]+sum[rc]+val[x])%mod;
        siz[x]=siz[lc]+siz[rc]+1;
    }
    void rotate(int x){
        int y=fa[x],z=fa[y],chk=getch(x),w=ch[x][chk^1];
        if (!isroot(y)) ch[z][y==ch[z][1]]=x;
        ch[x][chk^1]=y;
        ch[y][chk]=w;
        if (w) fa[w]=y;
        fa[y]=x; fa[x]=z;
        pushup(y);
    }
    int st[maxn];
    void splay(int x){
        int y=x,z=0;
        st[++z]=y;
        while (!isroot(y)) st[++z]=y=fa[y];
        while (z) pushdown(st[z--]);
        while (!isroot(x)){
            y=fa[x]; z=fa[y];
            if (!isroot(y))
                rotate((ch[y][0]==x)^(ch[z][0]==y)?x:y);
            rotate(x);
        }
        pushup(x);
    }
    void access(int x){
        for (int y=0;x;x=fa[y=x]){
            splay(x); rc=y; pushup(x);
        }
    }
    void makeroot(int x){
        access(x); splay(x); pushrev(x);
    }
    int findroot(int x){
        access(x); splay(x);
        while (lc){
            pushdown(x); x=lc;
        }
        splay(x); return x;
    }
    void split(int x,int y){
        //here y is splay's root 
        makeroot(x);
        access(y); splay(y);
    }
    void link(int x,int y){
        //x's father is y
        makeroot(x);
        if (findroot(y)!=x) fa[x]=y;
    }
    /* if it's always legal
    void link(int x,int y){
        makeroot(x); fa[x]=y;
    }
    */
    void cut(int x,int y){
        makeroot(x);
        if (x==findroot(y)&&fa[y]==x&&!ch[y][0]){
            fa[y]=ch[x][1]=0;
            pushup(x);
        }
        //below also ok:
        //if (!(findroot(y)!=x||siz[x]>2)){}
    }
    /* if it's always legal
    void cut(int x,int y){
        split(x,y); fa[x]=ch[y][0]=0;
        pushup(y);
    }
    */
    #undef lc
    #undef rc
}tree;
int n,q;
int rx,ry,ra,rb,rc,rd;
char opt;
int main(){
    scanf("%d%d",&n,&q);
    for (int i=1;i<=n;++i){
        tree.val[i]=1;
        tree.multag[i]=1;
        tree.siz[i]=1;
    }
    for (int i=1;i<n;++i){
        scanf("%d%d",&rx,&ry);
        tree.link(rx,ry);
    }
    while (q--){
        opt=getchar();
        while (opt!='+'&&opt!='-'&&opt!='*'&&opt!='/')
            opt=getchar();
        switch (opt){
            case '+': //link add ra->rb rc
                scanf("%d%d%d",&ra,&rb,&rc);
                tree.split(ra,rb);
                tree.pushadd(rb,rc);
                break;
            case '-': //cut ra-rb
                scanf("%d%d",&ra,&rb);
                tree.cut(ra,rb);
                scanf("%d%d",&ra,&rb);
                tree.link(ra,rb);
                break;
            case '*': //link mul ra->rb rc
                scanf("%d%d%d",&ra,&rb,&rc);
                tree.split(ra,rb);
                tree.pushmul(rb,rc);
                break;
            case '/': //link query ra->rb
                scanf("%d%d",&ra,&rb);
                tree.split(ra,rb);
                printf("%lld\n",tree.sum[rb]);
        }
    }
    return 0;
}