const double eps=1e-9;
double abss(double x){
    return (x<0)?-x:x;
} 
int check(){ 
    for (int i=1;i<=n;++i){
        int tot=0;
        for (int j=1;j<=n;++j){
            if (!a[i][j]) tot++;
        }
        if (tot==n&&abs(a[i][n+1])>eps) noans=true; 
        if (tot==n&&abs(a[i][n+1])<=eps) manyans=true;
    }
    if (noans) return -1; 
    if (manyans) return 0;
    return 1;
    /*
    -1:no answer,0:infinity answer,1:only one answer.
    judge no answer before infinity answer
    */
}
void gauss(){
    for (int i=1;i<=n;++i){
        int r=i;
        for (int j=i+1;j<=n;++j){
            if (abss(a[j][i])>abss(a[r][i])) r=j;
        }
        if (r!=i) swap(a[r],a[i]);
        if (abss(a[i][i])<=eps) continue;
        for (int j=1;j<=n;++j){
            if (i==j) continue;
            double tmp=a[j][i]/a[i][i];
            for (int k=1;k<=n+1;++k){
                a[j][k]-=tmp*a[i][k];
            }
        }
    }
    int flag=check();
    if (flag==-1){ //no answer
        printf("-1"); return;
    }
    if (flag==0){ //infinity answer
        printf("0"); return;
    }
    for (int i=n;i>=1;--i){
        a[i][n+1]/=a[i][i];
    }
    for (int i=1;i<=n;++i){
        printf("x%d=",i);
        if (abss(a[i][n+1])<=eps) printf("0\n");
        else printf("%.2lf\n",a[i][n+1]);
    }
}