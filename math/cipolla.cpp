namespace cipolla{
    ll I2;
    struct cp{
        ll rel,img;
        cp(ll _r=0,ll _i=0):rel(_r),img(_i){}
        bool operator == (cp _a){
            return rel==_a.rel&&img==_a.img;
        }
        cp operator * (cp _a){
            return cp((rel*_a.rel+I2*img%mod*_a.img)%mod,
                      (img*_a.rel+rel*_a.img)%mod);
        }
    };
    cp ksm(cp x,ll k){
        cp res(1,0);
        while (k){
            if (k&1) res=res*x;
            x=x*x; k>>=1;
        }
        return res;
    }
    ll ksm(ll x,ll k){
        ll res=1;
        while (k){
            if (k&1) res=res*x%mod;
            x=x*x%mod; k>>=1;
        }
        return res;
    }
    bool check(int x){
        return ksm(cp(x,0),(mod-1)>>1)==cp(1,0);
    }
    ll solve(ll n){
        if (!n) return 0; //special judge 0
        if (ksm(n,(mod-1)>>1)==mod-1) return -1; //no answer
        ll tmp=rand()%mod;
        while (!tmp||check((tmp*tmp-n+mod)%mod)){
            tmp=rand()%mod;
        }
        I2=(tmp*tmp-n+mod)%mod;
        return ksm(cp(tmp,1),(mod+1)>>1).rel;
    }
}