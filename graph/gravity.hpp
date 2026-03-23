// 重心を求める関数：引数 c が与えられた場合
int calc_g(const vvi &to, const vl &c) {
    int n = to.size();
    vector<ll> sub(n, 0);   // 各頂点の部分木の重み
    vector<int> par(n, -1); // DFS での親頂点

    // DFS による部分木重みの計算
    function<ll(int, int)> dfs = [&](int v, int p) -> ll {
        par[v] = p;
        ll sum = c[v];
        for (int u : to[v]) {
            if (u == p) continue;
            sum += dfs(u, v);
        }
        sub[v] = sum;
        return sum;
    };

    ll total = dfs(0, -1);
    int centroid = 0;
    ll best = total;  // 最小の「最大連結成分の重み」を求める
    for (int v = 0; v < n; v++) {
        ll max_comp = total - sub[v]; // v の親側の重み
        for (int u : to[v]) {
            if (u == par[v]) continue;
            max_comp = max(max_comp, sub[u]); // v の各子方向の部分木重み
        }
        if (max_comp < best) {
            best = max_comp;
            centroid = v;
        }
    }
    return centroid;
}
// 重み c を指定しない場合は、各頂点の重みを 1 として呼び出すオーバーロード版
int calc_g(const vvi &to) {
    int n = to.size();
    vl c(n, 1);
    return calc_g(to, c);
}
