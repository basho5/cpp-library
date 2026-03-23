// Edge<cost> : グラフの辺 (src->to, 重みcost)
template <typename cost>
struct Edge {
  int src, to;
  cost c;   // 辺の重み (Cost -> cost に改名)
  Edge(int s, int t, cost cc = 1) : src(s), to(t), c(cc) {}
  // "operator int()" は、Edgeを int へ暗黙変換するとき "to" を返す
  operator int() const { return to; }
};

// Graph<cost> : 辺の重み型を cost としたグラフ
template <typename cost>
struct Graph : vector<vector<Edge<cost>>> {
  Graph(int n) : vector<vector<Edge<cost>>>(n) {}
  // add_edge(s,t,c) : s->t に重み c の辺を加える (有向)
  void add_edge(int s, int t, cost c = 1) {
    (*this)[s].emplace_back(s, t, c);
  }
};

template <typename cost, typename dat,
          dat (*mergeF)(dat, dat),
          dat (*eF)(),
          dat (*leafF)(),
          dat (*applyF)(dat, int, int, cost)>
struct Rerooting : Graph<cost> {
  vector<dat> dp, memo;

  Rerooting(int n) : Graph<cost>(n) {}

  // run(): 全方位木DPを実行し、各頂点の最終DPを返す
  vector<dat> reroot() {
    memo.resize(this->size(), eF());
    dp.resize(this->size());
    dfs1(0, -1);
    dfs2(0, -1, eF());
    return dp;
  }

  // dfs1: 子から親への集約 (メモ用)
  void dfs1(int c, int p) {
    bool upd = false;
    for (Edge<cost> &ed : (*this)[c]) {
      if (ed == p) continue;
      dfs1(ed, c);
      upd = true;
      // memo[c] に merge で合成
      // applyF(memo[子], 子頂点, 親頂点, 辺コスト)
      memo[c] = mergeF(memo[c], applyF(memo[ed], ed, c, ed.c));
    }
    if (!upd) memo[c] = leafF(); // 子を持たない(葉)なら leafF()
  }

  // dfs2: 親->子へ情報を再配分して、dp[c] (全方位DP) を作る
  void dfs2(int c, int p, const dat &val) {
    // ds[] に 親からの情報 val と、各子からの情報を格納
    vector<dat> ds{val};
    for (Edge<cost> &ed : (*this)[c]) {
      if (ed == p) continue;
      ds.push_back(applyF(memo[ed], ed, c, ed.c));
    }
    int n = (int)ds.size(), idx = 1;

    // 左右からの累積merge
    vector<dat> head(n+1, eF()), tail(n+1, eF());
    for (int i = 0; i++ < n;) {
      head[i] = mergeF(head[i-1], ds[i-1]);
    }
    for (int i = n; i-- > 0;) {
      tail[i] = mergeF(tail[i+1], ds[i]);
    }

    // dp[c] = head[n] ( = 全部合成した結果 )
    dp[c] = head[n];

    // 子へ再帰: 子に渡す情報を sub として計算
    for (Edge<cost> &ed : (*this)[c]) {
      if (ed == p) continue;
      dat sub = mergeF(head[idx], tail[idx+1]);
      // applyF(sub, c, ed, ed.c) => 親情報を子視点へ変換
      dfs2(ed, c, applyF(sub, c, ed, ed.c));
      idx++;
    }
  }
};

/*
  Rerooting<cost, dat,
            dat (*merge)(dat,dat),
            dat (*e)(),
            dat (*leaf)(),
            dat (*apply)(dat, int, int, cost)>
   について:

   - cost : 辺コストの型
   - dat  : 各頂点や部分木ごとのDPの型
   - merge(dat,dat)->dat : 子DPをまとめるときの演算
   - e()->dat            : merge の単位元
   - leaf()->dat         : 「葉のときの初期値」
   - apply(dat a, int c, int p, cost w)->dat
       子aの情報を、親(c視点)へ変換するときに使う (辺コストwを考慮など)
*/
