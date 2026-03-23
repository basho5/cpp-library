template <typename TREE, typename Data>
struct Rerooting {
  static_assert(!TREE::Graph_type::is_directed);
  TREE& tree;
  vc<Data> dp_1; // 辺 pv に対して、部分木 v

  vc<Data> dp_2; // 辺 pv に対して、部分木 p

  vc<Data> dp;   // full tree

  template <typename F1, typename F2, typename F3>
  Rerooting(TREE& tree, F1 f_ee, F2 f_ev, F3 f_ve, const Data unit) : tree(tree) {
    build(f_ee, f_ev, f_ve, unit);
  }

  // v を根としたときの full tree
  // operator[]: v を根としたときの全木 DP 値を取得
  Data operator[](int v) { return dp[v]; }

  // root を根としたときの部分木 v
  // get(v,root): root を根とした木における v の部分木 DP
  Data get(int v, int root) {
    if (root == v) return dp[v];
    if (!tree.in_subtree(root, v)) { return dp_1[v]; }
    int w = tree.jump(v, root, 1);
    return dp_2[w];
  }

  template <typename F1, typename F2, typename F3>
  void build(F1 f_ee, F2 f_ev, F3 f_ve, const Data unit) {
    int N = tree.N;
    // dp1: subtree

    dp_1.assign(N, unit);
    drep(i, N) {
      int v = tree.V[i];
      for (auto&& e: tree.G[v]) {
        if (e.to == tree.parent[v]) continue;
        dp_1[v] = f_ee(dp_1[v], f_ve(dp_1[e.to], e));
      }
      dp_1[v] = f_ev(dp_1[v], v);
    }

    // dp2[v]: subtree of p, rooted at v

    dp_2.assign(N, unit);
    // dp[v]: fulltree, rooted at v

    dp.assign(N, unit);
    rep(i, N) {
      int p = tree.V[i];
      vc<int> ch;
      vc<Data> ch_data;
      Data x = unit;
      for (auto&& e: tree.G[p]) {
        if (e.to == tree.parent[p]) {
          x = f_ve(dp_2[p], e);
        } else {
          ch.eb(e.to);
          ch_data.eb(f_ve(dp_1[e.to], e));
        }
      }
      int n = sz(ch);
      if (!n) {
        dp[p] = f_ev(x, p);
        continue;
      }
      vc<Data> prod_left(n, x);
      rep(i, n - 1) prod_left[i + 1] = f_ee(prod_left[i], ch_data[i]);
      Data prod_right = unit;
      drep(i, n) {
        dp_2[ch[i]] = f_ev(f_ee(prod_left[i], prod_right), p);
        prod_right = f_ee(prod_right, ch_data[i]);
      }
      dp[p] = f_ev(f_ee(x, prod_right), p);
    }
  }
};

// =========================
// 全方位木DP (Rerooting) テンプレート
// 
// TREE :
//   無向再根付け木クラス。以下のメンバを持つことが前提:
//     - tree.N         : 頂点数
//     - tree.G[v]      : 隣接リスト (Edge<...>)
//     - tree.parent[v] : 根 0 から見たときの親
//     - tree.V         : root 0 からの DFS 順リスト
//     - tree.in_subtree(u,v) : u を根としたとき v が部分木内にいるか
//     - tree.jump(u,v,k)     : u->v パス上で u 側から k ステップ進んだ頂点
// 
// Data  : DP の値の型
// 
// コンストラクタ引数:
//   f_ee  : Data f_ee(Data acc, Data child_val)
//           子どうしをマージする演算 (結合法則が前提)
//   f_ev  : Data f_ev(Data merged_children, int v)
//           子どもからまとめた値を頂点 v の最終 DP に変換
//   f_ve  : Data f_ve(Data from_parent, const Edge<...>& e)
//           親→子伝搬時に、親側からの DP を子視点に変換 (辺 e の情報利用可)
//   unit  : merge 演算の単位元 (f_ee(unit,x)==x を満たす)
// =========================

void solve() {
  LL(N);
  Graph<int> G(N);
  G.read_tree();
  Tree tree(G);

  using Data = pair<int, mint>;
  Data unit = {0, mint(1)};
  auto fee = [&](Data x, Data y) -> Data { return {x.fi + y.fi, x.se * y.se}; };
  auto fev = [&](Data x, int v) -> Data {
    return {x.fi , x.se * invs(x.fi + 1)};
  };
  // e は v から出る有向辺
  auto fve = [&](Data x, auto& e) -> Data {  auto r = x ; r.fi ++ ;return r; };
  Rerooting<decltype(tree), Data> dp(tree, fee, fev, fve, unit);

  rep(v, N) out(dp[v].se*facs(N));
}
