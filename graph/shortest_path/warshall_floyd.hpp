// 負辺があっても負閉路がなければ正しく動作する。
// 負閉路があるかどうかは、dist[v][v] < 0 となる v があるかどうかで判定。
template <typename T, typename GT>
vc<vc<T>> warshall_floyd(GT& G) {
  ll N = G.N;
  vv(T, dist, N, N, infty<T>);
  rep(v, N) {
    dist[v][v] = 0;
    for (auto&& e: G[v]) mins(dist[v][e.to], e.cost);
  }
  rep(k, N)rep(i, N) {
    if (dist[i][k] == infty<T>) continue;
    rep(j, N) {
      if (dist[k][j] == infty<T>) continue;
      mins(dist[i][j], dist[i][k] + dist[k][j]);
    }
  }
  return dist;
}
