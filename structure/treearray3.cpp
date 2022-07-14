void add(int x,int y,int z){ //add z to (x,y)
    int memo_y=y;
    while(x<=n){
        y=memo_y;
        while(y<=n)
            tree[x][y]+=z,y+=y&-y;
        x+=x&-x;
    }
}
void ask(int x,int y){ //calc sum of (1,1) to (x,y)
    int res=0,memo_y=y;
    while(x){
        y=memo_y;
        while(y)
            res+=tree[x][y],y-=y&-y;
        x-=x&-x;
    }
}