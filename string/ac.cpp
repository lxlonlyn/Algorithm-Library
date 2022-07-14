struct AC_automaton{
    int trie[75*160][26],tot;
    int fail[75*160];
    int mp[75*160],cnt[160];
    //mp:trie->origin string
    //additional operation
    int endword[maxn]; //how many times
    //additional operation
    void init(){
        memset(trie,0,sizeof(trie)); tot=0;
        memset(fail,0,sizeof(fail));
        memset(cnt,0,sizeof(cnt));
        memset(mp,0,sizeof(mp));
    }
    void insert(char *s,int id){
        int u=0;
        for (int i=1;s[i];++i){
            if (!trie[u][s[i]-'a']) trie[u][s[i]-'a']=++tot;
            u=trie[u][s[i]-'a'];
        }
        mp[u]=id; //addational:endword[u]++;
    }
    void build(){
        queue<int> q;
        for (int i=0;i<26;++i){
            if (trie[0][i]) q.push(trie[0][i]);
        }
        while (!q.empty()){
            int u=q.front(); q.pop();
            for (int i=0;i<26;++i){
                if (trie[u][i]){
                    fail[trie[u][i]]=trie[fail[u]][i]; 
                    q.push(trie[u][i]);
                }else{
                    trie[u][i]=trie[fail[u]][i];
                }
            }
        }
    }
    int query(char *s){
        int u=0,ans=0;
        for (int i=1;s[i];++i){
            u=trie[u][s[i]-'a'];
            for (int j=u;j;j=fail[j]){
                if (mp[j]){
                    cnt[mp[j]]++; ans=max(ans,cnt[mp[j]]);
                }
                //additional:
                ans+=endword[j]; endword[j]=-1;
                //attention:in for judge:j&endword[j]!=-1
            }
        }
        return ans;
    }
}AC;