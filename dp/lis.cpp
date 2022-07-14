for (int i=1;i<=n;++i){ //最长上升子序列（严格）
    if (!cnt||a[i]>d[cnt]){
        d[++cnt]=a[i];
    }else{
        int p=lower_bound(d+1,d+1+cnt,a[i])-d;
        d[p]=a[i];
    }
}
for (int i=1;i<=n;++i){ //最长不下降子序列
    if (!cnt||a[i]>=d[cnt]){
        d[++cnt]=a[i];
    }else{
        int p=upper_bound(d+1,d+1+cnt,a[i])-d;
        d[p]=a[i];
    }
}
for (int i=1;i<=n;++i){ //最长不上升子序列
    if (!cnt||a[i]<=d[cnt]){
        d[++cnt]=a[i];
    }else{
        int p=upper_bound(d+1,d+1+cnt,a[i],greater<int>())-d;
        d[p]=a[i];
    }
}