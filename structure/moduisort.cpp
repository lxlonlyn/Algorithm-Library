bool cmp(node a, node b) {
    return pos[a.l] ^ pos[b.l] ? 
        pos[a.l] < pos[b.l] : pos[a.l] & 1 ? 
            a.r < b.r : a.r > b.r;
}