ll liner(ll a,ll b,ll c){ //ax=c(mod b)
    ll x,y;
    ll d=exgcd(a,b,x,y);
    if (c%d) return -1; //there is no answer
    x*=c/d; ll t=b/d;
    return (x%t+t)%t; //the minest positive answer
}