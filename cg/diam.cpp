double dis(vec _a,vec _b){
    return sqrt((_a.x-_b.x)*(_a.x-_b.x)
               +(_a.y-_b.y)*(_a.y-_b.y));
}
double getdiam(){
    if (n<=2){
        return dis(p[1],p[2]);
    }
    double res=0.0;
    int j=3;
    for (int i=1;i<top;++i){
        while (cross(p[sta[i+1]]-p[sta[i]],p[sta[j]]-p[sta[i]])
              <cross(p[sta[i+1]]-p[sta[i]],p[sta[j+1]]-p[sta[i]])){
            ++j; if (j>top) j-=top;
        }
        res=max(res,dis(p[sta[i]],p[sta[j]]));
        res=max(res,dis(p[sta[i+1]],p[sta[j]]));
    }
    return res;
}