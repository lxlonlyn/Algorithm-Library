void prim(int u){
    int sum_mst = 0;
    for(int i = 1; i <= n; i++){ //initial
        lowcost[i] = Map[u][i];
        mst[i] = u;
    }
    mst[u] = -1;
    for(int i = 1; i < n; i++){
        int minn = INF;
        int v = -1;
        //find the minest mst in lowcost
        for(int j = 1; j <= n; j++){
            if(mst[j] != -1 && lowcost[j] < minn){
                v = j; minn = lowcost[j];
            }
        }
        if(v != -1){
            printf("%d %d %d\n", mst[v], v, lowcost[v]);
            //output path
            mst[v] = -1;
            sum_mst += lowcost[v];
            for(int j = 1; j <= n; j++){
                if(mst[j] != -1 && lowcost[j] > Map[v][j]){
                    lowcost[j] = Map[v][j];
                    mst[j] = v;
                }
            }
        }
    }
    printf("weight of mst is %d\n", sum_mst);
}