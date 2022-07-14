int s[maxn],sv[maxn]; 
/*
s[]: prefix product
sv[]: inverse of s[]
*/
int inv[maxn]; 
s[0]=1;
for (int i=1;i<=n;++i) s[i]=s[i-1]*a[i]%p;
sv[n]=ksm(s[n],p-2); 
for (int i=n;i>=1;--i) inv[i-1]=inv[i]*a[i]%p;
for (int i=1;i<=n;++i) inv[i]=sv[i]*s[i-1]%p;