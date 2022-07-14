ll f[maxn][2333][2][2]; //pos sum limit zero
ll a[maxn],len;
ll dfs(ll len,ll sum,ll limit,ll zero,ll x){
    if (!len) return sum;
    if (f[len][sum][limit][zero]!=-1){
        return f[len][sum][limit][zero];
    }
    ll n=limit?a[len]:9;
    ll t=0;
    for (ll i=0;i<=n;++i){
        t+=dfs(len-1,sum+((i==x)&&(!zero||i)),
               limit&&(i==n),zero&&(!i),x);
    }
    f[len][sum][limit][zero]=t;
    return t;
}
ll solve(ll n,ll x){
    memset(a,0,sizeof(a));
    len=0;
    while (n){
        a[++len]=n%10;
        n/=10;
    }
    memset(f,-1,sizeof(f));
    return dfs(len,0,1,1,x);
}