#define cp complex_number
const double PI = acos(-1);
struct complex_number{
    double rel,img;
    complex_number(double x=0,double y=0){
        rel=x; img=y;
    }
};
cp operator + (cp a,cp b){
    return cp(a.rel+b.rel,a.img+b.img);
}
cp operator - (cp a,cp b){
    return cp(a.rel-b.rel,a.img-b.img);
}
cp operator * (cp a,cp b){
    return cp(a.rel*b.rel-a.img*b.img,a.rel*b.img+b.rel*a.img);
}
void fft(cp *a,int len,int inv) 
{
    for (int i=0;i<len;++i){
        if (i<rev[i]) swap(a[i],a[rev[i]]);
    }
    for (int mid=1;mid<len;mid<<=1){
        cp tmp=cp(cos(PI/mid),inv*sin(PI/mid));
        for (int i=0;i<len;i+=mid<<1){
            cp omega=cp(1,0);
            for (int j=0;j<mid;++j,omega=omega*tmp){
                cp x=a[i+j],y=omega*a[i+j+mid];
                a[i+j]=x+y; a[i+j+mid]=x-y; 
            }
        }
    }
}
//proceduce:
int limits=1,m,n,lim; 
/*
limits=2^lim,ans's finally length
*/
cp aa[maxn],bb[maxn]; 
int rev[maxn];
void work(){ 
    limits=1; lim=0;
    while (limits<=m+n) limits<<=1,++lim;
    for (int i=0;i<=n;++i) aa[i].rel=read();
    for (int i=0;i<=m;++i) bb[i].rel=read();
    for (int i=0;i<limits;++i){
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(lim-1));
    }//transfer to position 
    fft(aa,limits,1); fft(bb,limits,1);
    for (int i=0;i<=limits;++i){
        aa[i]=aa[i]*bb[i];
    }
    fft(aa,limits,-1);
    for (int i=0;i<=n+m;++i){
        printf("%d ",(int)(aa[i].rel/limits+0.5)); 
    }
} 