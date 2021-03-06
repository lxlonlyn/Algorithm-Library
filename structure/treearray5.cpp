ll t1[N][N],t2[N][N],t3[N][N],t4[N][N];
void add(ll x,ll y,ll z){
    for(int X=x;X<=n;X+=X&-X)
        for(int Y=y; Y<=m;Y+=Y&-Y){
            t1[X][Y]+=z;
            t2[X][Y]+=z*x;
            t3[X][Y]+=z*y;
            t4[X][Y]+=z*x*y;
        }
}
ll ask(ll x,ll y){
    ll res=0;
    for(int i=x;i;i-=i&-i)
        for(int j=y;j;j-=j&-j)
            res+=(x+1)*(y+1)*t1[i][j]
               -(y+1)*t2[i][j]
               -(x+1)*t3[i][j]
               +t4[i][j];
    return res;
}
ll range_ask(ll xa,ll ya,ll xb,ll yb){
    return ask(xb,yb)-ask(xb,ya-1)
          -ask(xa-1,yb)+ask(xa-1,ya-1);
}