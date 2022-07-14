struct line{
    int from,to,val;
    bool operator < (const line _a){
        return val<_a.val;
    }
};
vector<line> edge;
int fa[maxn];
int find_father(int x){
    return (x==fa[x])?x:fa[x]=find_father(fa[x]);
}
bool addcheck(int x,int y,int v){
    int fx=find_father(x),fy=find_father(y);
    if (fx==fy){
        return false;
    }else{
        fa[fx]=fy;
        return true;
    }
}
void work(){
    sort(edge.begin(),edge.end());
    int tot=0;
    for (int i=0;i<edge.size();++i){
        line e=edge[i];
        if (addcheck(e.from,e.to,e.val)) ++tot;
        if (tot==n-1) break;
    }
}