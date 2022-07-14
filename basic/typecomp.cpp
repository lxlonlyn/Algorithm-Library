// example of map
struct node {
    int x, y;
} cur;
struct cmp {
    bool operator () (const node &a, const node &b) const {
        return (a.x == b.x) ? a.y < b.y : a.x < b.x;
    }
};
map<node, int, cmp> mp;
