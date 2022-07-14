int prime[maxn],tot;
bool notprime[maxn];
int mu[maxn],sum[maxn];
void get_mu(){ //get mu and sum of mu
    notprime[1]=true; mu[1]=1;
    for (int i=2;i<=50000;++i){
        if (!notprime[i]){
            prime[++tot]=i;
            mu[i]=-1;
        }
        for (int j=1;j<=tot&&i*prime[j]<=50000;++j){
            notprime[i*prime[j]]=true;
            if (i%prime[j]==0) break;
            else mu[i*prime[j]]=-mu[i];
        }
    }
    for (int i=1;i<=50000;++i){
        sum[i]=sum[i-1]+mu[i];
    }
}