char s[maxn];
int pi[maxn]; 
void prefix_function(){
    int len=strlen(s);
    pi[0]=0;
    for (int i=1;i<n;++i){
        int j=pi[i-1];
        while (j>0&&s[i]!=s[j]) j=pi[j-1];
        if (s[i]==s[j]) j++;
        pi[i]=j;
    }
} 