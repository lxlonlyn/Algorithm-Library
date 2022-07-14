void add(int x,int y,int z){ 
    int memo_y=y;
    while(x<=n){
        y=memo_y;
        while(y<=n)
            tree[x][y]+= z,y+=y&-y;
        x+=x&-x;
    }
}
void range_add(int xa,int ya,int xb,int yb,int z){
    add(xa,ya,z);
    add(xa,yb+1,-z);
    add(xb+1,ya,-z);
    add(xb+1,yb+1,z);
}
void ask(int x,int y){
    int res=0,memo_y=y;
    while(x){
        y=memo_y;
        while(y)
            res+=tree[x][y],y-=y&-y;
        x-=x&-x;
    }
}