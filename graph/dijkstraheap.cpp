struct line{
    int to,v;
};
vector<line> edge;
vector<int> G[maxn];
struct node{
    int pos,dis;
    bool operator < (const node _a)const{
        return dis>_a.dis;
    }
};
priority_queue<node> q;
int dis[maxn];
bool vis[maxn];
void addedge(int from,int to,int val){
    edge.push_back((line){to,val});
    int m=edge.size();
    G[from].push_back(m-1);
}
void dij(){
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    q.push((node){s,0});
    while (!q.empty()){
        node u=q.top();
        q.pop();
        int now=u.pos,val=u.dis;
        if (!vis[now]){
            vis[now]=true;
            for (int i=0;i<G[now].size();++i){
                int to=edge[G[now][i]].to;
                int va=edge[G[now][i]].v;
                if (dis[to]>dis[now]+va){
                    dis[to]=dis[now]+va;
                    q.push((node){to,dis[to]});
                }
            }
        }
    }
}