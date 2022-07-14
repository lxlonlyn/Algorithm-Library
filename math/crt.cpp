ll a[maxn],m[maxn];
ll crt(){ //x=a[](mod m[])
    ll ans=0,M=1;
    for (int i=1;i<=n;++i) M*=m[i];
    for (int i=1;i<=n;++i){
        ll x,y,Mi=M/m[i];
        exgcd(Mi,m[i],x,y); //attention this is Mi not M
        ans=(ans+Mi*x*a[i])%M;
        //ans=(ans+step_mul(Mi*x,a[i],M))%M;
        //this is safe,but it's very slow
    }   
    if (ans<0) ans+=M;
    return ans;
} 