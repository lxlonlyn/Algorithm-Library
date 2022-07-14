vector<int> InvContor(int bits,int num){
    num--;
    vector<bool> vis(bits+1,false);
    vector<int> p(bits,-1);
    int n,r=num;
    for (int i=0;i<bits;++i){
        n=r/(fact[bits-i-1]);
        r=r%(fact[bits-i-1]);
        for (int j=1;j<=bits;++j){
            if (!vis[j]&&!(n--)){
                vis[j]=true;
                p[i]=j;
                break;
            }
        }
    }
    return p;
}