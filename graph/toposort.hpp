// トポロジカルソート
// o(V+E)
vector<int> topo(const vector<vector<int>> &g) {
    int n = g.size();
    vector<int> in(n, 0), res;
    for (int i = 0; i < n; i++) for (int j : g[i]) in[j]++;
    queue<int> q;
    for (int i = 0; i < n; i++) if (!in[i]) q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        res.push_back(u);
        for (int v : g[u])
            if (--in[v] == 0) q.push(v);
    }
    return (res.size() == n ? res : vector<int>{});
}

// 一意性の判定付きトポロジカルソート
// o(V+E)
pair<vector<int>, bool> utopo(const vector<vector<int>> &g) {
    int n = g.size();
    vector<int> in(n, 0), res;
    bool uniq = true;
    for (int i = 0; i < n; i++) for (int j : g[i]) in[j]++;
    queue<int> q;
    for (int i = 0; i < n; i++) if (!in[i]) q.push(i);
    while (!q.empty()) {
        if (q.size() > 1) uniq = false;
        int u = q.front(); q.pop();
        res.push_back(u);
        for (int v : g[u])
            if (--in[v] == 0) q.push(v);
    }
    return (res.size() == n ? make_pair(res, uniq) : make_pair(vector<int>{}, false));
}

// 辞書順最小のトポロジカルソート
// o((V+E)logV)
vector<int> ltopo(const vector<vector<int>> &g) {
    int n = g.size();
    vector<int> in(n, 0), res;
    for (int i = 0; i < n; i++) for (int j : g[i]) in[j]++;
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < n; i++) if (!in[i]) pq.push(i);
    while (!pq.empty()) {
        int u = pq.top(); pq.pop();
        res.push_back(u);
        for (int v : g[u])
            if (--in[v] == 0) pq.push(v);
    }
    return (res.size() == n ? res : vector<int>{});
}
