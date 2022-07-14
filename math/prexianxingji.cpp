void InsertNode(int x){
    ++n; a[n]=a[n-1]; int pos=n;
    for (int i=31;i>=0;--i){
        if (!(x>>i)) continue;
        if (!a[n].d[i]){
            a[n].d[i]=x;
            a[n].p[i]=pos;
            break;
        }
        if (a[n].p[i]<pos){
            swap(a[n].p[i],pos);
            swap(a[n].d[i],x);
        }
        x^=a[n].d[i];
    }
}
int QueryAns(int ql,int qr){
    int res=0;
    for (int i=31;i>=0;--i){
        if (a[qr].p[i]>=ql){
            res=max(res,res^a[qr].d[i]);
        }
    }
    return res;
}