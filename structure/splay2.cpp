struct treenode{
    int ch[2],fa;
    int val,sz;
    int cnt; 
}splay[maxn];
int root,tot;
void splay_maintain(int x){
    splay[x].sz=splay[splay[x].ch[0]].sz
               +splay[splay[x].ch[1]].sz
               +splay[x].cnt;
}
int splay_getchild(int x){
    return x==splay[splay[x].fa].ch[1];
}
void splay_clear(int x){
    splay[x].ch[0]=splay[x].ch[1]=splay[x].fa=0;
    splay[x].val=splay[x].sz=0;
    splay[x].cnt=0;
}
void splay_rotate(int x){
    int y=splay[x].fa,z=splay[y].fa,chk=splay_getchild(x);
    splay[y].ch[chk]=splay[x].ch[chk^1];
    splay[splay[x].ch[chk^1]].fa=y;
    splay[x].ch[chk^1]=y;
    splay[y].fa=x; splay[x].fa=z;
    if (z) splay[z].ch[y==splay[z].ch[1]]=x;
    splay_maintain(x); splay_maintain(y);
}
void splay_splay(int x,int goal){
    for (int f;(f=splay[x].fa)!=goal;splay_rotate(x)){
        if (splay[f].fa!=goal) 
            splay_rotate(splay_getchild(x)==splay_getchild(f)?f:x);
    }
    if (!goal) root=x;
}
void splay_insert(int k){
    if (!root){
        splay[++tot].val=k; splay[tot].cnt++;
        root=tot; splay_maintain(root);
        return;
    }
    int cur=root,f=0;
    while (1){
        if (splay[cur].val==k){
            splay[cur].cnt++;
            splay_maintain(cur); splay_maintain(f);
            splay_splay(cur,0);
            break; 
        }
        f=cur; cur=splay[cur].ch[splay[cur].val<k];
        if (!cur){
            splay[++tot].val=k; splay[tot].cnt++;
            splay[tot].fa=f; splay[f].ch[splay[f].val<k]=tot;
            splay_maintain(tot); splay_maintain(f);
            splay_splay(tot,0); break;
        } 
    }
}
int splay_findrank(int k){  
    int res=0,cur=root;
    while (1){
        if (k<splay[cur].val){
            cur=splay[cur].ch[0];
        }else{
            res+=splay[splay[cur].ch[0]].sz;
            if (k==splay[cur].val){
                splay_splay(cur,0); return res+1;
            }
            res+=splay[cur].cnt;
            cur=splay[cur].ch[1];
        }
    }
}
int splay_findvalue(int k){ 
    int cur=root;
    while (1){
        if (splay[cur].ch[0]&&k<=splay[splay[cur].ch[0]].sz){
            cur=splay[cur].ch[0];
        }else{
            k-=splay[cur].cnt+splay[splay[cur].ch[0]].sz;
            if (k<=0) return splay[cur].val;
            /*
            this just return the value
            if want's the id in splay just return cur
            */
            cur=splay[cur].ch[1];
        }
    }
}
int splay_prenumber(){ 
    int cur=splay[root].ch[0];
    while (splay[cur].ch[1]) cur=splay[cur].ch[1];
    return cur;
}
int splay_nxtnumber(){ 
    int cur=splay[root].ch[1];
    while (splay[cur].ch[0]) cur=splay[cur].ch[0];
    return cur;
}
void splay_delete(int k){ 
    splay_findrank(k);
    if (splay[root].cnt>1){
        splay[root].cnt--; splay_maintain(root);
        return;
    }
    if (!splay[root].ch[0]&&!splay[root].ch[1]){
        splay_clear(root); root=0;
        return;
    }
    if (!splay[root].ch[0]){
        int cur=root; root=splay[root].ch[1];
        splay[root].fa=0; splay_clear(cur);
        return;
    }
    if (!splay[root].ch[1]){
        int cur=root; root=splay[root].ch[0];
        splay[root].fa=0; splay_clear(cur);
        return;
    }
    int cur=root,x=splay_prenumber();
    splay_splay(x,0);
    splay[splay[cur].ch[1]].fa=x;
    splay[x].ch[1]=splay[cur].ch[1];
    splay_clear(cur); splay_maintain(root);
}
//operations:
switch (opt){
    //add a point val x
    case 1:splay_insert(x); break; 
    //delete a point val x
    case 2:splay_delete(x); break;
    //return point's min rank which value is x
    case 3:printf("%d\n",splay_findrank(x)); break;
    //return point's value whick rank is x
    case 4:printf("%d\n",splay_findvalue(x)); break;
    //return x's prenumber
    case 5:
        splay_insert(x);
        printf("%d\n",splay[splay_prenumber()].val);
        splay_delete(x);
        break;
    //retunr x's nxtnumber
    case 6:
        splay_insert(x);
        printf("%d\n",splay[splay_nxtnumber()].val);
        splay_delete(x);
        break;
}