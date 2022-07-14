bool toposort() {
    q = new queue();
    for (i = 0; i < n; i++)
        if (in_deg[i] == 0) q.push(i);
    ans = new vector();
    while (!q.empty()) {
        u = q.pop();
        ans.push_back(u);
        for each edge(u, v) {
            if (--in_deg[v] == 0) q.push(v);
        }
    }
    if (ans.size() == n) {
        for (i = 0; i < n; i++)
            cout << ans[i] << endl;
        return true;
    } else {
        return false;
    }
}