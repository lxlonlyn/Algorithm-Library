#define mod 998244353
#define g 3
ll ksm(ll x,int k){
    ll res=1;
    while (k){
        if (k&1) res=(res*x)%mod;
        x=(x*x)%mod; k>>=1;
    }
    return res%mod;
}
void ntt(ll *a,int len,int inv)
{
    for (int i=0;i<len;++i){
        if (i<rev[i]) swap(a[i],a[rev[i]]);
    }
    for (int mid=1;mid<len;mid<<=1){
        ll tmp=ksm((inv==1)?g:ksm(g,mod-2),(mod-1)/(mid*2));
        for (int i=0;i<len;i+=mid<<1){
            ll omega=1;
            for (int j=0;j<mid;++j,omega=omega*tmp%mod){
                ll x=a[i+j],y=omega*a[i+j+mid]%mod;
                a[i+j]=(x+y)%mod; a[i+j+mid]=(x-y+mod)%mod; 
            }
        }
    }
}
void work(){ 
    limits=1; lim=0;
    while (limits<=m+n) limits<<=1,++lim;
    for (int i=0;i<limits;++i){
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(lim-1));
    }
    ntt(aa,limits,1); ntt(bb,limits,1);
    for (int i=0;i<=limits;++i){
        aa[i]=(aa[i]*bb[i])%mod;
    }
    ntt(aa,limits,-1);
    ll inv=ksm(limits,mod-2);
    for (int i=0;i<=n+m;++i){
        printf("%lld ",aa[i]*inv%mod);
    }
    //final ans is aa[i]*inv%mod
}