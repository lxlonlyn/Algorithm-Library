for (int i=1;i<=n;++i){
    f[i][i][1]=0;
}
for (int len=1;len<=n;++len){
    for (int i=1;i<=n;++i){
        int j=i+len-1;
        for (int k=len;k>=1;--k){
            if (k==1){
                for (int tmp=l;tmp<=r;++tmp){
                    f[i][j][k]=
                        min(f[i][j][k],f[i][j][tmp]+sum[j]-sum[i-1]);
                }
            }else{
                for (int tmp=i;tmp<j;++tmp){
                    f[i][j][k]=
                        min(f[i][j][k],f[i][tmp][1]+f[tmp+1][j][k-1]);
                }
            }
        }
    }
}