int n; char s[maxn]; //start from 1
int sa[maxn],rk[maxn];
int oldrk[maxn<<1],id[maxn],px[maxn],cnt[maxn];
bool cmp(int x,int y,int w){
    return (oldrk[x]==oldrk[y]&&oldrk[x+w]==oldrk[y+w]);
}
void get_sa(){
    int m=300,p;
    for (int i=1;i<=n;++i) ++cnt[rk[i]=s[i]];
    for (int i=1;i<=m;++i) cnt[i]+=cnt[i-1];
    for (int i=n;i>=1;--i) sa[cnt[rk[i]]--]=i;
    for (int w=1;w<n;w<<=1,m=p){
        p=0;
        for (int i=n;i>n-w;--i) id[++p]=i;
        for (int i=1;i<=n;++i){
            if (sa[i]>w) id[++p]=sa[i]-w;
        }
        memset(cnt,0,sizeof(cnt));
        for (int i=1;i<=n;++i) ++cnt[px[i]=rk[id[i]]];
        for (int i=1;i<=m;++i) cnt[i]+=cnt[i-1];
        for (int i=n;i>=1;--i) sa[cnt[px[i]]--]=id[i];
        memcpy(oldrk,rk,sizeof(rk));
        p=0;
        for (int i=1;i<=n;++i){
            rk[sa[i]]=cmp(sa[i],sa[i-1],w)?p:++p;
        }
    }
}