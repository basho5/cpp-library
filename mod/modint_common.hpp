// has_mod_impl/check: T 型に get_mod() メンバが存在するかチェックする仕組み。
struct has_mod_impl {
  template <class T>
  static auto check(T &&x) -> decltype(x.get_mod(), std::true_type{});
  template <class T>
  static auto check(...) -> std::false_type;
};

template <class T>
class has_mod : public decltype(has_mod_impl::check<T>(std::declval<T>())) {};

// --- 逆元の計算 ---
// inv<mint>(n) は、モジュロ mint::get_mod() の下で n の逆元を返す
template <typename mint>
mint inv(int n) {
  static const int mod = mint::get_mod();
  static vector<mint> dat = {0, 1};
  assert(0 <= n);
  if (n >= mod) n %= mod;
  while (sz(dat) <= n) {
    int k = sz(dat);
    int q = (mod + k - 1) / k;
    dat.eb(dat[k * q - mod] * mint::raw(q));
  }
  return dat[n];
}

// --- 階乗の計算 ---
// fact<mint>(n) は、n! をモジュロ mint::get_mod() で計算する。
template <typename mint>
mint fact(int n) {
  static const int mod = mint::get_mod();
  assert(0 <= n && n < mod);
  static vector<mint> dat = {1, 1};
  while (sz(dat) <= n) dat.eb(dat[sz(dat) - 1] * mint::raw(sz(dat)));
  return dat[n];
}

// fact_inv<mint>(n) は、n! の逆元（n!^(-1)）を計算する。
template <typename mint>
mint fact_inv(int n) {
  static vector<mint> dat = {1, 1};
  if (n < 0) return mint(0);
  while (sz(dat) <= n) dat.eb(dat[sz(dat) - 1] * inv<mint>(sz(dat)));
  return dat[n];
}

// 複数の引数に対して、それぞれの fact_inv を掛け合わせたものを返す。
// 例: fact_invs(x, y, z) = fact_inv(x) * fact_inv(y) * fact_inv(z)
template <class mint, class... Ts>
mint fact_invs(Ts... xs) {
  return (mint(1) * ... * fact_inv<mint>(xs));
}

// multinomial<mint>(n, k, n-k) を計算する。
// これは n! / (k! (n-k)!) に対応する多項係数を返す。
template <typename mint, class Head, class... Tail>
mint multinomial(Head &&head, Tail &&... tail) {
  return fact<mint>(head) * fact_invs<mint>(std::forward<Tail>(tail)...);
}

// --- 密なDPテーブルによる組み合わせ計算 ---
// C_dense<mint>(n, k) は、n C k を DP を用いて計算する。
template <typename mint>
mint C_dense(int n, int k) {
  assert(n >= 0);
  if (k < 0 || n < k) return 0;
  static vv<mint> C;
  static int H = 0, W = 0;
  auto calc = [&](int i, int j) -> mint {
    if (i == 0) return (j == 0 ? mint(1) : mint(0));
    return C[i - 1][j] + (j ? C[i - 1][j - 1] : 0);
  };
  if (W <= k) {
    rep(i, H) {
      C[i].resize(k + 1);
      rep(j, W, k + 1) { C[i][j] = calc(i, j); }
    }
    W = k + 1;
  }
  if (H <= n) {
    C.resize(n + 1);
    rep(i, H, n + 1) {
      C[i].resize(W);
      rep(j, W) { C[i][j] = calc(i, j); }
    }
    H = n + 1;
  }
  return C[n][k];
}

// C<mint, large, dense>(n, k) は、n C k を計算する。
template <typename mint, bool large = false, bool dense = false>
mint C(ll n, ll k) {
  assert(n >= 0);
  if (k < 0 || n < k) return 0;
  if constexpr (dense) return C_dense<mint>(n, k);
  if constexpr (!large) return multinomial<mint>(n, k, n - k);
  k = min(k, n - k);
  mint x(1);
  rep(i, k) x *= mint(n - i);
  return x * fact_inv<mint>(k);
}

// C_inv は、n C k の逆元を計算する。
template <typename mint, bool large = false>
mint C_inv(ll n, ll k) {
  assert(n >= 0);
  assert(0 <= k && k <= n);
  if (!large) return fact_inv<mint>(n) * fact<mint>(k) * fact<mint>(n - k);
  return mint(1) / C<mint, 1>(n, k);
}

// --- 負の指数を持つ二項展開の係数 ---
// C_negative<mint>(n, d) は、(1-x)^{-n} の x^d の係数を返す。
// [x^d](1-x)^{-n}
template <typename mint, bool large = false, bool dense = false>
mint C_negative(ll n, ll d) {
  assert(n >= 0);
  if (d < 0) return mint(0);
  if (n == 0) { return (d == 0 ? mint(1) : mint(0)); }
  return C<mint, large, dense>(n + d - 1, d);
}
