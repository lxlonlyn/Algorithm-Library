int n,a[maxn];
ll jc[maxn];
int tree[maxn];
void AddValue(int x,int k){
    while (x<=n){
        tree[x]+=k;
        x+=x&-x;
    }
}
int QueryPrefixSum(int x){
    int res=0;
    while (x){
        res+=tree[x];
        x-=x&-x;
    }
    return res;
}
void CantorExpansion(int a[]){
    jc[0]=1; ll rank=0;
    for (int i=1;i<=n;++i){
        jc[i]=jc[i-1]*i%mod; AddValue(i,1);
    }
    for (int i=1;i<=n;++i){
        rank=(rank+jc[n-i]*(QueryPrefixSum(a[i])-1))%mod;
        AddValue(a[i],-1);
    }
    printf("%lld\n",(rank+1)%mod);
}