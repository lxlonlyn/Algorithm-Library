int lowbit(int x){
    return x&(-x);
}
void add_val(int pos,int val){
    while (pos<=n){
        tree[pos]+=val;
        pos+=lowbit(pos);
    }
}
int get_sum(int pos){
    int tmp=0;
    while (pos>0){
        tmp+=tree[pos];
        pos-=lowbit(pos);
    }
    return tmp;
}