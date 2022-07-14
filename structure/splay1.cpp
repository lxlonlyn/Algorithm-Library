int root,tot,fa[maxn],ch[maxn][2];
int val[maxn],cnt[maxn],sz[maxn];
void maintain(int x){ //calc the size of subtree
    sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+cnt[x];
}
int get_child(int x){ 
    return x==ch[fa[x]][1];
}
void clear(int x){ //not equal to delete
    ch[x][0]=ch[x][1]=fa[x]=val[x]=sz[x]=cnt[x]=0;
}
void rotate(int x){ 
    int y=fa[x],z=fa[y],chk=get_child(x);
    ch[y][chk]=ch[x][chk^1];
    fa[ch[x][chk^1]]=y;
    ch[x][chk^1]=y;
    fa[y]=x; fa[x]=z;
    if (z) ch[z][y==ch[z][1]]=x;
    maintain(x); maintain(y);
}
void splay(int x,int goal){ 
    //make x the son of goal(0:make it root) 
    for (int f;(f=fa[x])!=goal;rotate(x)){
        if (fa[f]!=goal) rotate(get_child(x)==get_child(f)?f:x);
    }
    if (!goal) root=x;
}
void ins(int k){ 
    //add a point val k
    if (!root){
        val[++tot]=k; cnt[tot]++;
        root=tot; maintain(root);
        return;
    }
    int cur=root,f=0;
    while (1){
        if (val[cur]==k){
            cnt[cur]++; 
            maintain(cur); maintain(f);
            splay(cur,0);
            break;
        }
        f=cur;
        cur=ch[cur][val[cur]<k];
        if (!cur){
            val[++tot]=k; cnt[tot]++;
            fa[tot]=f; ch[f][val[f]<k]=tot;
            maintain(tot); maintain(f);
            splay(tot,0);
            break;
        }
    }
}
int findrank(int k){ 
    //return point's rank which value is k
    int res=0,cur=root;
    while (1){
        if (k<val[cur]){
            cur=ch[cur][0];
        }else{
            res+=sz[ch[cur][0]];
            if (k==val[cur]){
                splay(cur,0); return res+1;
            }
            res+=cnt[cur];
            cur=ch[cur][1];
        }
    }
}
int findvalue(int k){ 
    //return point's value which rank is k
    int cur=root;
    while (1){
        if (ch[cur][0]&&k<=sz[ch[cur][0]]){
            cur=ch[cur][0];
        }else{
            k-=cnt[cur]+sz[ch[cur][0]];
            if (k<=0) return val[cur];
            cur=ch[cur][1];
        }
    }
}
int prenumber(){ 
    /*this is just step 2
    steps:
    1.add a point val x then it backs to root
    2.root's left's right(to leaf) is the biggest number less than x
    3.delete x
    */
    int cur=ch[root][0];
    while (ch[cur][1]) cur=ch[cur][1];
    return cur;
}
int nxtnumber(){ 
    int cur=ch[root][1];
    while (ch[cur][0]) cur=ch[cur][0];
    return cur;
}
void del(int k){ //delete
    /*
    1.x to root
    2.if there are more than one,just dec
    3.if no child just delete
    4.if only one child:delete myself,make child root
    5.make prenumber root,root's right subtree to roots'right,refresh
    */
    findrank(k);
    if (cnt[root]>1){
        cnt[root]--; maintain(root);
        return;
    }
    if (!ch[root][0]&&!ch[root][1]){
        clear(root); root=0;
        return;
    }
    if (!ch[root][0]){
        int cur=root; root=ch[root][1];
        fa[root]=0; clear(cur);
        return;
    }
    if (!ch[root][1]){
        int cur=root; root=ch[root][0];
        fa[root]=0; clear(cur);
        return;
    }
    int cur=root,x=prenumber();
    splay(x,0);
    fa[ch[cur][1]]=x;
    ch[x][1]=ch[cur][1];
    clear(cur); maintain(root);
}