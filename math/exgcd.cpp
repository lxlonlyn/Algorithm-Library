#define ll long long 
ll exgcd(ll a,ll b,ll &x,ll &y){ //ax+by=c->ax=c(mod b)
    if (!b){
        x=1; y=0; return a;
    }
    ll d=exgcd(b,a%b,x,y);
    ll tmp=x; x=y; y=tmp-a/b*y;
    return d;
}