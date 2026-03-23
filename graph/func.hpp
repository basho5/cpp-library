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

// N が根となる木を新たに作る
// 関数グラフ：各頂点から出る辺が 1 本あるグラフ（つまり a_i が与えられる）
// この構造体は、各頂点から出る辺の先を TO に、辺の重みを wt に保持し、
// 人工根（頂点番号 N）を追加して全体を1つの木に変換する処理などを行う。
template <typename T = int>
struct FunctionalGraph {
  int N, M;           // N: 頂点数, M: 登録された辺の本数（関数グラフでは M == N になる）
  vc<int> TO;         // 各頂点 i から出る辺の先（a_i の情報）
  vc<T> wt;           // 各頂点 i の辺の重み。通常は 1
  vc<int> root;       // 各頂点が属する成分のサイクル代表。サイクルに属する頂点は、その代表を root[v] に記録する
  Graph<T, 1> G;      // 変換後のグラフ。人工根付きの有向グラフ（directed = true）
  
  // コンストラクタ
  FunctionalGraph() {}
  FunctionalGraph(int N) : N(N), M(0), TO(N, -1), wt(N), root(N, -1) {}

  // add(a, b, c): 頂点 a から b への辺を追加する。
  // すでに a からの辺が登録されていないかを assert で確認する（関数グラフなので各頂点は必ず1本の辺を持つ）。
  void add(int a, int b, T c = 1) {
    assert(0 <= a && a < N);
    assert(TO[a] == -1);  // 既に辺が存在しないことを保証
    ++M;
    TO[a] = b;
    wt[a] = c;
  }

  // build():
  // 1. DSU を用いて、各頂点が属する成分内でサイクルを検出し、
  //    サイクルに属する頂点は root[v] = v として記録する。
  // 2. DSU により得た代表情報から、各頂点の root[v] を更新する。
  // 3. 人工根（頂点番号 N）を追加して、各成分を1つの木に変換する。
  //    - サイクル代表の場合は、人工根からその頂点へ辺を張る。
  //    - それ以外は、元の辺（TO[v] -> v）の逆向きで張る。
  // 4. 変換後のグラフ G を build() して、Tree 構造体 (後述) を作成し、返す。
  pair<Graph<T, 1>, Tree<Graph<T, 1>>> build() {
    assert(N == M);  // 各頂点から必ず1本の辺が登録されている前提
    UnionFind uf(N);
    // 各頂点 v について、uf.merge(v, TO[v]) を試みる。
    // もし既に同じ集合に属していればサイクルの一部と判断し、root[v] を v とする。
    rep(v, N) {
      if (!uf.merge(v, TO[v])) { 
        root[v] = v; 
      }
    }
    // サイクル代表情報の補正
    rep(v, N) {
      if (root[v] == v)
        root[uf[v]] = v;  // もし v がサイクル代表なら、その集合に属する頂点の root を v に設定
    }
    rep(v, N) {
      root[v] = root[uf[v]];  // 各頂点 v の root[v] を最終的な代表で更新
    }
    
    // 新しいグラフ G の構築：頂点数は N+1（元の頂点 0～N-1 と、人工根 N）
    G.build(N + 1);
    rep(v, N) {
      if (root[v] == v)
        // サイクル代表の場合、人工根 (N) から v への辺を張る
        G.add(N, v, wt[v]);
      else
        // それ以外の場合、元の辺の向きを逆転させ、TO[v] から v への辺を張る
        G.add(TO[v], v, wt[v]);
    }
    G.build();
    // 人工根 N を根として Tree 構造体を構築
    Tree<Graph<T, 1>> tree(G, N);
    return {G, tree};
  }

  // dist() : 関数グラフ上で、頂点 a から頂点 b へ到達するために必要な「回数」（ステップ数）を O(1) で返す。
  // もし到達不可能なら infty<int> を返す。
  template <typename TREE>
  int dist(TREE& tree, int a, int b) {
    if (tree.in_subtree(a, b)) 
      return tree.depth[a] - tree.depth[b];
    int r = root[a];
    int btm = TO[r]; // サイクル代表 r の次の頂点
    // a -> r -> btm -> b というルートを想定
    if (tree.in_subtree(btm, b)) {
      int x = tree.depth[a] - tree.depth[r]; // a から r までの距離
      x += 1;                                // r から btm への 1 ステップ
      x += tree.depth[btm] - tree.depth[b];    // btm から b までの距離
      return x;
    }
    return INF; // 到達不可能の場合は無限大（infty<int>）を返す
  }

  // jump() : TREE の情報を利用して、頂点 v から関数グラフ上で step 回進んだ頂点を求める。
  // 基本的な考え方：
  //   - まず、v の木部分での深さを tree.depth[v] とし、
  //     step が木部分内で収まる場合は、tree.jump() で直接求める。
  //   - それ以外の場合、v をサイクル部分へ移動させ、残りの step をサイクル部分の長さで mod した上で、
  //     サイクル内でその位置に対応する頂点を求める。
  template <typename TREE>
  int jump(TREE& tree, int v, ll step) {
    int d = tree.depth[v];
    if (step <= d - 1) 
      return tree.jump(v, N, step);
    v = root[v];         // サイクル部分に移動
    step -= d - 1;       // 木部分で消費した分を引く
    int bottom = TO[v];  // サイクル代表 v の次の頂点（サイクルの先頭）
    int c = tree.depth[bottom]; // サイクル部分の長さ（木として見た深さ）
    step %= c;           // サイクル部分での残り step を mod する
    if (step == 0) 
      return v;
    return tree.jump(bottom, N, step - 1);
  }

  // jump_all() : 全頂点について、関数グラフ上で step 回進んだ先の頂点を一括で求める。
  // 各頂点 v に対して、結果を res[v] に格納する。
  // DFS とクエリ登録を用いて、Euler Tour 順の情報から各頂点について答えを決定する。
  template <typename TREE>
  vc<int> jump_all(TREE& tree, ll step) {
    vc<int> res(N, -1);
    // 各頂点 v のクエリを、(v, k) のペアとして query[v] に登録する。
    // ここで k は、Euler Tour の配列上で、v の位置から先に進むべきインデックスの差を表す。
    vv<pair<int, int>> query(N);
    rep(v, N) {
      int d = tree.depth[v];
      int r = root[v];
      if (d - 1 > step) {
        query[v].push_back({v, step});
      }
      if (d - 1 <= step) {
        ll k = step - (d - 1);
        int bottom = TO[r];
        int c = tree.depth[bottom];
        k %= c;
        if (k == 0) {
          res[v] = r;
          continue;
        }
        query[bottom].push_back({v, k - 1});
      }
    }

    vc<int> path;  // DFS 中の Euler Tour 順の経路を保持するスタック
    // DFS を使って、登録されたクエリに応じた結果を res に書き込む
    auto dfs = [&](auto& dfs, int v) -> void {
      path.push_back(v);
      for (auto &p: query[v]) {
        int w = p.first, k = p.second;
        res[w] = path[path.size() - 1 - k];
      }
      for (auto &e: G[v])
        dfs(dfs, e.to);
      path.pop_back();
    };
    // 人工根は G[N] に登録されているので、その子から DFS を開始する
    for (auto &e: G[N]) { dfs(dfs, e.to); }
    return res;
  }

  // in_cycle() : TREE の情報を利用して、頂点 v が関数グラフのサイクル部分に属しているかを判定する。
  // 具体的には、v の成分のサイクル代表 r を求め、r の次の頂点 bottom から見て、
  // v が bottom の部分木に入っているなら、サイクルに属しているとみなす。
  template <typename TREE>
  bool in_cycle(TREE& tree, int v) {
    int r = root[v];
    int bottom = TO[r];
    return tree.in_subtree(bottom, v);
  }

  // collect_cycle() : サイクル代表 r を指定して、その成分内のサイクルに属するすべての頂点を、
  // サイクル順に収集した配列を返す。
  // 具体的には、r から TO[r] をたどり、r に戻るまでの頂点列を返す。
  vc<int> collect_cycle(int r) {
    assert(r == root[r]);
    vc<int> cyc;
    cyc.push_back(TO[r]);
    while (cyc.back() != r)
      cyc.push_back(TO[cyc.back()]);
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
// [G, Tree]=fg.build() ;
