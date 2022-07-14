ll excrt(){
    ll M=m[1],ans=a[1];
    for (int i=2;i<=n;++i){ 
        ll tmpa=M,tmpb=m[i],tmpc;
        tmpc=(a[i]-ans%tmpb+tmpb)%tmpb;
        ll x,y;
        ll d=exgcd(tmpa,tmpb,x,y);
        if (tmpc%d) return -1; //there is no answer
        x=(x*tmpc/d)%(tmpb/d);
        //x=step_mul(x,tmpc/d,tmpb/d); 
        //also safe but slow
        ans+=x*M; M*=tmpb/d; ans=(ans%M+M)%M;
    }
    return (ans%M+M)%M;
}