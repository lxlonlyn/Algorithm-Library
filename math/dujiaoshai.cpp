int T; ll n;
int limit;
int prime[maxn],tot;
int notprime[maxn];
int mu[maxn],phi[maxn];
ll sum_mu[maxn],sum_phi[maxn];
void linear_sieve(){
    phi[1]=mu[1]=1; notprime[1]=1;
    for (int i=2;i<=limit;++i){
        if (!notprime[i]){
            prime[++tot]=i;
            mu[i]=-1; phi[i]=i-1;
        }
        for (int j=1;j<=tot&&i*prime[j]<=limit;++j){
            notprime[i*prime[j]]=1;
            if (!(i%prime[j])){
                phi[i*prime[j]]=phi[i]*prime[j];
                break;
            }else{
                phi[i*prime[j]]=phi[i]*(prime[j]-1);
                mu[i*prime[j]]=-mu[i];
            }
        }
    }
    for (int i=1;i<=limit;++i){
        sum_mu[i]=sum_mu[i-1]+mu[i];
        sum_phi[i]=sum_phi[i-1]+phi[i];
    }
}
unordered_map<ll,ll> map_mu;
unordered_map<ll,ll> map_phi;
ll askmu(ll x){
    if (x<=limit) return sum_mu[x];
    if (map_mu[x]) return map_mu[x];
    ll ans=1;
    for (ll l=2,r;l>=0&&l<=x;l=r+1){
        r=x/(x/l); 
        ans-=(r-l+1)*askmu(x/l);
    }
    return map_mu[x]=ans;
}
ll askphi(ll x){
    if (x<=limit) return sum_phi[x];
    if (map_phi[x]) return map_phi[x];
    ll ans=(x*(x+1))>>1;
    for (ll l=2,r;l<=x;l=r+1){
        r=x/(x/l);
        ans-=(r-l+1)*askphi(x/l);
    }
    return map_phi[x]=ans;
}
int main(){
    scanf("%d",&T);
    limit=(int)(pow(2147483647,0.6666666666667));
    linear_sieve();
    while (T--){
        scanf("%lld",&n);
        printf("%lld %lld\n",askphi(n),askmu(n));
    }
    return 0;
}