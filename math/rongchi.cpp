ll ans,a[21],n;
int m;
void dfs(ll val,int pos,int f){
    if (val>n) return;
    if (pos>m){
        ans+=n/val*f;
        return;
    }
    dfs(val,pos+1,f);
    dfs(val/gcd(val,a[pos])*a[pos],pos+1,-f);
}