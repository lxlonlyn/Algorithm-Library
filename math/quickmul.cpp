ll step_mul(ll aa,ll bb,ll mod){
    ll tmp=0;
    while (bb){
        if (bb&1) tmp=(tmp+aa)%mod;
        aa=(aa+aa)%mod; bb>>=1;
    }
    return tmp%mod;
}