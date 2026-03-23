template <typename T, typename GT>
pair<T, vc<int>> tree_diameter(GT& G) {
  assert(G.is_prepared());
  int A, B;
  auto [distA, parA] = bfs01<T>(G, 0);
  A = max_element(rng(distA)) - distA.begin();
  auto [dist, par] = bfs01<T>(G, A);
  B = max_element(rng(dist)) - dist.begin();
  vc<int> P = restore_path(par, B);
  return {dist[B], P};
}
