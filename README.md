# 競技プログラミング C++ ライブラリ

競技プログラミングでよく使うデータ構造・アルゴリズムをまとめた **ヘッダオンリーライブラリ** です。
C++17 標準ライブラリのみに依存し、外部ライブラリは不要です。

---

## インストール

```bash
git clone <repository-url>
```

コンパイル時にインクルードパスを通して使用します。

```bash
g++ -std=c++17 -O2 -I/path/to/library main.cpp -o main
```

---

## モジュール一覧

| カテゴリ                                 | パス          | 概要                                                               |
| ---------------------------------------- | ------------- | ------------------------------------------------------------------ |
| [代数構造](#alg---代数構造)              | `alg/`        | モノイド・作用付きモノイド                                         |
| [データ構造](#dat---データ構造)          | `dat/`        | BIT, セグ木, 遅延セグ木, Union-Find, 平衡二分木, Wavelet Matrix 等 |
| [グラフ](#graph---グラフ)                | `graph/`      | Graph構造体, HLD, 最短経路, 全方位木DP, Functional Graph 等        |
| [モジュラー算術](#mod---モジュラー算術)  | `mod/`        | modint, 階乗, 二項係数, CRT                                        |
| [整数論](#nt---整数論)                   | `nt/`         | 素因数分解, 素数判定, 篩, ゼータ・メビウス変換 等                  |
| [形式的べき級数](#fps---形式的べき級数)  | `fps/`        | FPS, NTT, 畳み込み, log/exp/pow/sqrt, Bostan-Mori                  |
| [文字列](#string---文字列)               | `string/`     | Rolling Hash, Manacher, LCS, Trie/Aho-Corasick 等                  |
| [数列](#seq---数列)                      | `seq/`        | LIS, 転倒数, MEX, 区間和集合, 最大長方形 等                        |
| [幾何](#geo---幾何)                      | `geo/`        | 2D点/ベクトル, 円, マンハッタンMST                                 |
| [線形代数](#linalg---線形代数)           | `linalg/`     | 行列演算, 行列累乗, 行列式, ガウス消去                             |
| [ナップサック](#knapsack---ナップサック) | `knapsack/`   | 4種のナップサック解法                                              |
| [多倍長整数](#bigint---多倍長整数)       | `bigint/`     | 任意精度整数演算                                                   |
| [日時](#datetime---日時)                 | `datetime/`   | 日付演算・曜日計算                                                 |
| [乱数](#random---乱数)                   | `random/`     | XORShift乱数生成                                                   |
| [セグ木使用例](#segtree---セグ木使用例)  | `segtree/`    | セグメント木の問題別使用例集                                       |
| [ACL](#ac-library---atcoder-library)     | `ac-library/` | AtCoder Library ミラー                                             |

---

## alg - 代数構造

セグメント木・遅延セグメント木・平衡二分木に渡すためのモノイド・作用付きモノイドを定義するモジュール。

### monoid/ - モノイド

モノイド $(S, \cdot, e)$ を `struct` として定義する。各 struct は以下を提供する。

- `using X = ...` / `using value_type = ...` — 値の型
- `static X op(X, X)` — 二項演算
- `static X unit()` — 単位元
- `static constexpr bool commute` — 可換かどうか

#### 一覧

| ファイル         | 構造体                           | テンプレート | 演算                  | 単位元               | 可換 | 備考                                                 |
| ---------------- | -------------------------------- | ------------ | --------------------- | -------------------- | ---- | ---------------------------------------------------- |
| `add.hpp`        | `Monoid_Add<E>`                  | `E`          | $x + y$               | $0$                  | Yes  | `inverse`, `power` あり                              |
| `add_pair.hpp`   | `Monoid_Add_Pair<E>`             | `E`          | 成分ごと加算          | $(0, 0)$             | Yes  | `inverse` あり                                       |
| `add_array.hpp`  | `Monoid_Add_Array<E, K>`         | `E, int K`   | 成分ごと加算          | $\mathbf{0}$         | Yes  | `inverse`, `power` あり                              |
| `affine.hpp`     | `Monoid_Affine<K>`               | `K`          | $f \circ g$ (合成)    | $(1, 0)$             | No   | $f(x) = ax + b$, `eval`, `inverse` あり              |
| `assign.hpp`     | `Monoid_Assign<X, none_val>`     | `X, int`     | 後勝ち代入            | `none_val`           | No   | センチネル値で無操作を表現                           |
| `max.hpp`        | `Monoid_Max<E>`                  | `E`          | $\max(x, y)$          | $-\infty$            | Yes  |                                                      |
| `max_id.hpp`     | `Monoid_Max_Idx<T, tie_is_left>` | `T, bool`    | 最大値 + インデックス | $(-\infty, -1)$      | Yes  | タイブレーク設定可                                   |
| `min.hpp`        | `Monoid_Min<E>`                  | `E`          | $\min(x, y)$          | $+\infty$            | Yes  |                                                      |
| `min_id.hpp`     | `Monoid_Min_Idx<T, tie_is_left>` | `T, bool`    | 最小値 + インデックス | $(+\infty, -1)$      | Yes  | タイブレーク設定可                                   |
| `minmax.hpp`     | `Monoid_MinMax<X>`               | `X`          | 区間min/max同時管理   | $(+\infty, -\infty)$ | Yes  | `from_element(x)` あり                               |
| `monoid_pow.hpp` | —                                | `Monoid`     | モノイド冪乗          | —                    | —    | `power` メソッドがあれば利用、なければ繰り返し二乗法 |

### acted_monoid/ - 作用付きモノイド

遅延セグメント木用。`Monoid_X` (データ), `Monoid_A` (作用), `act(x, a, size)` を定義する。

#### 命名規則: `ActedMonoid_{データ}_{作用}`

| ファイル               | 構造体                               | X (データ)                    | A (作用)     | act の意味                                        |
| ---------------------- | ------------------------------------ | ----------------------------- | ------------ | ------------------------------------------------- |
| `sum_add.hpp`          | `ActedMonoid_Sum_Add<E>`             | 区間和                        | 加算         | $x + a \times \text{size}$                        |
| `sum_affine.hpp`       | `ActedMonoid_Sum_Affine<E>`          | 区間和                        | アフィン変換 | $x \cdot a + b \times \text{size}$                |
| `sum_assign.hpp`       | `ActedMonoid_Sum_Assign<E, none>`    | 区間和                        | 代入         | $a \times \text{size}$                            |
| `cntsum_add.hpp`       | `ActedMonoid_CntSum_Add<E>`          | (個数, 和)                    | 加算         | 和に $\text{cnt} \times a$ を加算                 |
| `cntsum_affine.hpp`    | `ActedMonoid_CntSum_Affine<E>`       | (個数, 和)                    | アフィン変換 | 和を $\text{sum} \cdot a + \text{cnt} \cdot b$ に |
| `max_add.hpp`          | `ActedMonoid_Max_Add<E>`             | 区間max                       | 加算         | $x + a$                                           |
| `max_assign.hpp`       | `ActedMonoid_Max_Assign<E, none>`    | 区間max                       | 代入         | $a$                                               |
| `max_max.hpp`          | `ActedMonoid_Max_Max<E>`             | 区間max                       | chmax        | $\max(x, a)$                                      |
| `max_min.hpp`          | `ActedMonoid_Max_Min<E>`             | 区間max                       | chmin        | $\min(x, a)$                                      |
| `maxid_add.hpp`        | `ActedMonoid_MaxIdx_Add<E>`          | 最大値+idx                    | 加算         | $(\text{val} + a, \text{idx})$                    |
| `min_add.hpp`          | `ActedMonoid_Min_Add<E>`             | 区間min                       | 加算         | $x + a$                                           |
| `min_assign.hpp`       | `ActedMonoid_Min_Assign<E, none>`    | 区間min                       | 代入         | $a$                                               |
| `min_max.hpp`          | `ActedMonoid_Min_Max<E>`             | 区間min                       | chmax        | $\max(x, a)$                                      |
| `min_min.hpp`          | `ActedMonoid_Min_Min<E>`             | 区間min                       | chmin        | $\min(x, a)$                                      |
| `minid_add.hpp`        | `ActedMonoid_MinIdx_Add<E>`          | 最小値+idx                    | 加算         | $(\text{val} + a, \text{idx})$                    |
| `powersums_add.hpp`    | `ActedMonoid_Power_Sums_Add<T>`      | べき乗和 $[s_0, s_1, s_2]$    | 加算         | $s_k' = \sum (x_i + a)^k$                         |
| `powersums_assign.hpp` | `ActedMonoid_Power_Sums_Assign<T,K>` | べき乗和 $[s_0, \ldots, s_K]$ | 代入         | $s_k = \text{cnt} \cdot a^k$                      |

### 使い方

```cpp
#include "alg/monoid/add.hpp"
#include "alg/acted_monoid/sum_add.hpp"
#include "dat/segtree/segtree.hpp"
#include "dat/segtree/lazy_segtree.hpp"

// セグメント木 (区間和クエリ)
SegTree<Monoid_Add<ll>> seg(N);

// 遅延セグメント木 (区間加算・区間和クエリ)
Lazy_SegTree<ActedMonoid_Sum_Add<ll>> lazy_seg(N);
```

---

## dat - データ構造

### fenwicktree/ - Binary Indexed Tree (BIT)

#### `BIT<T>` — `bit.hpp`

1次元 Fenwick Tree。0-indexed。

```cpp
BIT<ll> bit(N);          // サイズ N で初期化
bit.add(i, x);           // a[i] += x
bit.sum(i);              // a[0] + ... + a[i-1]
bit.sum(l, r);           // a[l] + ... + a[r-1]
bit.lower_bound(k);      // prefix sum >= k となる最小 index
```

| メソッド               | 計算量      |
| ---------------------- | ----------- |
| `add(i, x)`            | $O(\log N)$ |
| `sum(i)` / `sum(l, r)` | $O(\log N)$ |
| `lower_bound(k)`       | $O(\log N)$ |

#### `BIT_2D<T>` — `bit2d.hpp`

2次元 Fenwick Tree。

```cpp
BIT_2D<ll> bit(H, W);
bit.add(i, j, x);        // a[i][j] += x
bit.sum(i, j);            // [0,i) × [0,j) の矩形和
```

| メソッド       | 計算量                   |
| -------------- | ------------------------ |
| `add(i, j, x)` | $O(\log H \cdot \log W)$ |
| `sum(i, j)`    | $O(\log H \cdot \log W)$ |

#### `setbit` — `setbit.hpp`

BIT を利用した順序統計量つき集合。値域 $[1, N]$。

```cpp
setbit sb(N);
sb.insert(a);             // 要素 a を追加
sb.erase(a);              // 要素 a を削除
sb.index(a);              // a より小さい要素数
sb.find_kth(k);           // k 番目に小さい要素 (0-indexed)
```

| メソッド                                  | 計算量      |
| ----------------------------------------- | ----------- |
| `insert` / `erase` / `index` / `find_kth` | $O(\log N)$ |

---

### segtree/ - セグメント木

#### `SegTree<Monoid>` — `segtree.hpp`

モノイドに対するセグメント木。0-indexed, 半開区間 $[l, r)$。

```cpp
SegTree<Monoid_Max<int>> seg(v);  // vector から構築
seg.set(i, x);                     // a[i] = x
seg.get(i);                        // a[i]
seg.prod(l, r);                    // op(a[l], ..., a[r-1])
seg.prod_all();                    // 全体の積
seg.max_right(check, l);           // check(prod(l..r)) が true な最大 r
seg.min_left(check, r);            // check(prod(l..r)) が true な最小 l
seg.multiply(i, x);                // a[i] = op(a[i], x)
```

| メソッド                                  | 計算量      |
| ----------------------------------------- | ----------- |
| 構築                                      | $O(N)$      |
| `set` / `prod` / `max_right` / `min_left` | $O(\log N)$ |
| `get` / `prod_all`                        | $O(1)$      |

#### `Lazy_SegTree<ActedMonoid>` — `lazy_segtree.hpp`

作用付きモノイドに対する遅延伝搬セグメント木。

```cpp
Lazy_SegTree<ActedMonoid_Sum_Add<ll>> seg(v);
seg.apply(l, r, a);               // 区間 [l, r) に作用 a を適用
seg.prod(l, r);                    // 区間積
seg.get(p);                        // 遅延評価を反映した a[p]
```

| メソッド                 | 計算量      |
| ------------------------ | ----------- |
| 構築                     | $O(N)$      |
| `apply` / `prod` / `get` | $O(\log N)$ |
| `max_right` / `min_left` | $O(\log N)$ |

---

### unionfind/ - Union-Find

#### `UnionFind` — `unionfind.hpp`

```cpp
UnionFind uf(N);
uf.merge(a, b);            // a と b を統合
uf.same(a, b);             // 同じ連結成分か判定
uf.leader(a);              // 代表元
uf.size(a);                // 連結成分サイズ
uf.groups();               // 全連結成分のリスト
```

| メソッド                             | 計算量         |
| ------------------------------------ | -------------- |
| `merge` / `same` / `leader` / `size` | $O(\alpha(N))$ |
| `groups`                             | $O(N)$         |

#### `Dsu` — `dsu.hpp`

動的に要素を追加できるラベル付き Union-Find。

```cpp
Dsu dsu;
int id = dsu.append(label);   // 新要素追加 (ラベル付き)
dsu.merge(u, v, newLabel);     // 統合しラベルを更新
dsu[u];                        // 代表ラベル
dsu.count();                   // 連結成分数
```

#### `weightedUF<T>` — `weightdsu.hpp`

重み付き Union-Find。$\text{weight}[b] - \text{weight}[a] = w$ の制約を管理。

```cpp
weightedUF<ll> uf(N);
uf.unite(a, b, w);            // weight[b] - weight[a] = w
uf.diff(a, b);                 // weight[b] - weight[a]
uf.same(a, b);                 // 同じ連結成分か
```

| メソッド | 計算量         |
| -------- | -------------- |
| 全操作   | $O(\alpha(N))$ |

---

### rbst/ - ランダム平衡二分木 (RBST)

暗黙の Treap。列の split/merge を $O(\log N)$ で行う。`PERSISTENT=true` で永続化可能。

#### `RBST<S>` — `rbst.hpp`

```cpp
RBST<int> rbst(MAX_NODES);
auto root = rbst.new_node(vec);           // vector から構築 O(N)
auto [l, r] = rbst.split(root, k);        // [0,k) と [k,n) に分割
root = rbst.merge(l, r);                   // 結合
rbst.get(root, k);                         // k 番目取得
rbst.set(root, k, val);                    // k 番目更新
rbst.reverse(root, l, r);                  // [l,r) を反転
```

#### `RBST_Monoid<Monoid>` — `rbst_monoid.hpp`

モノイド集約つき RBST。

```cpp
RBST_Monoid<Monoid_Add<ll>> rbst(MAX_NODES);
rbst.prod(root, l, r);                    // 区間積 O(log N)
```

#### `RBST_ActedMonoid<AM>` — `rbst_acted_monoid.hpp`

遅延伝搬つき RBST。

```cpp
RBST_ActedMonoid<ActedMonoid_Sum_Add<ll>> rbst(MAX_NODES);
rbst.apply(root, l, r, a);                // 区間作用 O(log N)
rbst.prod(root, l, r);                    // 区間積 O(log N)
```

---

### splaytree/ - スプレー木

ノードプール方式のスプレー木。ならし $O(\log N)$。

| ファイル                     | クラス                      | 説明                             |
| ---------------------------- | --------------------------- | -------------------------------- |
| `splaytree_basic.hpp`        | `SplayTree_Basic<S>`        | 基本的な列操作 (get/set/reverse) |
| `splaytree_monoid.hpp`       | `SplayTree_Monoid<Monoid>`  | モノイド集約つき                 |
| `splaytree_acted_monoid.hpp` | `SplayTree_ActedMonoid<AM>` | 遅延伝搬つき                     |

API は RBST と同様 (`split`, `merge`, `prod`, `apply`, `reverse` 等)。

---

### skiplist/ - スキップリスト

確率的平衡リスト。ランダムアクセス $O(\log N)$。

| ファイル       | クラス                | 説明                                  |
| -------------- | --------------------- | ------------------------------------- |
| `skiplist.hpp` | `SkipList<T>`         | 順序付きリスト (重複可・位置指定操作) |
| `set.hpp`      | `SkipListSet<T>`      | ユニーク集合 (`contains` が $O(1)$)   |
| `multiset.hpp` | `SkipListMultiSet<T>` | 多重集合 (`lower_bound`, `count` 等)  |

```cpp
SkipListSet<int> s;
s.add(x);                     // 挿入 O(log N)
s.remove(x);                  // 削除 O(log N)
s.contains(x);                // 存在判定 O(1) (ハッシュ)
s.get(k);                     // k 番目 O(log N)
s.lower_bound(x);             // x 以上の最小 index O(log N)
```

---

### wavelet_matrix/ - Wavelet Matrix

#### `WaveletMatrix<T>` — `waveletmatrix.hpp`

非負整数列に対する静的クエリ。構築 $O(N \log V)$、各クエリ $O(\log V)$ ($V$ は値の最大値)。

```cpp
WaveletMatrix<int> wm(vec);
wm.build();
wm.access(i);                        // a[i]
wm.rank(l, r, val);                  // [l,r) での val の出現回数
wm.range_freq(l, r, lo, hi);         // [l,r) で lo <= x < hi の個数
wm.k_th_smallest(l, r, k);           // [l,r) の k 番目に小さい値
wm.k_th_largest(l, r, k);            // [l,r) の k 番目に大きい値
wm.top_k_sum(l, r, k);               // [l,r) の小さい方 k 個の和
wm.prev_value(l, r, val);            // [l,r) で val 未満の最大値
wm.next_value(l, r, val);            // [l,r) で val 以上の最小値
```

#### `BITonWaveletMatrix<POS, VAL>` — `waveletmatrix2d.hpp`

2次元の点加算・矩形和クエリ。

```cpp
BITonWaveletMatrix<int, ll> wm2d;
wm2d.add_point(x, y);                // 点の登録
wm2d.build();
wm2d.add(x, y, val);                 // 加算 O(log N · log V)
wm2d.sum(lx, rx, ly, ry);            // 矩形和 O(log N · log V)
```

---

### hashmap.hpp - ハッシュマップ

```cpp
HashMap<int> mp;
mp[key] = val;                // key: ull → val: int
mp.get(key, default_val);    // デフォルト値つき取得
mp.count(key);                // 存在判定
mp.enumerate_all([](ull k, int v) { ... });  // 全走査
```

| メソッド                       | 計算量      |
| ------------------------------ | ----------- |
| `operator[]` / `get` / `count` | $O(1)$ 平均 |

### pbds.hpp - Policy Based Data Structure

GNU の `__gnu_pbds::tree` のラッパー。順序統計量つき平衡BST。

```cpp
pbds_set<int> s;
s.insert(x);
s.order_of_key(x);           // x 未満の要素数 O(log N)
s.find_by_order(k);          // k 番目の要素 O(log N)
```

---

## graph - グラフ

### Graph 構造体 — `graph.hpp`

CSR (Compressed Sparse Row) 形式のグラフ。

```cpp
Graph<int> G(N);                    // N 頂点、無向グラフ
Graph<ll, true> G(N);               // 重み付き有向グラフ
G.add(u, v, cost);                  // 辺追加
G.build();                          // CSR 構築 O(N+M)
G.read_tree(wt, off);              // 木を入力
G.read_graph(M, wt, off);         // グラフを入力

for (auto& e : G[v]) {             // 頂点 v の隣接辺
    // e.to, e.cost, e.id
}
```

### Tree / HLD — `tree.hpp`

Heavy-Light Decomposition つき木構造。パスクエリ・部分木クエリを $O(\log N)$ に分解。

```cpp
Tree<decltype(G)> tree(G, root);

tree.LCA(u, v);                     // 最小共通祖先 O(log N)
tree.LA(v, k);                      // k 番目の祖先 O(log N)
tree.dist(u, v);                    // 距離 (辺数) O(log N)
tree.dist_weighted(u, v);           // 重み付き距離 O(log N)
tree.jump(a, b, k);                 // a→b パス上で k 歩進む O(log N)
tree.subtree_size(v);               // 部分木サイズ O(1)
tree.in_subtree(a, b);              // a が b の部分木に含まれるか O(1)
tree.depth[v];                      // 深さ
tree.parent[v];                     // 親

// パスを Euler Tour 上の区間に分解
auto segs = tree.get_path_decomposition(u, v, edge);
for (auto [l, r] : segs) { ... }   // セグ木クエリに利用

tree.LID[v], tree.RID[v];          // 部分木の Euler Tour 区間
```

### 最短経路 — `shortest_path/`

#### `bfs01<T>(G, v)` — `bfs01.hpp`

0-1 BFS。辺コストが 0 or 1 のグラフ向け。

```cpp
auto [dist, par] = bfs01<int>(G, start);   // O(N+M)
```

#### `dijkstra<T>(G, v)` — `dijkstra.hpp`

```cpp
auto [dist, par] = dijkstra<ll>(G, start);           // O((N+M) log N)
auto [dist, par] = dijkstra<ll, decltype(G), true>(G, start);  // 密グラフ用 O(N²)
auto [dist, par, root] = dijkstra<ll>(G, starts);    // 多始点
```

#### `warshall_floyd<T>(G)` — `warshall_floyd.hpp`

全頂点対最短距離。$O(N^3)$。

```cpp
auto dist = warshall_floyd<ll>(G);    // dist[i][j]
```

#### `restore_path(par, t)` — `restore_path.hpp`

親配列からパス復元。$O(\text{path length})$。

```cpp
auto path = restore_path(par, target);
```

### 二部グラフ判定 — `bipartite.hpp`

```cpp
auto color = bipartite_vertex(G);   // O(N+M)
// color が空なら二部グラフでない
```

### トポロジカルソート — `toposort.hpp`

```cpp
auto ord = topo(g);                  // O(V+E), 閉路があれば空
auto [ord, unique] = utopo(g);       // 一意性も判定
auto ord = ltopo(g);                 // 辞書順最小 O((V+E) log V)
```

### 木の直径 — `diameter.hpp`

```cpp
auto [diam, path] = tree_diameter<ll>(G);   // O(N)
```

### 重心 — `gravity.hpp`

```cpp
int centroid = calc_g(adj);                  // O(N)
int centroid = calc_g(adj, weights);         // 重み付き O(N)
```

### 全方位木DP — `tree_dp/`

#### `Rerooting` — `reroot.hpp`

```cpp
Rerooting<decltype(tree), Data> dp(tree, f_ee, f_ev, f_ve, unit);
dp[v];                              // v を根としたときの値 O(1)
dp.get(v, root);                    // root を根としたときの v の部分木値 O(log N)
```

- `f_ee(Data, Data) → Data` — 子の値のマージ
- `f_ev(Data, int v) → Data` — 子の値 → 頂点の値
- `f_ve(Data, Edge) → Data` — 頂点の値 → 辺を経由した値

構築 $O(N)$。

### Functional Graph — `func.hpp`

各頂点の出次数が 1 のグラフ (ρ グラフ)。

```cpp
FunctionalGraph<int> fg(N);
fg.add(a, b);                       // a → b
auto [G, tree] = fg.build();        // O(N)

fg.jump(tree, v, step);             // v から step 回遷移 O(log step)
fg.in_cycle(tree, v);               // v がサイクル上か O(1)
fg.collect_cycle(r);                // サイクル頂点列挙
fg.meet_time(tree, i, j);           // i, j が合流するまでの最小ステップ
```

#### `FunctionalGraph<Monoid>` — `func_monoid.hpp`

辺にモノイド値を持つ Functional Graph。`jump` で経路上のモノイド積を返す。

### 入力ユーティリティ — `ing.hpp`

```cpp
auto g = ing(N);                     // 木入力 (N-1辺, 1-indexed → 0-indexed)
auto g = ing(N, M, false);           // 有向グラフ
auto g = ingw<ll>(N, M);             // 重み付き
```

---

## mod - モジュラー算術

### `modint<mod>` — `modint.hpp`

コンパイル時定数 mod の modint。NTT 対応。

```cpp
using mint = modint<998244353>;

mint a = 10, b = 3;
mint c = a * b;                // 乗算
mint d = a.pow(100);           // 累乗 O(log n)
mint e = a.inv();              // 逆元
mint f = ~a;                   // inv() と同じ
mint g = a.ppow(t);            // a^(t mod (mod-1))
```

付属ユーティリティ:

```cpp
invs(i);                       // i の逆元 (遅延計算・キャッシュ)
facs(i);                       // i! (遅延計算・キャッシュ)
ifacs(i);                      // (i!)^{-1}
comb(n, k);                    // C(n, k)
```

### `modint_common.hpp` — 汎用組合せ関数

任意の `mint` 型 (get_mod() を持つ型) に対する関数群。

```cpp
inv<mint>(n);                  // n の逆元 (キャッシュ付き)
fact<mint>(n);                 // n!
fact_inv<mint>(n);             // (n!)^{-1}
C<mint>(n, k);                 // C(n,k)
C<mint, true>(n, k);           // n が大きい場合
C_dense<mint>(n, k);           // Pascal の三角形 DP 版
C_negative<mint>(n, d);        // (1-x)^{-n} の x^d の係数
multinomial<mint>(n, a, b, ...); // 多項係数
```

### `mint` — `mint.hpp`

実行時 mod (グローバル変数 `mod`) の modint。API は `modint<>` と同様。
追加: `two(i)` で $2^i$ のキャッシュ。

### `modint61` — `modint61.hpp`

mod = $2^{61} - 1$ の modint。ローリングハッシュ用。

```cpp
modint61 a(x);
a + b; a * b; a.pow(n); a.inverse();
```

### `modpow(a, b, mod)` — `modpow.hpp`

スタンドアロンの冪剰余。128bit 中間計算。$O(\log b)$。

### `mod_inv(val, mod)` — `modinv.hpp`

スタンドアロンの逆元 (拡張ユークリッド)。$O(\log \text{mod})$。

### `CRT2` / `CRT3` / `CRT4` / `CRT5` — `crt3.hpp`

中国剰余定理。コンパイル時定数 moduli。

```cpp
auto x = CRT3<ll, 998244353, 1000000007, 469762049>(a0, a1, a2);
```

---

## nt - 整数論

### 素因数分解 — `factor.hpp`

Pollard's rho + Miller-Rabin。

```cpp
auto pf = factor(n);         // vector<pair<ll, int>> (素因数, 指数)
auto pf = factor_by_lpf(n, lpf);  // LPF テーブル利用版
```

| 関数                    | 計算量                |
| ----------------------- | --------------------- |
| `factor(n)`             | $O(n^{1/4})$ (期待値) |
| `factor_by_lpf(n, lpf)` | $O(\log n)$           |

### 素数判定 — `isprime.hpp`

Miller-Rabin (Montgomery 乗算)。`uint64_t` 全域で決定的。

```cpp
bool p = isprime(n);          // O(1) (定数回の素数テスト)
```

### エラトステネスの篩 — `sieve.hpp`

```cpp
Sieve siv(N);                 // O(N log log N)
siv.is_prime(x);              // O(1)
siv.build_cumulative();       // 累積和構築
siv.cntp(x);                  // π(x): x 以下の素数の個数 O(1)
siv.cntrange(l, r);           // [l,r] の素数の個数 O(1)
```

### 素数テーブル — `primetable.hpp`

```cpp
auto primes = primetable(N);  // N 以下の素数リスト O(N log log N)
```

### 最小素因数テーブル — `lpf_table.hpp`

```cpp
auto lpf = lpf_table(N);     // lpf[i] = i の最小素因数 O(N log log N)
```

### GCD / LCM / 拡張GCD — `gcd.hpp`

```cpp
ll g = gcd(a, b);             // O(log min(a,b))
ll l = lcm(a, b);
auto [x, y] = extgcd(a, b);  // ax + by = gcd(a,b)
```

### オイラー関数 — `euler_phi.hpp`

```cpp
ll phi = euler_phi(n);                // O(√n)
auto phi_table = euler_phi_table<ll>(n);  // [0..n] の φ O(N log log N)
```

### 約数列挙 — `divisors.hpp`

```cpp
auto divs = divisors(n);             // O(√n), ソートなし
auto divs = divisors_by_pf(pf);     // 素因数分解から O(d(n))
auto divs = divisors_by_lpf(n, lpf); // LPF テーブルから
```

### ゼータ・メビウス変換 — `zeta.hpp`

添字 GCD/LCM 畳み込み用の変換。$O(N \log \log N)$。

```cpp
divisor_zeta(A);              // A[n] = Σ_{d|n} A[d]
divisor_mobius(A);            // 逆変換
multiplier_zeta(A);           // A[n] = Σ_{n|m} A[m]
multiplier_mobius(A);         // 逆変換
```

### その他

| ファイル         | 関数                                 | 説明                           | 計算量                   |
| ---------------- | ------------------------------------ | ------------------------------ | ------------------------ | --- | -------------- |
| `digit_sum.hpp`  | `digit_sum(x)`                       | 桁和                           | $O(\log x)$              |
| `kthroot.hpp`    | `kth_root(a, k)`                     | $\lfloor a^{1/k} \rfloor$      | $O(\log k \cdot \log a)$ |
| `convbinary.hpp` | `conv(s, from, to)`                  | 基数変換 (2〜36進)             | $O(                      | s   | \cdot \log s)$ |
| `round.hpp`      | `round_n(s, k)` / `round_down(s, k)` | 文字列ベース四捨五入・切り捨て | $O(                      | s   | )$             |

---

## fps - 形式的べき級数

### `fps` — `fps.hpp`

modint 上の形式的べき級数。NTT による高速乗算。

```cpp
fps f = {1, 2, 3};           // 1 + 2x + 3x²
fps g = f * g;                // O(n log n)
fps h = f.inv(deg);           // 逆元 O(n log n)
fps l = log(f, deg);          // log O(n log n)
fps e = exp(f, deg);          // exp O(n log n)
fps p = pow(f, k, deg);       // f^k O(n log n)
fps s = sqrt_base(f, deg);    // sqrt O(n log n)
fps d = f.dif();              // 微分 O(n)
fps i = f.integ();            // 積分 O(n)
f(x);                         // x に代入して評価 O(n)
f.rev();                      // 係数反転
f.low(n);                     // 先頭 n 項
f.taylorShift(c);             // f(x+c)
f.bostanMori(n, p);           // [x^n] p(x)/f(x) O(K log K log n)
```

### `fps<T>` — `fpsd.hpp`

double 等の非modint型でも使える FPS。

```cpp
fps<double> f = {1.0, 2.0};
f.inv(deg);                   // O(n log n) or O(n²)
f.eval(a);                    // Horner's method O(n)
f.multiply(d, c);             // (1 + c·z^d) を掛ける O(n)
f.divide(d, c);               // (1 + c·z^d) で割る O(n)
```

### NTT — `ntt.hpp`

```cpp
ntt(a, false);                // 順変換 O(n log n)
ntt(a, true);                 // 逆変換 O(n log n)
```

### 畳み込み — `convolution.hpp`

```cpp
auto c = convolution(a, b);           // modint O(n log n), 自動で NTT/Karatsuba 選択
auto c = convolution_ntt(a, b);       // NTT 直接
auto c = convolution_garner(a, b);    // 任意mod (3つの NTT で CRT)
auto c = convolution(va, vb);         // long long 畳み込み
```

| 関数                    | 計算量         | 備考                  |
| ----------------------- | -------------- | --------------------- |
| `convolution_ntt`       | $O(n \log n)$  | NTT-friendly mod のみ |
| `convolution_garner`    | $O(n \log n)$  | 任意 mod              |
| `convolution_karatsuba` | $O(n^{1.585})$ | NTT 不要              |
| `convolution_naive`     | $O(nm)$        | 小サイズ用            |

### 線形漸化式の第 N 項 — `kthseq.hpp`

Bostan-Mori アルゴリズム。

```cpp
mint ans = kthseq_sequences(K, N, init, coeff);  // O(K log K log N)
```

---

## string - 文字列

### Rolling Hash — `rollinghash.hpp`

2つの mod ($999999937$, $1000000007$) でハッシュ。

```cpp
RollingHash rh(s);
rh.get(l, r);                // [l,r) のハッシュ O(1)
rh.get(l, r, 1);             // 第2 mod のハッシュ
rh.getLCP(a, b);              // S[a:] と S[b:] の LCP O(log n)
rh.getLCP(other, a, b);       // 異なる文字列間の LCP
```

構築 $O(n)$、部分列ハッシュ $O(1)$、LCP $O(\log n)$。

### Rolling Hash + セグ木 — `rolihaseg.hpp`

1点更新可能なローリングハッシュ。

```cpp
RollingHash rh(s);
rh.update(pos, c);            // S[pos] = c  O(log n)
rh.get(l, r, id);             // ハッシュ O(log n)
rh.palindrome(L, R);          // 回文判定 O(log n)
rh.getLCP(a, b);               // LCP O(log² n)
```

### Manacher — `manacher.hpp`

全極大回文列挙。$O(n)$。

```cpp
auto pals = manacher(s);      // vector<pair<int,int>> の [L, R)
```

### LCS — `lcs.hpp`

```cpp
int len = LCS(s, t);          // 最長共通部分列の長さ O(|s||t|)
string sub = LCS_string(s, t); // 復元
```

### 編集距離 — `editdis.hpp`

```cpp
int d = edit_distance(s, t);  // Levenshtein 距離 O(|s||t|)
```

### Trie / Aho-Corasick — `trie.hpp`

```cpp
Trie<26> trie;                // アルファベットサイズ 26
trie.add(pattern, 'a');       // パターン追加 O(|pattern|)
trie.calc_suffix_link();      // Suffix Link 構築 O(全ノード数)
trie.calc_count();            // パターン出現カウント
```

### Run-Length Encoding — `rle.hpp`

```cpp
auto encoded = rle(s);        // vector<pair<char, ll>> O(n)
```

### グリッド操作 — `grid.hpp`, `gridset.hpp`

2Dグリッドの回転・配置・正規化操作。

---

## seq - 数列

### LIS — `lis.hpp`

```cpp
ll len = LIS(a);                    // 狭義単調増加 O(n log n)
ll len = LIS(a, true);              // 広義単調増加
auto seq = LIS_path(a);             // 復元
ll len = LIS2D(pairs);              // 2D LIS
```

### 3D LIS — `lis3d.hpp`

```cpp
ll len = LIS3D(tuples);             // O(n² log n)
```

### 転倒数 — `inversion.hpp`

```cpp
ll inv = tentou(a);                 // O(n log n), BIT 利用
auto c = compress(a);               // 座標圧縮
```

### MEX — `mex.hpp`

```cpp
int m = mex(A);                     // A に含まれない最小非負整数 O(n)
```

### 区間和集合 — `interval_union.hpp`

```cpp
auto merged = interval_union(intervals);  // O(n log n)
// intervals: vector<pair<T,T>> (半開区間 [l,r))
```

### 最大長方形 — `rectangle.hpp`

```cpp
ll area = largest_rectangle(heights);     // O(n), ヒストグラム中の最大長方形
```

### 区間分解 — `decompose.hpp`

```cpp
auto blocks = decompose(l, r);     // [l,r) を 2冪アラインされたブロックに分解
```

### 分数比較 — `frac.hpp`

```cpp
frac a{p1, q1}, b{p2, q2};
if (a < b) { ... }                 // オーバーフローなし比較
```

---

## geo - 幾何

### 2D ベクトル / 点 — `geom.hpp`

```cpp
V<double> p(x, y), q(x, y);
p + q; p - q; p * scalar;          // ベクトル演算
p.dot(q);                          // 内積
p.cross(q);                        // 外積
p.norm();                          // ノルム
dist(p, q);                        // 距離
p.rotate90();                      // 90° 回転
rotate(p, angle);                  // 任意角回転
```

### 円 — `circle.hpp`

```cpp
Circle<double> c1(center, r);
c1.xp(c2);                         // 2円の交点
c1.in(point);                      // 点が円内か
c1.touch(c2);                      // 2円が接するか
c1.distCC(c2);                     // 2円の距離
```

### マンハッタン MST — `manhattanmst.hpp`

```cpp
auto mst = manhattan_mst(points);   // O(n log n)
// Graph<T, 0> を返す
```

---

## linalg - 線形代数

### `Matrix<T>` — `matrix.hpp`

```cpp
Matrix<mint> A(N, M);               // N×M 行列
A[i][j] = val;                      // 要素アクセス
auto C = A * B;                     // 行列積 O(NMP)
auto An = A.pow(n);                 // 行列累乗 O(N³ log n)
auto det = A.det();                 // 行列式 O(N³)
int rank = A.elimination();         // ガウス消去 O(NM²)
auto I = Matrix<mint>::eye(N);      // 単位行列
```

### `transpose` — `transpose.hpp`

```cpp
auto At = transpose(A);             // O(HW)
```

---

## knapsack - ナップサック

`knapsack.hpp` に4種の解法を収録。

| 関数                     | 想定制約                    | 計算量               | アルゴリズム                  |
| ------------------------ | --------------------------- | -------------------- | ----------------------------- |
| `knapsack(w, v, W)`      | $n \le 100$, $W \le 10^5$   | $O(nW)$              | 0-1 ナップサック (重さ基準DP) |
| `knapsack1(w, v, W)`     | $n \le 200$, $v_i \le 1000$ | $O(n \sum v)$        | 0-1 ナップサック (価値基準DP) |
| `knapsack2(w, v, W)`     | $n \le 40$                  | $O(2^{n/2} \cdot n)$ | 半分全列挙                    |
| `knapsack_free(w, v, W)` | 個数制限なし                | $O(nW)$              | 個数無制限ナップサック        |

```cpp
ll ans = knapsack(weights, values, W);
```

注意: 配列は 1-indexed (index 0 は未使用)。

---

## bigint - 多倍長整数

### `BigInteger` — `base.hpp`

基数 $10^9$ 表現の任意精度整数。NTT による高速乗算対応。

```cpp
BigInteger a("123456789012345678901234567890");
BigInteger b(12345LL);
auto c = a + b;
auto d = a * b;                    // O(n log n) (NTT) or O(n²) (naive)
a.to_string();                     // 10進文字列
a.to_binary_string();              // 2進文字列
a.divmod(p);                       // p で割った (商, 余り)
a.pow(n);                          // a^n
a.log10();                         // 桁数
a.digit_sum();                     // 桁和
a.base_p_representation(p);        // p 進表現
```

| 演算       | 計算量                                 |
| ---------- | -------------------------------------- |
| 加算・減算 | $O(n)$                                 |
| 乗算       | $O(n \log n)$ (NTT) / $O(n^2)$ (naive) |
| 比較       | $O(n)$                                 |

---

## datetime - 日時

### `DateTime` — `datetime.hpp`

```cpp
DateTime dt(2024, 1, 15);
int days = dt.to_int();             // 年月日 → 通日 (year 1 起点)
DateTime dt2 = DateTime::from_int(days);  // 通日 → 年月日
int dow = dt.weekday();             // 曜日 [0,7), 0=日曜
++dt;                               // 翌日
dt.to_string("-");                  // "2024-01-15"
DateTime::is_leap_year(2024);       // 閏年判定
DateTime::is_valid_date(y, m, d);   // 日付妥当性
```

全操作 $O(1)$。

---

## random - 乱数

### `random.hpp`

XORShift ベースの乱数生成。ナノ秒シードで初期化。

```cpp
ull x = RNG_64();              // 64bit 乱数
ull y = RNG(lim);              // [0, lim) の乱数
ll z = RNG(l, r);              // [l, r) の乱数
```

全操作 $O(1)$。

---

## segtree - セグ木使用例

`segtree/` ディレクトリにセグメント木の問題別使用例を収録。

| ファイル           | 内容                   |
| ------------------ | ---------------------- |
| `segtree.cpp`      | 基本セグ木の使用例     |
| `lazy_segtree.cpp` | 遅延セグ木の使用例     |
| `rbst.cpp`         | RBST の使用例          |
| `affin.cpp`        | アフィン変換セグ木の例 |
| `aoj/rmq.cpp`      | Range Minimum Query    |
| `aoj/rsq.cpp`      | Range Sum Query        |
| `aoj/raq.cpp`      | Range Add Query        |
| `aoj/ruq.cpp`      | Range Update Query     |
| `aoj/rmq&raq.cpp`  | RMQ + RAQ              |
| `aoj/rmq&ruq.cpp`  | RMQ + RUQ              |
| `aoj/rsq&raq.cpp`  | RSQ + RAQ              |
| `aoj/rsq&ruq.cpp`  | RSQ + RUQ              |
| `aoj/rmax&rsq.cpp` | Range Max + RSQ        |

---

## ac-library - AtCoder Library

AtCoder Library (ACL) のミラーコピー。`acl/` 以下に全モジュールを収録。

収録モジュール: `convolution`, `dsu`, `fenwicktree`, `lazysegtree`, `math`, `maxflow`, `mincostflow`, `modint`, `scc`, `segtree`, `string`, `twosat`

```cpp
#include "ac-library/acl/modint.hpp"
#include "ac-library/acl/segtree.hpp"
// ...
```

公式ドキュメント: `ac-library/document_ja/`
