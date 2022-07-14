LL Lagrange(LL f[],int n,int k){                   
    if(k <= n) return f[k];
    per[0] = suf[n+1] = 1;
    for(int i = 0;i <= n; ++i) per[i+1] = per[i]*(k-i)%mod;
    for(int i = n;i >= 0; --i) suf[i] = suf[i+1]*(k-i)%mod;
    LL fk = 0;
    for(int i = 0;i <= n; ++i){
        LL tep = f[i]*per[i]%mod*suf[i+1]%mod*fac[i]%mod*fac[n-i]%mod;
        if((n-i)&1) fk = (fk-tep+mod)%mod;
        else fk = (fk+tep)%mod; 
    }
    return fk;
}