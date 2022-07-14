int in_queue[maxn];
int dis[maxn];
void spfa(){
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    queue<int> q;
    q.push(s); in_queue[s]=1;
    while (!q.empty()){
        int u=q.front(); q.pop();
        in_queue[u]=0;
        for (int i=0;i<G[u].size();++i){
            line e=edge[G[u][i]];
            if (dis[u]+e.v<dis[e.to]){
                dis[e.to]=dis[u]+e.v;
                if (!in_queue[e.to]){
                    q.push(e.to); in_queue[e.to]=1;
                }
            }
        }
    }
}
//program below has been added slf
//considering deque is slow,so set apart
void spfa(){
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0; in_queue[s]=1;
    deque<int> q; q.push_back(s);
    while (!q.empty()){
        int u=q.front(); q.pop_front();
        in_queue[u]=0;
        for (int i=0;i<G[u].size();++i){
            line e=edge[G[u][i]];
            if (dis[u]+e.v<dis[e.to]){ 
                dis[e.to]=dis[u]+e.v;
                if (!in_queue[e.to]){
                    in_queue[e.to]=1;
                    if (q.empty()||dis[e.to]>dis[q.front()]) q.push_back(e.to);
                    else q.push_front(e.to);
                }
            }
        }
    }
}