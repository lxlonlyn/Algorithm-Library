#define I_int int 
inline I_int read(){
  I_int x=0,f=1; char c=getchar();
  while(c<'0'||c>'9') {if(c=='-') f=-1; c=getchar();} 
  while(c>='0'&&c<='9') {x=x*10+c-'0'; c=getchar();} 
  return x*f;
}
char F[200];
inline void write(I_int x){
  I_int tmp=x>0?x:-x;
  if(x<0) putchar('-');
  int cnt=0;
  while(tmp>0){
     F[cnt++]=tmp%10+'0';
     tmp/=10;
  }
    while(cnt>0) putchar(F[--cnt]);
}
#undef I_int