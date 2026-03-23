// 最小全域木を作るので、特に各点からの最近点をとる目的で使うこともできる
template <typename T>
Graph<T, 0> manhattan_mst(vc<pair<T, T>>& XY) {
  int N = XY.size();
  vc<tuple<T, int, int>> dat;
  dat.reserve(4 * N);
  vc<int> idx(N);
  iota(rng(idx), 0);

  rep(a, 2) {
    for (auto&& [x, y]: XY) x = -x;
    rep(b, 2) {
      for (auto&& [x, y]: XY) swap(x, y);
      sort(rng(idx), [&](const int& i, const int& j) -> bool {
        return XY[i].fi + XY[i].se < XY[j].fi + XY[j].se;
      });

      map<T, int> MP;
      for (const int i: idx) {
        auto& [x, y] = XY[i];
        for (auto it = MP.lower_bound(-y); it != MP.end(); it = MP.erase(it)) {
          const int j = it->se;
          auto& [xj, yj] = XY[j];
          const int dx = x - xj;
          const int dy = y - yj;
          if (dy > dx) break;
          dat.eb(dx + dy, i, j);
        }
        MP[-y] = i;
      }
    }
  }

  sort(rng(dat));
  Graph<T, 0> G(N);
  UnionFind uf(N);
  for (auto&& [cost, i, j]: dat) {
    if (uf.merge(i, j)) G.add(i, j, cost);
  }
  G.build();
  return G;
}
