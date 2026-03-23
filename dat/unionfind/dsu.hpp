// Disjoint Set Union (DSU) 構造体（Union-Find）
// 各要素の集合管理や統合を高速に行うためのデータ構造
struct Dsu {
private:
    int N;                    // 現在の集合の個数
    std::vector<int> P;       // 各要素の親情報。負の場合は根であり、その絶対値は集合のサイズを表す
    std::vector<int> H;       // 各要素に対応するラベル。集合の代表元に対してラベルが設定される

public:
    // デフォルトコンストラクタ：空のDSUを生成
    Dsu() : N(0) {}

    // n個の要素で初期化するコンストラクタ
    // 各要素は最初は独立した集合として扱われ、ラベルは自分自身に設定される
    Dsu(int n) : N(n), P(n, -1), H(n) {
        for (int i = 0; i < n; i++) {
            H[i] = i;
        }
    }

    // leader(u): 要素uが属する集合の代表元（根）を返す
    // パス圧縮を利用して、探索を高速化する
    int leader(int u) {
        if (P[u] < 0) return u;  // 自分自身が根ならそのまま返す
        int v = P[u];
        // 親が根になるまでたどる。途中でパス圧縮を行い、uの親を更新する
        while (P[v] >= 0) {
            P[u] = P[v];
            u = v;
            v = P[v];
        }
        return P[u];
    }

    // append(label): 新たな要素を追加し、指定したラベルを設定する
    // 追加された要素のインデックスを返す
    int append(int label) {
        int n = P.size();
        P.push_back(-1);   // 新しい要素は根（単独の集合）として追加される
        H.push_back(label);  // 指定されたラベルを設定
        return n;
    }

    // append(): 新たな要素を追加し、要素数をラベルとして設定する（デフォルトのラベル）
    int append() { 
        return append(int(P.size())); 
    }

    // label(u): 要素uが属する集合の代表元に設定されたラベルを返す
    int label(int u) { 
        return H[leader(u)]; 
    }

    // operator[]: 添字演算子のオーバーロード
    // 要素uが属する集合の代表元に設定されたラベルを返す
    int operator[](int u) { 
        return H[leader(u)]; 
    }

    // merge(u, v, newLabel): 要素uとvの属する集合を統合する
    // 統合後、代表元のラベルをnewLabelに更新する
    void merge(int u, int v, int newLabel) {
        u = leader(u);
        v = leader(v);
        // 既に同じ集合の場合は、ラベルを更新して終了
        if (u == v) { 
            H[u] = newLabel; 
            return; 
        }
        N--; // 統合により集合の個数が1減る
        // union by size: 小さい集合を大きい集合に統合する
        if (-P[u] < -P[v]) 
            std::swap(u, v);
        P[u] += P[v];         // uの集合サイズを更新
        // vの親をuに設定し、uに対してラベルnewLabelを設定する
        H[P[v] = u] = newLabel;
    }

    // merge(u, v): 要素uとvの属する集合を統合する（ラベルはuのものを保持）
    // 統合後の代表元としてuを採用する
    int merge(int u, int v) { 
        merge(u, v, u); 
        return u; 
    }

    // count(): 現在の互いに素な集合の個数（連結成分の数）を返す
    int count() { 
        return N; 
    }

    // size(u): 要素uが属する集合のサイズ（要素数）を返す
    int size(int u) { 
        return -P[leader(u)]; 
    }

    // same(u, v): 要素uとvが同じ集合に属するかどうかを判定する
    bool same(int u, int v) { 
        return leader(u) == leader(v); 
    }
};
