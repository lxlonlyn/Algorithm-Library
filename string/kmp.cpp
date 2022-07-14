char t[maxn],s[maxn]; //find s in t 
int slen,tlen; //don't use strlen in for()
int pi[maxn]; //pi[i]=next[i]
void prefix_function(){
    pi[0]=0;
    for (int i=1;i<slen;++i){
        int j=pi[i-1];
        while (j>0&&s[i]!=s[j]) j=pi[j-1];
        if (s[i]==s[j]) j++;
        pi[i]=j;
    }
} 
vector<int> ans;
void kmp(){
    prefix_function();
    int j=0;
    for (int i=0;i<tlen;++i){
        while (j&&t[i]!=s[j]) j=pi[j-1];
        if (t[i]==s[j]) ++j;
        if (j==slen){
            ans.push_back(i-slen+2);
            j=pi[j-1];
        }
    }
}