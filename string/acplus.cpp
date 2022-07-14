int sameto[maxn];
struct AC_automaton {
    int lst[400010], dep[400010];
    void init(){
        memset(lst, -1, sizeof(lst));
        memset(dep, 0, sizeof(dep));
    }
    void insert(char *s, int id){
        // above is the same
        if (!mp[u]) mp[u] = id;
        else sameto[id] = mp[u];
    }
    void query(char *s) {
        int u = 0;
        for (int i = 1; s[i]; ++i){
            u = trie[u][s[i]-'a'];
            for (int j = u; j; j = fail[j]){
                // modify
                if (mp[j] && i - lst[j] >= dep[j]) {
                    ++cnt[mp[j]]; 
                    lst[j] = i;
                }
            }
        }
    }
} AC;

// output: same need to change
for (int i = 1; i <= n; ++i) {
    if (AC.cnt[i]) printf("%d\n", AC.cnt[i]);
    else printf("%d\n", AC.cnt[sameto[i]]);
}
