ll Comp(ll a,ll b,ll p){ 
    if (a<b) return 0;
    if (a==b) return 1;
    if (b>a-b) b=a-b;
    ll ans=1,ca=1,cb=1;
    for (int i=0;i<b;++i){
        ca=ca*(a-i)%p;
        cb=cb*(b-i)%p;
    }
    ans=ca*ksm(cb,p-2)%p; 
    return ans;
}
ll lucas(ll n,ll m,ll p){
    if (!m) return 1;
    return (Comp(n%p,m%p,p)*lucas(n/p,m/p,p))%p;
}