const ll base=131;
const ll mod=1610612741;//or 1e9+7
//do hash
for (rg int i=1;i<=n;++i){
    s[i]=read(); 
    hs[i]=(hs[i-1]*base+s[i])%mod;
}
//get hash
il ll geth(un ll a[],int l,int r){
    return ((a[r]-a[l-1]*p[r-l+1])%mod+mod)%mod;
}