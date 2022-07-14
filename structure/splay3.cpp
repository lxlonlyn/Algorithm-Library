//initial build:(1,n+2,0)
int splay_build(int l,int r,int f){
    if (l>r) return 0;
    int mid=(l+r)>>1,tmp=++tot;
    splay[tmp].val=a[mid];
    splay[tmp].fa=f; splay[tmp].cnt++;
    splay[tmp].ch[0]=splay_build(l,mid-1,tmp);
    splay[tmp].ch[1]=splay_build(mid+1,r,tmp);
    splay_maintain(tmp);
    return tmp;
}
void splay_pushdown(int x){
    if (x&&splay[x].tag){
        splay[splay[x].ch[0]].tag^=1;
        splay[splay[x].ch[1]].tag^=1;
        splay[x].tag=0;
        swap(splay[x].ch[0],splay[x].ch[1]);
    }
}
void splay_rotate(int x){
    int y=splay[x].fa,z=splay[y].fa;
    //remember to pushdown
    splay_pushdown(x); splay_pushdown(y);
    int chk=splay_getchild(x);
    splay[y].ch[chk]=splay[x].ch[chk^1];
    splay[splay[x].ch[chk^1]].fa=y;
    splay[x].ch[chk^1]=y;
    splay[y].fa=x; splay[x].fa=z;
    if (z) splay[z].ch[y==splay[z].ch[1]]=x;
    splay_maintain(x); splay_maintain(y);
}
int splay_findvalue_p(int k){
    int cur=root;
    while (1){
        //remember to pushdown
        splay_pushdown(cur);
        if (splay[cur].ch[0]&&k<=splay[splay[cur].ch[0]].sz){
            cur=splay[cur].ch[0];
        }else{
            k-=splay[cur].cnt+splay[splay[cur].ch[0]].sz;
            if (k<=0) return cur;
            cur=splay[cur].ch[1];
        }
    }
}
void splay_reverse(int l,int r){
    l--; r++;
    l=splay_findvalue_p(l);
    r=splay_findvalue_p(r);
    splay_splay(l,0); splay_splay(r,l);
    int tmp=splay[splay[root].ch[1]].ch[0];
    splay[tmp].tag^=1;
}
void splay_print(int x){
    //remember to pushdown
    splay_pushdown(x);
    if (splay[x].ch[0]) splay_print(splay[x].ch[0]);
    if (splay[x].val!=-inf&&splay[x].val!=inf) 
        printf("%d ",splay[x].val);
    if (splay[x].ch[1]) splay_print(splay[x].ch[1]);
}