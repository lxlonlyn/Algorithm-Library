for (i=1,k=0;i<=n;++i){
    if (k) --k;
    while (s[i+k]==s[sa[rk[i]-1]+k]) ++k;
    ht[rk[i]]=k;
}