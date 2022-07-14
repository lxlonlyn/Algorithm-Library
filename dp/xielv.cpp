ll st[maxn],sc[maxn],dp[maxn];
int Q[maxn],head=1,tail=0;
il ll X(int j){return sc[j];}
il ll Y(int j){return dp[j];}
il long double K(int i,int j){
    if (X(i)==X(j)){
        if (Y(j)>=Y(i)) return 1e18;
        else return -1e18;
    }else{
        return (long double)(Y(j)-Y(i))/(X(j)-X(i));
    }
}
int check(int k){
    if (head==tail) return Q[head];
    int l=head,r=tail,mid;
    while (l<r){
        mid=(l+r)>>1;
        if (K(Q[mid],Q[mid+1])<k) l=mid+1;
        else r=mid;
    }
    return Q[l];
}
void work(){
    Q[++tail]=0;
    for (int i=1;i<=n;++i){
        int j=check(s+st[i]);
        dp[i]=dp[j]+st[i]*(sc[i]-sc[j])+s*(sc[n]-sc[j]);
        while (head<tail&&
               K(Q[tail-1],Q[tail])>=K(Q[tail-1],i)) --tail;
        Q[++tail]=i;
    }
}