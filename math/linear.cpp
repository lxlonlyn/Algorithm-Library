//phi and prime
int prime[maxn],phi[maxn];
int notprime[maxn];
int tot;
void init(){
    notprime[1]=1;
    for (int i=2;i<=maxn;++i){
        if (!notprime[i]){
            prime[++tot]=i;
            phi[i]=i-1;
        }
        for (int j=1;j<=tot&&i*prime[j]<=maxn;++j){
            notprime[i*prime[j]]=1;
            if (!(i%prime[j])){
                phi[i*prime[j]]=phi[i]*prime[j];
                break; 
            }else{
                phi[i*prime[j]]=phi[i]*(prime[j]-1);
            }
        }
    }
} 
/*
calulate how many divisors are there in n
example:d[6]=4
*/
int notprime[maxn];
int prime[maxn],d[maxn],num[maxn];
//num[i]:the minest prime divisor
int tot;
void init(){
    cnt=0;
    d[1]=1;
    for (int i=2;i<=maxn;++i){
        if (!notprime[i]){
            prime[++tot]=i; num[i]=1;
            d[i]=2;
        }
        for (int j=1;j<=tot&&i*prim[j]<=maxn;++j){
            notprime[i*prime[j]]=1;
            if (!(i%prim[j])){
                num[i*prime[j]]=num[i]+1;
                d[i*prime[j]]=d[i]/(num[i]+1)*(num[i*prime[j]]+1);
                break;
            }
            d[i*prime[j]]=d[i]*d[prime[j]];
            num[i*prime[j]]=1;
        }
    }
}
/*
calculate the sum of divisor of n
example:sd[6]=1+2+3+6=12
*/
int notprime[maxn];
int prime[maxn];
long long sd[N],sp[N];
int tot;
void init(){
    cnt=0; sd[1]=1;
    for (int i=2;i<=maxn;++i){
        if (!notprime[i]){
            prim[++tot]=i; sd[i]=i+1; sp[i]=i+1;
        }
        for (int j=0;j<cnt&&i*prime[j]<=maxn;++j){
            mark[i*prime[j]]=1;
            if (!(i%prime[j])){
                sp[i*prime[j]]=sp[i]*prime[j]+1;
                sd[i*prime[j]]=sd[i]/sp[i]*sp[i*prime[j]];
                break;
            }
            sd[i*prime[j]]=sd[i]*sd[prime[j]];
            sp[i*prime[j]]=1+prime[j];
        }
    }
}