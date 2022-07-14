ll calc(int x,int y){
    ll tmp=0;
    int mx=min(x,y)/k;
    //if k>min(x,y)/k then F(k)=(x/(k*d))*(y/(k*d))=0
    for (int l=1,r;l<=mx;l=r+1){
        r=min(x/(x/l),y/(y/l)); 
        //if there is only x then x/(x/l)
        tmp+=(ll)(x/(l*k))*(ll)(y/(l*k))*(sum[r]-sum[l-1]);
    }
    return tmp;
}