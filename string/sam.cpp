namespace SAM{
    struct state{
        int mxlen,link;
        map<char,int> nxt;
    }st[maxn<<1];
    bool vis[maxn<<1];
    int ind[maxn<<1];
    int cnt[maxn<<1];
    int sz,lst;
    void init(){
        st[0].mxlen=0;
        st[0].link=-1;
        ++sz; lst=0;
    }
    void extend(char c){
        int cur=sz++,p=lst; vis[cur]=true;
        st[cur].mxlen=st[lst].mxlen+1;
        while (p!=-1&&!st[p].nxt.count(c)){
            st[p].nxt[c]=cur;
            p=st[p].link;
        }
        if (p==-1){
            st[cur].link=0;
        }else{
            int q=st[p].nxt[c];
            if (st[p].mxlen+1==st[q].mxlen){
                st[cur].link=q;
            }else{
                int tmp=sz++;
                st[tmp].mxlen=st[p].mxlen+1;
                st[tmp].nxt=st[q].nxt;
                st[tmp].link=st[q].link;
                while (p!=-1&&st[p].nxt[c]==q){
                    st[p].nxt[c]=tmp;
                    p=st[p].link;
                }
                st[q].link=st[cur].link=tmp;
            }
        }
        lst=cur;
    }
    void toposort(){
        for (int i=1;i<=sz;++i){
            ind[st[i].link]++;
        }
        for (int i=1;i<=sz;++i){
            if (ind[i]&&vis[i]) ++cnt[i];
        }
        queue<int> q;
        for (int i=1;i<=sz;++i){
            if (!ind[i]){
                q.push(i); ++cnt[i];
            }
        }
        while (!q.empty()){
            int u=q.front(); q.pop();
            int v=st[u].link;
            if (!v) continue;
            cnt[v]+=cnt[u]; ind[v]--;
            if (!ind[v]) q.push(v);
        }
    }
}