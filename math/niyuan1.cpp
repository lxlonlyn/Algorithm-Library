int inv[maxn];
inv[1]=1;
for (int i=2;i<p;++i){
    inv[i]=(p-p/i)*inv[p%i]%p;
}