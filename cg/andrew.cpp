struct vec{
    //vector,also the point's position
    double x,y;
    bool operator <(const vec &_p){
        return (x==_p.x)?y<_p.y:x<_p.x;
    }
    vec operator +(const vec &_p){
        return (vec){x+_p.x,y+_p.y};
    }
    vec operator -(const vec &_p){
        return (vec){x-_p.x,y-_p.y};
    }
}p[maxn];
double cross(vec _a,vec _b){
    return _a.x*_b.y-_a.y*_b.x;
}
int sta[maxn],top=0;
//instack=on convex hull
int used[maxn]; //if it is on convex hull
void Andrew(){
    sort(p+1,p+1+n);
    if (n<=2) return; //no answer
    sta[++top]=1;
    for (int i=2;i<=n;++i){
        while (top>=2&&
               cross(p[sta[top]]-p[sta[top-1]],p[i]-p[sta[top]])<=0){
            used[sta[top--]]=0;
        }
        used[i]=1; sta[++top]=i;
    }
    int tmp=top;
    for (int i=n-1;i>0;--i){
        if (used[i]) continue;
        //don't have influence on down convex hull
        while (top>tmp&&
               cross(p[sta[top]]-p[sta[top-1]],p[i]-p[sta[top]])<=0){
            used[sta[top--]]=0;
        }
        used[i]=1; sta[++top]=i;
    }
}