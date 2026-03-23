//----------------------------------------------------------
// HLD 構造体 (Heavy-Light Decomposition)
//----------------------------------------------------------
/*
  HLD 構造体は、与えられた木 (Graph で表現) から Euler Tour や Heavy-Light 分解に基づく情報を計算し、
  以下の情報をメンバ変数として保持します:
    - LID[v]: 頂点 v の Euler Tour 上での入時刻
    - RID[v]: 頂点 v の部分木の終端 (v の部分木に含まれる頂点は [LID[v], RID[v]) に位置)
    - head[v]: 頂点 v が属する heavy path の先頭頂点
    - parent[v]: 頂点 v の親頂点 (根は -1)
    - depth[v]: 頂点 v の深さ (根からの距離)
    - root[v]: 頂点 v の属する連結成分の根（親がいない場合の v）
    - V: Euler Tour 順に並んだ頂点列
  これらの情報を用いて、LCA (最小共通祖先) や部分木クエリ、頂点間距離などを高速に計算できます。
*/
// LCA, LA などは O(logN) 時間。
// 木以外、非連結でも使えるようにした。dfs順序や親がとれる。
template <typename GT>
struct Tree {
  using Graph_type = GT;
  GT &G;
  using WT = typename GT::cost_type;
  int N;
  vector<int> LID, RID, head, V, parent, VtoE;
  vc<int> depth;
  vc<WT> depth_weighted;

  // コンストラクタ：Graph G と根 r を指定（r == -1 なら非連結にも対応）
  Tree(GT &G, int r = 0, bool hld = 1) : G(G) { build(r, hld); }

  // build() : 根 r からの DFS により、Euler Tour, 親, 深さなどを計算
  void build(int r = 0, bool hld = 1) {
    if (r == -1) return; // build を遅延したいとき
    N = G.N;
    LID.assign(N, -1), RID.assign(N, -1), head.assign(N, r);
    V.assign(N, -1), parent.assign(N, -1), VtoE.assign(N, -1);
    depth.assign(N, -1), depth_weighted.assign(N, 0);
    assert(G.is_prepared());
    int t1 = 0;
    dfs_sz(r, -1, hld);
    dfs_hld(r, t1);
  }

  // dfs_sz(v, p, hld) : 深さ優先探索により、頂点 v の部分木サイズ（RID[v] に一時的に格納）、
  // 親 (parent[v])、深さ (depth[v])、および重み付き深さを更新する。
  // また、hld==true の場合は heavy child を先頭に持ってくるため、csr_edges の順序を調整する。
  void dfs_sz(int v, int p, bool hld) {
    auto &sz = RID;  // 一時的に部分木サイズとして利用
    parent[v] = p;
    depth[v] = (p == -1 ? 0 : depth[p] + 1);
    sz[v] = 1;
    int l = G.indptr[v], r = G.indptr[v + 1];
    auto &csr = G.csr_edges;
    // 使う辺があれば先頭に持ってくる。FOR3_R(i, l, r-1) で i=r-2 から l まで逆順ループ
    for(ll i=r-2;i>=(ll)l;i--){
      if (hld && depth[csr[i + 1].to] == -1)
        swap(csr[i], csr[i + 1]);
    }
    int hld_sz = 0;
    srep(i, l, r) {
      auto e = csr[i];
      if (depth[e.to] != -1) continue;  // 既に訪問済みならスキップ
      depth_weighted[e.to] = depth_weighted[v] + e.cost;
      VtoE[e.to] = e.id;
      dfs_sz(e.to, v, hld);
      sz[v] += sz[e.to];
      if (hld && maxs(hld_sz, sz[e.to]) && (l < i)) {
        swap(csr[l], csr[i]);
      }
    }
  }

  // dfs_hld(v, times) : Euler Tour の順序に基づいて、各頂点の LID[v] (入時刻) を設定し、
  // Euler Tour 順に頂点を V[t] に記録、heavy-path の head も設定する。
  void dfs_hld(int v, int &times) {
    LID[v] = times++;
    RID[v] += LID[v];
    V[LID[v]] = v;
    bool heavy = true;
    for (auto &&e: G[v]) {
      if (depth[e.to] <= depth[v]) continue;
      head[e.to] = (heavy ? head[v] : e.to);
      heavy = false;
      dfs_hld(e.to, times);
    }
  }

  // heavy_path_at(v): 頂点 v を heavy path の先頭として、その heavy path 上の頂点列を返す
  vc<int> heavy_path_at(int v) {
    vc<int> P = {v};
    while (true) {
      int a = P.back();
      bool found = false;
      for (auto &&e: G[a]) {
        if (e.to != parent[a] && head[e.to] == v) {
          P.eb(e.to);
          found = true;
          break;
        }
      }
      if (!found) break;
    }
    return P;
  }

  // heavy_child(v): 頂点 v の heavy child（もし存在すれば）を返す。
  int heavy_child(int v) {
    int k = LID[v] + 1;
    if (k == N) return -1;
    int w = V[k];
    return (parent[w] == v ? w : -1);
  }
  
  vc<int> memo_tail ; 
  int tail(int v){
	if(memo_tail.empty()){
		memo_tail.assign(N, -1);
        drep(i, N){
        int v = V[i];
        int w = heavy_child(v);
        memo_tail[v] = (w == -1 ? v : memo_tail[w]);
      }
	}
	return memo_tail[v] ;
  }

  // e_to_v(eid): 辺の id を指定し、その辺が木上で子側として使われている頂点を返す。
  int e_to_v(int eid) {
    auto e = G.edges[eid];
    return (parent[e.frm] == e.to ? e.frm : e.to);
  }
  // v_to_e(v): 頂点 v に入ってくる辺の id を返す
  int v_to_e(int v) { return VtoE[v]; }
  // get_eid(u, v): u と v の間の辺の id を返す（u が子なら u に対応）
  int get_eid(int u, int v) {
    if (parent[u] != v) swap(u, v);
    assert(parent[u] == v);
    return VtoE[u];
  }

  // ELID(v) と ERID(v): Euler Tour 上での頂点 v の拡張区間の開始／終了位置
  int ELID(int v) { return 2 * LID[v] - depth[v]; }
  int ERID(int v) { return 2 * RID[v] - depth[v] - 1; }

  // LA(v, k): 頂点 v から上方向に k 回移動した頂点を返す (k=0 なら v 自身)
  int LA(int v, int k) {
    assert(k <= depth[v]);
    while (true) {
      int u = head[v];  // 現在の heavy path の先頭
      if (LID[v] - k >= LID[u])
        return V[LID[v] - k];
      k -= (LID[v] - LID[u] + 1);
      v = parent[u];
    }
  }

  pair<int,int> subtree(int v){return {LID[v], RID[v]};} 

  int la(int u, int v) { return LA(u, v); }

  // LCA(u, v): 頂点 u と v の最小共通祖先を返す
  int LCA(int u, int v) {
    for (;; v = parent[head[v]]) {
      if (LID[u] > LID[v])
        swap(u, v);
      if (head[u] == head[v])
        return u;
    }
  }
  int lca(int u, int v) { return LCA(u, v); }

  // meet(a, b, c): 3頂点のうち、ある意味での「交点」を返す補助関数（XOR の組み合わせ）
  int meet(int a, int b, int c) { return LCA(a, b) ^ LCA(a, c) ^ LCA(b, c); }

  // subtree_size(v, root): 頂点 v の部分木サイズを返す。root 指定時は調整あり。
  int subtree_size(int v, int root = -1) {
    if (root == -1) return RID[v] - LID[v];
    if (v == root) return N;
    int x = jump(v, root, 1);
    if (in_subtree(v, x)) return RID[v] - LID[v];
    return N - RID[x] + LID[x];
  }

  // dist(a, b): 頂点 a と b の距離（辺の数）を返す
  int dist(int a, int b) {
    int c = LCA(a, b);
    return depth[a] + depth[b] - 2 * depth[c];
  }

  // dist_weighted(a, b): 重み付きの距離を返す
  WT dist_weighted(int a, int b) {
    int c = LCA(a, b);
    return depth_weighted[a] + depth_weighted[b] - WT(2) * depth_weighted[c];
  }

  // in_subtree(a, b): 頂点 a が頂点 b の部分木に含まれるかを判定
  // a in b 
  bool in_subtree(int a, int b) { return LID[b] <= LID[a] && LID[a] < RID[b]; }

  // jump(a, b, k): 頂点 a から b までの経路上で k 回ジャンプした頂点を返す
  int jump(int a, int b, ll k) {
    if (k == 1) {
      if (a == b) return -1;
      return (in_subtree(b, a) ? LA(b, depth[b] - depth[a] - 1) : parent[a]);
    }
    int c = LCA(a, b);
    int d_ac = depth[a] - depth[c];
    int d_bc = depth[b] - depth[c];
    if (k > d_ac + d_bc) return -1;
    if (k <= d_ac) return LA(a, k);
    return LA(b, d_ac + d_bc - k);
  }

  // collect_child(v): 頂点 v の子頂点のリストを返す
  vc<int> collect_child(int v) {
    vc<int> res;
    for (auto &&e: G[v])
      if (e.to != parent[v])
        res.eb(e.to);
    return res;
  }

  // collect_light(v): 頂点 v の「light edge」先の子を返す（最初の子を除く）
  vc<int> collect_light(int v) {
    vc<int> res;
    bool skip = true;
    for (auto &&e: G[v])
      if (e.to != parent[v]) {
        if (!skip) res.eb(e.to);
        skip = false;
      }
    return res;
  }

  // get_path_decomposition(u, v, edge):
  // 頂点 u から v までのパスを、Euler Tour 上の区間の列として分解して返す。
  // edge が true なら、区間を辺を含むように調整する。
  vc<pair<int, int>> get_path_decomposition(int u, int v, bool edge) {
    vc<pair<int, int>> up, down;
    while (true) {
      if (head[u] == head[v]) break;
      if (LID[u] < LID[v]) {
        down.eb(LID[head[v]], LID[v]);
        v = parent[head[v]];
      } else {
        up.eb(LID[u], LID[head[u]]);
        u = parent[head[u]];
      }
    }
    if (LID[u] < LID[v]){
		down.eb(LID[u] + edge, LID[v]);
	}else if (LID[v] + edge <= LID[u]) up.eb(LID[u], LID[v] + edge);
    reverse(rng(down));
    up.insert(up.end(), rng(down));
    return up;
  }

  // restore_path(u, v): get_path_decomposition() の結果から、実際の頂点列（パス）を復元して返す。
  vc<int> restore_path(int u, int v) {
    vc<int> P;
    for (auto &&[a, b] : get_path_decomposition(u, v, 0)) {
      if (a <= b) {
        srep(i, a, b + 1) P.eb(V[i]);
      } else {
        for(ll i=b-1;i>=a+1;--i)P.eb(V[i]);
      }
    }
    return P;
  } 
  
  // path [a,b] と [c,d] の交わり. 空ならば {-1,-1}.
  // https://codeforces.com/problemset/problem/500/G
  pair<int, int> path_intersection(int a, int b, int c, int d) {
    int ab = lca(a, b), ac = lca(a, c), ad = lca(a, d);
    int bc = lca(b, c), bd = lca(b, d), cd = lca(c, d);
    int x = ab ^ ac ^ bc, y = ab ^ ad ^ bd; // meet(a,b,c), meet(a,b,d)
    if (x != y) return {x, y};
    int z = ac ^ ad ^ cd;
    if (x != z) x = -1;
    return {x, x};
  }

   // uv path 上で check(v) を満たす最後の v
  // なければ （つまり check(v) が ng ）-1

  template <class F>
  int max_path(F check, int u, int v) {
    if (!check(u)) return -1;
    auto pd = get_path_decomposition(u, v, false);
    for (auto [a, b]: pd) {
      if (!check(V[a])) return u;
      if (check(V[b])) {
        u = V[b];
        continue;
      }
      int c = binary_search([&](int c) -> bool { return check(V[c]); }, a, b, 0);
      return V[c];
    }
    return u;
  }

};

