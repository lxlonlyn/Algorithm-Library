unordered_map<ll,ll> mp; //if use map then add a log
ll bsgs(ll a,ll b){ //a^x=b(%p)
    if (!a){
        if (!b) return 0;
        else if (b==1) return 0;
        else return -1;
    }
    mp.clear();
    if (b==1) return 0;
    ll ans=-1,m=sqrt(p)+1,s=b;
    for (ll i=0;i<m;++i){
        mp[s]=i; s=s*a%p;
    }
    ll tmp=ksm(a,m); s=1; 
    for (ll i=1;i<=m+1;++i){
        s=s*tmp%p;
        if (mp.count(s)){
            ans=i*m-mp[s];
            break;
        }
    }
    return ans;
}