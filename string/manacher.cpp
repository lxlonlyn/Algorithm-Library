int changestring(){
    int len=strlen(s);
    new_s[0]='$'; new_s[1]='#';
    int j=2;
    for (int i=0;i<len;++i){
        new_s[j++]=s[i];
        new_s[j++]='#';
    }
    new_s[j]='\0'; //don't forget
    return j; //return new string's length
}
int manacher(){
    int len=changestring(),ans=-1;
    int l=-1,r=0;
    for (int i=1;i<len;++i){
        if (i<r){
            p[i]=min(p[2*l-i],r-i);
        }else{
            p[i]=1;
        }
        while (new_s[i-p[i]]==new_s[i+p[i]]) ++p[i];
        if (r<i+p[i]){
            l=i; r=i+p[i];
        }
        ans=max(ans,p[i]-1);
    }
    return ans;
}