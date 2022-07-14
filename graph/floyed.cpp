int f[maxn][maxn];
memset(f,0x3f,sizeof(f));
for (int i=1;i<=n;++i) f[i][i]=0; //按需
for (int k=1;k<=n;++k){
    for (int i=1;i<=n;++i){
        for (int j=1;j<=n;++j){
            f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
        }
    }
}