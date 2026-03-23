//----------------------------------------------------------
// Edge 構造体
//----------------------------------------------------------
/*
  Edge 構造体は、グラフの辺を表します。
  メンバ:
    - frm: 辺の始点
    - to: 辺の終点
    - cost: 辺の重み（デフォルトは 1）
    - id: 辺の識別番号（入力順など）
*/
template <typename T = int>
struct Edge {
    int frm, to;
    T cost;
    int id;
};

//----------------------------------------------------------
// Graph 構造体
//----------------------------------------------------------
/*
  Graph 構造体は、辺の追加から始まり、build() を呼ぶことで
  CSR (Compressed Sparse Row) 形式に変換され、各頂点から出る辺へ高速にアクセスできるようになります。
  テンプレート引数 T は辺の重みの型、directed は有向グラフか否かを指定します。
*/
// Graph 構造体
// directed が false の場合は無向グラフとして、双方向に辺を張る
template <typename T = int, bool directed = false>
struct Graph {
    static constexpr bool is_directed = directed;
    int N, M;
    using cost_type = T;
    using edge_type = Edge<T>;
    // 辺の登録用配列
    vector<edge_type> edges;
    // CSR 形式構築用の配列
    vector<int> indptr;
    vector<edge_type> csr_edges;
    // 各頂点の次数（後で計算するため）
    vector<int> vc_deg, vc_indeg, vc_outdeg;
    bool prepared;

    // コンストラクタ
    Graph() : N(0), M(0), prepared(false) { }
    Graph(int N) : N(N), M(0), prepared(false) { }

    // build(n) : グラフの再構築（N を再設定し、内部の配列をクリア）
    void build(int n) {
        N = n;
        M = 0;
        prepared = false;
        edges.clear();
        indptr.clear();
        csr_edges.clear();
        vc_deg.clear();
        vc_indeg.clear();
        vc_outdeg.clear();
    }

    // add() : 辺を追加する。
    // prepared == false で呼ぶ必要があります。
    void add(int frm, int to, T cost = 1, int i = -1) {
        assert(!prepared);
        assert(frm >= 0 && to >= 0 && to < N);
        if(i == -1) i = M;
        edge_type e = {frm, to, cost, i};
        edges.push_back(e);
        ++M;
    }

	bool is_prepared(){return prepared ;}

    // read_tree: 木の場合、辺数は N-1 本として読み込む。
	// wt は重みがあるかないか
	// offsetは1-indexにするか
    void read_tree(bool wt = false, int off = 1) { read_graph(N - 1, wt, off); }

    // read_graph: 辺数 M 本のグラフを読み込み、各辺を追加し build() を呼ぶ
    void read_graph(int M, bool wt = false, int off = 1) {
        for (int m = 0; m < M; ++m) {
            int a, b;
            // ※ ここでは標準入力から読み込む例（実際は fastio 等の関数を使うことも可能）
            cin >> a >> b;
            a -= off; b -= off;
            if (!wt) {
                add(a, b);
            } else {
                T c;
                cin >> c;
                add(a, b, c);
            }
        }
        build();
    }

    // build() : 辺の集合から CSR 形式のデータ構造 (indptr, csr_edges) を構築する
    void build() {
        assert(!prepared);
        prepared = true;
        indptr.assign(N + 1, 0);
        for (auto &e: edges) {
            indptr[e.frm + 1]++;
            if (!directed)
                indptr[e.to + 1]++;
        }
        for (int v = 0; v < N; ++v) {
            indptr[v + 1] += indptr[v];
        }
        vector<int> counter = indptr;
        // 注意: 元のコードでは csr_edges.resize(indptr.back() + 1) となっていましたが、
        // CSR 形式では通常要素数 = indptr.back() です。
        csr_edges.resize(indptr.back());
        for (auto &e: edges) {
            csr_edges[counter[e.frm]++] = e;
            if (!directed) {
                // 無向の場合は反対向きの辺も追加する
                edge_type rev = {e.to, e.frm, e.cost, e.id};
                csr_edges[counter[e.to]++] = rev;
            }
        }
    }

    // OutgoingEdges クラス：頂点 v の出る辺の範囲をイテレートするためのクラス
    class OutgoingEdges {
    public:
        OutgoingEdges(const Graph* G, int l, int r) : G(G), l(l), r(r) {}
        const edge_type* begin() const {
            if (l == r) { return nullptr; }
            return &G->csr_edges[l];
        }
        const edge_type* end() const {
            if (l == r) { return nullptr; }
            return &G->csr_edges[r];
        }
    private:
        const Graph* G;
        int l, r;
    };

    // operator[] : 頂点 v の出る辺を OutgoingEdges として返す
    OutgoingEdges operator[](int v) const {
        assert(prepared);
        return OutgoingEdges(this, indptr[v], indptr[v + 1]);
    }

    // deg_array: 各頂点の次数を返す（vc_deg を計算してキャッシュ）
    vector<int> deg_array() {
        if (vc_deg.empty()) calc_deg();
        return vc_deg;
    }

    // deg_array_inout: 入次数と出次数のペアを返す
    pair<vector<int>, vector<int>> deg_array_inout() {
        if (vc_indeg.empty()) calc_deg_inout();
        return {vc_indeg, vc_outdeg};
    }

    int deg(int v) {
        if (vc_deg.empty()) calc_deg();
        return vc_deg[v];
    }
    int in_deg(int v) {
        if (vc_indeg.empty()) calc_deg_inout();
        return vc_indeg[v];
    }
    int out_deg(int v) {
        if (vc_outdeg.empty()) calc_deg_inout();
        return vc_outdeg[v];
    }


    // rearrange: 指定された頂点集合 V に基づいて、新しいグラフを作る
    Graph<T, directed> rearrange(vector<int> V_order, bool keep_eid = false) {
        if (new_idx.size() != static_cast<size_t>(N))
            new_idx.assign(N, -1);
        if (used_e.size() != static_cast<size_t>(M))
            used_e.assign(M, false);
        int n = V_order.size();
        for (int i = 0; i < n; i++) {
            new_idx[V_order[i]] = i;
        }
        Graph<T, directed> newG(n);
        vector<int> history;
        for (int i = 0; i < n; i++) {
            for (auto &e: (*this)[V_order[i]]) {
                if (used_e[e.id]) continue;
                int a = e.frm, b = e.to;
                if (new_idx[a] != -1 && new_idx[b] != -1) {
                    history.push_back(e.id);
                    used_e[e.id] = true;
                    int eid = (keep_eid ? e.id : -1);
                    newG.add(new_idx[a], new_idx[b], e.cost, eid);
                }
            }
        }
        for (int i = 0; i < n; i++) {
            new_idx[V_order[i]] = -1;
        }
        for (int eid: history)
            used_e[eid] = false;
        newG.build();
        return newG;
    }

	Graph<T, true> to_directed_tree(int root = -1) {
		if (root == -1) root = 0;
		assert(!is_directed && prepared && M == N - 1);
		Graph<T, true> G1(N);
		vc<int> par(N, -1);
		auto dfs = [&](auto& dfs, int v) -> void {
		  for (auto& e: (*this)[v]) {
			if (e.to == par[v]) continue;
			par[e.to] = v, dfs(dfs, e.to);
		  }
		};
		dfs(dfs, root);
		for (auto& e: edges) {
		  int a = e.frm, b = e.to;
		  if (par[a] == b) swap(a, b);
		  assert(par[b] == a);
		  G1.add(a, b, e.cost);
		}
		G1.build();
		return G1;
  }


private:
    vector<int> new_idx;
    vector<bool> used_e;

    // calc_deg: 各頂点の次数を計算する
    void calc_deg() {
        assert(vc_deg.empty());
        vc_deg.resize(N);
        for (auto &e: edges) {
            vc_deg[e.frm]++;
            vc_deg[e.to]++;
        }
    }
    // calc_deg_inout: 入次数と出次数を計算する
    void calc_deg_inout() {
        assert(vc_indeg.empty());
        vc_indeg.resize(N);
        vc_outdeg.resize(N);
        for (auto &e: edges) {
            vc_indeg[e.to]++;
            vc_outdeg[e.frm]++;
        }
    }
};
