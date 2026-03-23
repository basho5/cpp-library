struct UnionFind {
  int n, n_comp;
  vc<int> dat; // par or (-size)
  UnionFind(int n = 0) { build(n); }

  void build(int m) {
    n = m, n_comp = m;
    dat.assign(n, -1);
  }

  void reset() { build(n); }

  int operator[](int x) {
    while (dat[x] >= 0) {
      int pp = dat[dat[x]];
      if (pp < 0) { return dat[x]; }
      x = dat[x] = pp;
    }
    return x;
  }

  ll size(int x) {
    x = (*this)[x];
    return -dat[x];
  }

  bool merge(int x, int y) {
    x = (*this)[x], y = (*this)[y];
    if (x == y) return false;
    if (-dat[x] < -dat[y]) swap(x, y);
    dat[x] += dat[y], dat[y] = x, n_comp--;
    return true;
  }

  vc<int> get_all() {
    vc<int> A(n);
    rep(i, n) A[i] = (*this)[i];
    return A;
  }
};

template <typename E>
struct Monoid_Add {
  using X = E;
  using value_type = X;
  static constexpr X op(const X &x, const X &y) noexcept { return x + y; }
  static constexpr X inverse(const X &x) noexcept { return -x; }
  static constexpr X power(const X &x, ll n) noexcept { return X(n) * x; }
  static constexpr X unit() { return X(0); }
  static constexpr bool commute = true;
};

template <typename U, typename Arg1, typename Arg2>
struct has_power_method {
private:
  // ヘルパー関数の実装
  template <typename V, typename A1, typename A2>
  static auto check(int)
      -> decltype(std::declval<V>().power(std::declval<A1>(),
                                          std::declval<A2>()),
                  std::true_type{});
  template <typename, typename, typename>
  static auto check(...) -> std::false_type;

public:
  // メソッドの有無を表す型
  static constexpr bool value = decltype(check<U, Arg1, Arg2>(0))::value;
};

template <typename Monoid>
typename Monoid::X monoid_pow(typename Monoid::X x, ll exp) {
  using X = typename Monoid::X;
  if constexpr (has_power_method<Monoid, X, ll>::value) {
    return Monoid::power(x, exp);
  } else {
    assert(exp >= 0);
    X res = Monoid::unit();
    while (exp) {
      if (exp & 1) res = Monoid::op(res, x);
      x = Monoid::op(x, x);
      exp >>= 1;
    }
    return res;
  }
}


// functional graph の辺に static な群の要素があるとする
// （モノイドにもできるがそれは doubling してもらうということでさぼり. ）
template <typename Monoid>
struct FunctionalGraph {
  using MX = Monoid;
  using X = typename MX::value_type;
  int N, M;
  vc<int> TO;
  vc<X> wt, dp;
  vc<int> root;
  Graph<int, 1> G;

  FunctionalGraph() {}
  FunctionalGraph(int N) : N(N), M(0), TO(N, -1), wt(N, MX::unit()), root(N, -1) {}

  void add(int a, int b, X c = MX::unit()) {
    assert(0 <= a && a < N);
    assert(TO[a] == -1);
    ++M;
    TO[a] = b;
    wt[a] = c;
  }

  pair<Graph<int, 1>, Tree<Graph<int, 1>>> build() {
    assert(N == M);
    UnionFind uf(N);
    rep(v, N) if (!uf.merge(v, TO[v])) { root[v] = v; }
    rep(v, N) if (root[v] == v) root[uf[v]] = v;
    rep(v, N) root[v] = root[uf[v]];

    G.build(N + 1);
    rep(v, N) {
      if (root[v] == v)
        G.add(N, v);
      else
        G.add(TO[v], v);
    }
    G.build();
    Tree<Graph<int, 1>> tree(G, N);
    dp.assign(N, MX::unit());
    rep(i, 1, N + 1) {
      int v = tree.V[i];
      int p = tree.parent[v];
      if (p == N) { continue; }
      dp[v] = MX::op(wt[v], dp[p]);
    }
    return {G, tree};
  }

  // a -> b にかかる回数. 不可能なら infty<int>. O(1).

  template <typename TREE>
  int dist(TREE& tree, int a, int b) {
    if (tree.in_subtree(a, b)) return tree.depth[a] - tree.depth[b];
    int r = root[a];
    int btm = TO[r];
    // a -> r -> btm -> b

    if (tree.in_subtree(btm, b)) {
      int x = tree.depth[a] - tree.depth[r];
      x += 1;
      x += tree.depth[btm] - tree.depth[b];
      return x;
    }
    return infty<int>;
  }

  // functional graph に向かって進む

  // return: 終点, 群の積

  template <typename TREE>
  pair<int, X> jump(TREE& tree, int v, ll step) {
    int d = tree.depth[v];
    if (step <= d - 1) {
      int w = tree.jump(v, N, step);
      return {w, MX::op(dp[v], MX::inverse(dp[w]))};
    }
    X x = dp[v];
    v = root[v];
    step -= d - 1;
    int bottom = TO[v];
    int c = tree.depth[bottom];
    x = MX::op(x, monoid_pow<MX>(MX::op(wt[v], dp[bottom]), step / c));
    step %= c;
    if (step == 0) return {v, x};
    int w = tree.jump(bottom, N, step - 1);
    x = MX::op(x, wt[v]);
    x = MX::op(x, dp[bottom]);
    x = MX::op(x, MX::inverse(dp[w]));
    return {w, x};
  }

  // functional graph に step 回進む

  template <typename TREE>
  vc<int> jump_all(TREE& tree, ll step) {
    vc<int> res(N, -1);
    // v の k 個先を res[w] に入れる

    vv<pair<int, int>> query(N);
	rep(v, N) {
      int d = tree.depth[v];
      int r = root[v];
      if (d - 1 > step) { query[v].eb(v, step); }
      if (d - 1 <= step) {
        ll k = step - (d - 1);
        int bottom = TO[r];
        int c = tree.depth[bottom];
        k %= c;
        if (k == 0) {
          res[v] = r;
          continue;
        }
        query[bottom].eb(v, k - 1);
      }
    }

    vc<int> path;
    auto dfs = [&](auto& dfs, int v) -> void {
      path.eb(v);
      for (auto&& [w, k]: query[v]) { res[w] = path[sz(path) - 1 - k]; }
      for (auto&& e: G[v]) dfs(dfs, e.to);
      path.pop_back();
    };
    for (auto&& e: G[N]) { dfs(dfs, e.to); }
    return res;
  }

  template <typename TREE>
  bool in_cycle(TREE& tree, int v) {
    int r = root[v];
    int bottom = TO[r];
    return tree.in_subtree(bottom, v);
  }

  // 葉側から順にならんだものを出力

  vc<int> collect_cycle(int r) {
    assert(r == root[r]);
    vc<int> cyc = {TO[r]};
    while (cyc.back() != r) cyc.eb(TO[cyc.back()]);
    return cyc;
  }

  // F^k(i)==F^k(j) となる最小の k OR -1

  template <typename TREE>
  int meet_time(TREE& tree, int i, int j) {
    if (i == j) return 0;
    if (root[i] != root[j]) return -1;
    int r = root[i];
    int b = TO[r];
    int n = tree.depth[b] - tree.depth[r] + 1; // cyc len

    if ((tree.depth[i] - tree.depth[j]) % n != 0) return -1;

    if (tree.depth[i] == tree.depth[j]) {
      int lca = tree.lca(i, j);
      return tree.depth[i] - tree.depth[lca];
    }
    int ti = tree.depth[i] - tree.depth[tree.lca(b, i)];
    int tj = tree.depth[j] - tree.depth[tree.lca(b, j)];
    return max(ti, tj);
  }
};
