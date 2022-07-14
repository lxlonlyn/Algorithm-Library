#define ls o<<1
#define rs ls|1
struct treenode{
    ll sum;
    ll lazy_add,lazy_mul;
}sgt[maxn<<2];
void sgt_build(int o,int l,int r){
    sgt[o].lazy_mul=1; 
    if (l==r){
        sgt[o].sum=a[l]; 
        return;
    }
    int mid=(l+r)>>1;
    sgt_build(ls,l,mid); sgt_build(rs,mid+1,r);
    sgt[o].sum=sgt[ls].sum+sgt[rs].sum;
}
void sgt_pushdown(int o,int l,int r){ 
    //pushdown when query or modify
    //frist mul then add
    sgt[ls].lazy_mul=(sgt[ls].lazy_mul*sgt[o].lazy_mul)%p;
    sgt[rs].lazy_mul=(sgt[rs].lazy_mul*sgt[o].lazy_mul)%p;
    sgt[ls].lazy_add=(sgt[ls].lazy_add*sgt[o].lazy_mul)%p;
    sgt[rs].lazy_add=(sgt[rs].lazy_add*sgt[o].lazy_mul)%p;
    sgt[ls].sum=(sgt[ls].sum*sgt[o].lazy_mul)%p;
    sgt[rs].sum=(sgt[rs].sum*sgt[o].lazy_mul)%p;
    sgt[o].lazy_mul=1; 
    int mid=(l+r)>>1;
    sgt[ls].lazy_add=(sgt[ls].lazy_add+sgt[o].lazy_add)%p;
    sgt[rs].lazy_add=(sgt[rs].lazy_add+sgt[o].lazy_add)%p;
    sgt[ls].sum=(sgt[ls].sum+(mid-l+1)*sgt[o].lazy_add)%p;
    sgt[rs].sum=(sgt[rs].sum+(r-mid)*sgt[o].lazy_add)%p;
    sgt[o].lazy_add=0;
}
void sgt_mul(int o,int l,int r,int ql,int qr,ll k){
    if (l>=ql&&r<=qr){
        sgt[o].lazy_add=(sgt[o].lazy_add*k)%p;
        sgt[o].lazy_mul=(sgt[o].lazy_mul*k)%p;
        sgt[o].sum=(sgt[o].sum*k)%p;
        return;
    }
    int mid=(l+r)>>1;
    if (sgt[o].lazy_mul!=1||sgt[o].lazy_add) sgt_pushdown(o,l,r);
    if (ql<=mid) sgt_mul(ls,l,mid,ql,qr,k);
    if (qr>mid) sgt_mul(rs,mid+1,r,ql,qr,k);
    sgt[o].sum=(sgt[ls].sum+sgt[rs].sum)%p;
}
void sgt_add(int o,int l,int r,int ql,int qr,ll k){
    if (l>=ql&&r<=qr){
        sgt[o].lazy_add=(sgt[o].lazy_add+k)%p;
        sgt[o].sum=(sgt[o].sum+(r-l+1)*k)%p;
        return;
    }
    int mid=(l+r)>>1;
    if (sgt[o].lazy_mul!=1||sgt[o].lazy_add) sgt_pushdown(o,l,r);
    if (ql<=mid) sgt_add(ls,l,mid,ql,qr,k);
    if (qr>mid) sgt_add(rs,mid+1,r,ql,qr,k);
    sgt[o].sum=(sgt[ls].sum+sgt[rs].sum)%p;
}
ll sgt_querysum(int o,int l,int r,int ql,int qr){
    if (l>=ql&&r<=qr){
        return sgt[o].sum;
    }
    int mid=(l+r)>>1;
    if (sgt[o].lazy_add||sgt[o].lazy_mul!=1) sgt_pushdown(o,l,r);
    ll tmp_sum=0;
    if (ql<=mid) tmp_sum=(tmp_sum+sgt_querysum(ls,l,mid,ql,qr))%p;
    if (qr>mid) tmp_sum=(tmp_sum+sgt_querysum(rs,mid+1,r,ql,qr))%p;
    return tmp_sum%p;
}