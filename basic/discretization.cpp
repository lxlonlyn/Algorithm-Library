// int a[],b[]
// a[1..n]->b[1..n]
sort(a+1,a+1+n);
len=unique(a+1,a+n+1)-a-1;
b[i]=lower_bound(a+1,a+len+1,x)-a;
// vector<int> a,b
sort(a.begin(),a.end());
a.erase(unique(a.begin(),a.end()),a.end());
for (int i=0;i<n;++i){
    b[i] = std::lower_bound(a.begin(), a.end(), b[i]) - a.begin();
}