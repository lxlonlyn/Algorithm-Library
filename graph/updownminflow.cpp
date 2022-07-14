//just different here
if (totflow==dinic(SS,TT)){
    ll sum=edge[G[T][G[T].size()-1]].flow;
    G[S].pop_back(); G[T].pop_back();
    printf("%lld",sum-dinic(T,S)); //dont't write S,T
}else{
    printf("please go home to sleep");
}