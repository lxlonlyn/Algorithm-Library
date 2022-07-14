void linear_basis(){
    for (int i=1;i<=n;++i){ //every number
        for (int j=60;j>=0;--j){ //every bit
            if (!(a[i]>>j)) continue;
            if (!d[j]){
                d[j]=a[i]; break; //break!
            }
            a[i]^=d[j];
        } 
    }
}
//example:find the maxnum xor sum
ll ans=0;
for (int j=60;j>=0;--j){
    if (ans^d[j]>ans) ans^=d[j];
}
//example:find out how many different numbers can be xor to
ll ans=1;
for (int j=0;j<=60;++j){
    if (d[j]) ans<<=1;
    ans%=mod; //if needed
}