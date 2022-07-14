struct Node{
    int x,y;
}
struct NodeHash {
  static uint64_t splitmix64(uint64_t x) { //很复杂的式子
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  size_t operator()(Type _a) const { 
    static const uint64_t FIXED_RANDOM =
        chrono::steady_clock::now().time_since_epoch().count();
    //加入未确定时间因素更难hack
    return splitmix64(_a.x*233+_a.y + FIXED_RANDOM);
  }
};
struct NodeEqual{
    bool operator () {const Node& _a,const Node& _b} const {
        return _a.x==_b.x&&_a.y==_b.y;
    }
}