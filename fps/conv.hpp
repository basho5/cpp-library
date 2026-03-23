#line 2 "mod/modint_common.hpp"
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

#line 2 "mod/modint.hpp"
const int mod = 998244353; 
// const int mod = 1000000007;
template <int mod>
struct modint {
  static constexpr uint umod = uint(mod);
  static_assert(umod < uint(1) << 31);
  uint val;

  static modint raw(uint v) {
    modint x;
    x.val = v;
    return x;
  }
  constexpr modint() : val(0) {}
  constexpr modint(uint x) : val(x % umod) {}
  constexpr modint(ull x) : val(x % umod) {}
  constexpr modint(u128 x) : val(x % umod) {}
  constexpr modint(int x) : val((x %= mod) < 0 ? x + mod : x){};
  constexpr modint(ll x) : val((x %= mod) < 0 ? x + mod : x){};
  constexpr modint(i128 x) : val((x %= mod) < 0 ? x + mod : x){};
  bool operator<(const modint &other) const { return val < other.val; }
  modint &operator+=(const modint &p) {
    if ((val += p.val) >= umod) val -= umod;
    return *this;
  }
  modint &operator-=(const modint &p) {
    if ((val += umod - p.val) >= umod) val -= umod;
    return *this;
  }
  modint &operator*=(const modint &p) {
    val = ull(val) * p.val % umod;
    return *this;
  }
  modint &operator/=(const modint &p) {
    *this *= p.inv();
    return *this;
  }
  modint operator-() const { return modint::raw(val ? mod - val : uint(0)); }
  modint operator+(const modint &p) const { return modint(*this) += p; }
  modint operator-(const modint &p) const { return modint(*this) -= p; }
  modint operator*(const modint &p) const { return modint(*this) *= p; }
  modint operator/(const modint &p) const { return modint(*this) /= p; }
  bool operator==(const modint &p) const { return val == p.val; }
  bool operator!=(const modint &p) const { return val != p.val; }
  modint operator~() const { return this->pow(mod - 2); }
  modint inv() const {
    int a = val, b = mod, u = 1, v = 0, t;
    while (b > 0) {
      t = a / b;
      swap(a -= t * b, b), swap(u -= t * v, v);
    }
    return modint(u);
  }
  modint pow(ll n) const {
    if (n < 0) return inv().pow(-n);
    assert(n >= 0);
    modint ret(1), mul(val);
    while (n > 0) {
      if (n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }

  constexpr modint ppow(ll t)const {int p=mod-1; return pow((t%p+p)%p);}

  static constexpr int get_mod() { return mod; }
  // (n, r), r は 1 の 2^n 乗根
  static constexpr pair<int, int> ntt_info() {
    if (mod == 120586241) return {20, 74066978};
    if (mod == 167772161) return {25, 17};
    if (mod == 469762049) return {26, 30};
    if (mod == 754974721) return {24, 362};
    if (mod == 880803841) return {23, 211};
    if (mod == 943718401) return {22, 663003469};
    if (mod == 998244353) return {23, 31};
    if (mod == 1004535809) return {21, 582313106};
    if (mod == 1012924417) return {21, 368093570};
    return {-1, -1};
  }
  static constexpr bool can_ntt() { return ntt_info().fi != -1; }
};
using mint = modint<mod> ; 
using vm = vector<mint>;
using vvm = vector<vm>;
istream& operator>>(istream &is, modint<mod> &a) { ll v; is >> v; a = modint<mod>(v); return is; }
ostream& operator<<(ostream &os, const modint<mod> &a) { return os << a.val; }

struct modinv {
  int n; vector<mint> d;
  modinv(): n(2), d({mint(0), mint(1)}) {}
  mint operator()(int i) { while(n <= i) d.push_back(-d[mod % n] * mint(mod / n)), ++n; return d[i]; }
  mint operator[](int i) const { return d[i]; }
} invs;
struct modfact {
  int n; vector<mint> d;
  modfact(): n(2), d({mint(1), mint(1)}) {}
  mint operator()(int i) { while(n <= i) d.push_back(d.back() * mint(n)), ++n; return d[i]; }
  mint operator[](int i) const { return d[i]; }
} facs;
struct modfactinv {
  int n; vector<mint> d;
  modfactinv(): n(2), d({mint(1), mint(1)}) {}
  mint operator()(int i) { while(n <= i) d.push_back(d.back() * invs(n)), ++n; return d[i]; }
  mint operator[](int i) const { return d[i]; }
} ifacs;
mint comb(int a, int b) { return (a < b || b < 0) ? mint(0) : facs(a) * ifacs(b) * ifacs(a-b); }

#line 2 "mod/mod_inv.hpp"
ll mod_inv(ll val, ll mod) {
  if (mod == 0) return 0;
  mod = abs(mod);
  val %= mod;
  if (val < 0) val += mod;
  ll a = val, b = mod, u = 1, v = 0, t;
  while (b > 0) {
    t = a / b;
    swap(a -= t * b, b), swap(u -= t * v, v);
  }
  if (u < 0) u += mod;
  return u;
}

#line 2 "mod/crt3.hpp"
constexpr uint mod_pow_constexpr(ull a, ull n, uint mod) {
  a %= mod;
  ull res = 1;
  rep(32) {
    if (n & 1) res = res * a % mod;
    a = a * a % mod, n /= 2;
  }
  return res;
}

template <typename T, uint p0, uint p1>
T CRT2(ull a0, ull a1) {
  static_assert(p0 < p1);
  static constexpr ull x0_1 = mod_pow_constexpr(p0, p1 - 2, p1);
  ull c = (a1 - a0 + p1) * x0_1 % p1;
  return a0 + c * p0;
}

template <typename T, uint p0, uint p1, uint p2>
T CRT3(ull a0, ull a1, ull a2) {
  static_assert(p0 < p1 && p1 < p2);
  static constexpr ull x1 = mod_pow_constexpr(p0, p1 - 2, p1);
  static constexpr ull x2 = mod_pow_constexpr(ull(p0) * p1 % p2, p2 - 2, p2);
  static constexpr ull p01 = ull(p0) * p1;
  ull c = (a1 - a0 + p1) * x1 % p1;
  ull ans_1 = a0 + c * p0;
  c = (a2 - ans_1 % p2 + p2) * x2 % p2;
  return T(ans_1) + T(c) * T(p01);
}

template <typename T, uint p0, uint p1, uint p2, uint p3>
T CRT4(ull a0, ull a1, ull a2, ull a3) {
  static_assert(p0 < p1 && p1 < p2 && p2 < p3);
  static constexpr ull x1 = mod_pow_constexpr(p0, p1 - 2, p1);
  static constexpr ull x2 = mod_pow_constexpr(ull(p0) * p1 % p2, p2 - 2, p2);
  static constexpr ull x3 = mod_pow_constexpr(ull(p0) * p1 % p3 * p2 % p3, p3 - 2, p3);
  static constexpr ull p01 = ull(p0) * p1;
  ull c = (a1 - a0 + p1) * x1 % p1;
  ull ans_1 = a0 + c * p0;
  c = (a2 - ans_1 % p2 + p2) * x2 % p2;
  u128 ans_2 = ans_1 + c * static_cast<u128>(p01);
  c = (a3 - ans_2 % p3 + p3) * x3 % p3;
  return T(ans_2) + T(c) * T(p01) * T(p2);
}

template <typename T, uint p0, uint p1, uint p2, uint p3, uint p4>
T CRT5(ull a0, ull a1, ull a2, ull a3, ull a4) {
  static_assert(p0 < p1 && p1 < p2 && p2 < p3 && p3 < p4);
  static constexpr ull x1 = mod_pow_constexpr(p0, p1 - 2, p1);
  static constexpr ull x2 = mod_pow_constexpr(ull(p0) * p1 % p2, p2 - 2, p2);
  static constexpr ull x3 = mod_pow_constexpr(ull(p0) * p1 % p3 * p2 % p3, p3 - 2, p3);
  static constexpr ull x4 = mod_pow_constexpr(ull(p0) * p1 % p4 * p2 % p4 * p3 % p4, p4 - 2, p4);
  static constexpr ull p01 = ull(p0) * p1;
  static constexpr ull p23 = ull(p2) * p3;
  ull c = (a1 - a0 + p1) * x1 % p1;
  ull ans_1 = a0 + c * p0;
  c = (a2 - ans_1 % p2 + p2) * x2 % p2;
  u128 ans_2 = ans_1 + c * static_cast<u128>(p01);
  c = static_cast<ull>(a3 - ans_2 % p3 + p3) * x3 % p3;
  u128 ans_3 = ans_2 + static_cast<u128>(c * p2) * p01;
  c = static_cast<ull>(a4 - ans_3 % p4 + p4) * x4 % p4;
  return T(ans_3) + T(c) * T(p01) * T(p23);
}

#line 2 "fps/convolution_naive.hpp"
template <class T, typename enable_if<!has_mod<T>::value>::type* = nullptr>
vc<T> convolution_naive(const vc<T>& a, const vc<T>& b) {
  int n = int(a.size()), m = int(b.size());
  if (n > m) return convolution_naive<T>(b, a);
  if (n == 0) return {};
  vector<T> ans(n + m - 1);
  rep(i, n)rep(j, m) ans[i + j] += a[i] * b[j];
  return ans;
}
template <class T, typename enable_if<has_mod<T>::value>::type* = nullptr>
vc<T> convolution_naive(const vc<T>& a, const vc<T>& b) {
  int n = int(a.size()), m = int(b.size());
  if (n > m) return convolution_naive<T>(b, a);
  if (n == 0) return {};
  vc<T> ans(n + m - 1);
  if (n <= 16 && (T::get_mod() < (1 << 30))) {
    for (int k = 0; k < n + m - 1; ++k) {
      int s = max(0, k - m + 1);
      int t = min(n, k + 1);
      ull sm = 0;
      for (int i = s; i < t; ++i) { sm += ull(a[i].val) * (b[k - i].val); }
      ans[k] = sm;
    }
  } else {
    for (int k = 0; k < n + m - 1; ++k) {
      int s = max(0, k - m + 1);
      int t = min(n, k + 1);
      u128 sm = 0;
      for (int i = s; i < t; ++i) { sm += ull(a[i].val) * (b[k - i].val); }
      ans[k] = T::raw(sm % T::get_mod());
    }
  }
  return ans;
}

#line 2 "fps/convolution_karatsuba.hpp"
// 任意の環でできる
template <typename T>
vc<T> convolution_karatsuba(const vc<T>& f, const vc<T>& g) {
  const int thresh = 30;
  if (min(sz(f), sz(g)) <= thresh) return convolution_naive(f, g);
  int n = max(sz(f), sz(g));
  int m = ceil(n, 2);
  vc<T> f1, f2, g1, g2;
  if (sz(f) < m) f1 = f;
  if (sz(f) >= m) f1 = {f.begin(), f.begin() + m};
  if (sz(f) >= m) f2 = {f.begin() + m, f.end()};
  if (sz(g) < m) g1 = g;
  if (sz(g) >= m) g1 = {g.begin(), g.begin() + m};
  if (sz(g) >= m) g2 = {g.begin() + m, g.end()};
  vc<T> a = convolution_karatsuba(f1, g1);
  vc<T> b = convolution_karatsuba(f2, g2);
  rep(i, sz(f2)) f1[i] += f2[i];
  rep(i, sz(g2)) g1[i] += g2[i];
  vc<T> c = convolution_karatsuba(f1, g1);
  vc<T> F(sz(f) + sz(g) - 1);
  assert(2 * m + sz(b) <= sz(F));
  rep(i, sz(a)) F[i] += a[i], c[i] -= a[i];
  rep(i, sz(b)) F[2 * m + i] += b[i], c[i] -= b[i];
  if (c.back() == T(0)) c.pop_back();
  rep(i, sz(c)) if (c[i] != T(0)) F[m + i] += c[i];
  return F;
}

#line 2 "fps/ntt.hpp"
template <class mint>
void ntt(vector<mint>& a, bool inverse) {
  assert(mint::can_ntt());
  const int rank2 = mint::ntt_info().fi;
  const int mod = mint::get_mod();
  static array<mint, 30> root, iroot;
  static array<mint, 30> rate2, irate2;
  static array<mint, 30> rate3, irate3;

  assert(rank2 != -1 && sz(a) <= (1 << max(0, rank2)));

  static bool prepared = 0;
  if (!prepared) {
    prepared = 1;
    root[rank2] = mint::ntt_info().se;
    iroot[rank2] = mint(1) / root[rank2];
    drep(i, rank2) {
      root[i] = root[i + 1] * root[i + 1];
      iroot[i] = iroot[i + 1] * iroot[i + 1];
    }
    mint prod = 1, iprod = 1;
    for (int i = 0; i <= rank2 - 2; i++) {
      rate2[i] = root[i + 2] * prod;
      irate2[i] = iroot[i + 2] * iprod;
      prod *= iroot[i + 2];
      iprod *= root[i + 2];
    }
    prod = 1, iprod = 1;
    for (int i = 0; i <= rank2 - 3; i++) {
      rate3[i] = root[i + 3] * prod;
      irate3[i] = iroot[i + 3] * iprod;
      prod *= iroot[i + 3];
      iprod *= root[i + 3];
    }
  }

  int n = int(a.size());
  int h = topbit(n);
  assert(n == 1 << h);
  if (!inverse) {
    int len = 0;
    while (len < h) {
      if (h - len == 1) {
        int p = 1 << (h - len - 1);
        mint rot = 1;
        rep(s, 1 << len) {
          int offset = s << (h - len);
          rep(i, p) {
            auto l = a[i + offset];
            auto r = a[i + offset + p] * rot;
            a[i + offset] = l + r;
            a[i + offset + p] = l - r;
          }
          rot *= rate2[topbit(~s & -~s)];
        }
        len++;
      } else {
        int p = 1 << (h - len - 2);
        mint rot = 1, imag = root[2];
        for (int s = 0; s < (1 << len); s++) {
          mint rot2 = rot * rot;
          mint rot3 = rot2 * rot;
          int offset = s << (h - len);
          for (int i = 0; i < p; i++) {
            ull mod2 = ull(mod) * mod;
            ull a0 = a[i + offset].val;
            ull a1 = ull(a[i + offset + p].val) * rot.val;
            ull a2 = ull(a[i + offset + 2 * p].val) * rot2.val;
            ull a3 = ull(a[i + offset + 3 * p].val) * rot3.val;
            ull a1na3imag = (a1 + mod2 - a3) % mod * imag.val;
            ull na2 = mod2 - a2;
            a[i + offset] = a0 + a2 + a1 + a3;
            a[i + offset + 1 * p] = a0 + a2 + (2 * mod2 - (a1 + a3));
            a[i + offset + 2 * p] = a0 + na2 + a1na3imag;
            a[i + offset + 3 * p] = a0 + na2 + (mod2 - a1na3imag);
          }
          rot *= rate3[topbit(~s & -~s)];
        }
        len += 2;
      }
    }
  } else {
    mint coef = mint(1) / mint(sz(a));
    rep(i, sz(a)) a[i] *= coef;
    int len = h;
    while (len) {
      if (len == 1) {
        int p = 1 << (h - len);
        mint irot = 1;
        rep(s, 1 << (len - 1)) {
          int offset = s << (h - len + 1);
          rep(i, p) {
            ull l = a[i + offset].val;
            ull r = a[i + offset + p].val;
            a[i + offset] = l + r;
            a[i + offset + p] = (mod + l - r) * irot.val;
          }
          irot *= irate2[topbit(~s & -~s)];
        }
        len--;
      } else {
        int p = 1 << (h - len);
        mint irot = 1, iimag = iroot[2];
        rep(s, (1 << (len - 2))) {
          mint irot2 = irot * irot;
          mint irot3 = irot2 * irot;
          int offset = s << (h - len + 2);
          for (int i = 0; i < p; i++) {
            ull a0 = a[i + offset + 0 * p].val;
            ull a1 = a[i + offset + 1 * p].val;
            ull a2 = a[i + offset + 2 * p].val;
            ull a3 = a[i + offset + 3 * p].val;
            ull x = (mod + a2 - a3) * iimag.val % mod;
            a[i + offset] = a0 + a1 + a2 + a3;
            a[i + offset + 1 * p] = (a0 + mod - a1 + x) * irot.val;
            a[i + offset + 2 * p] = (a0 + a1 + 2 * mod - a2 - a3) * irot2.val;
            a[i + offset + 3 * p] = (a0 + 2 * mod - a1 - x) * irot3.val;
          }
          irot *= irate3[topbit(~s & -~s)];
        }
        len -= 2;
      }
    }
  }
}

#line 2 "fps/convolution.hpp"
template <class mint>
vector<mint> convolution_ntt(vector<mint> a, vector<mint> b) {
  if (a.empty() || b.empty()) return {};
  int n = int(a.size()), m = int(b.size());
  int sz = 1;
  while (sz < n + m - 1) sz *= 2;

  // sz = 2^k のときの高速化。分割統治的なやつで損しまくるので。

  if ((n + m - 3) <= sz / 2) {
    auto a_last = a.back(), b_last = b.back();
    a.pop_back(), b.pop_back();
    auto c = convolution(a, b);
    c.resize(n + m - 1);
    c[n + m - 2] = a_last * b_last;
    rep(i, sz(a)) c[i + sz(b)] += a[i] * b_last;
    rep(i, sz(b)) c[i + sz(a)] += b[i] * a_last;
    return c;
  }

  a.resize(sz), b.resize(sz);
  bool same = a == b;
  ntt(a, 0);
  if (same) {
    b = a;
  } else {
    ntt(b, 0);
  }
  rep(i, sz) a[i] *= b[i];
  ntt(a, 1);
  a.resize(n + m - 1);
  return a;
}

template <typename mint>
vector<mint> convolution_garner(const vector<mint>& a, const vector<mint>& b) {
  int n = sz(a), m = sz(b);
  if (!n || !m) return {};
  static constexpr int p0 = 167772161;
  static constexpr int p1 = 469762049;
  static constexpr int p2 = 754974721;
  using mint0 = modint<p0>;
  using mint1 = modint<p1>;
  using mint2 = modint<p2>;
  vc<mint0> a0(n), b0(m);
  vc<mint1> a1(n), b1(m);
  vc<mint2> a2(n), b2(m);
  rep(i, n) a0[i] = a[i].val, a1[i] = a[i].val, a2[i] = a[i].val;
  rep(i, m) b0[i] = b[i].val, b1[i] = b[i].val, b2[i] = b[i].val;
  auto c0 = convolution_ntt<mint0>(a0, b0);
  auto c1 = convolution_ntt<mint1>(a1, b1);
  auto c2 = convolution_ntt<mint2>(a2, b2);
  vc<mint> c(sz(c0));
  rep(i, n + m - 1) { c[i] = CRT3<mint, p0, p1, p2>(c0[i].val, c1[i].val, c2[i].val); }
  return c;
}

vector<ll> convolution(vector<ll> a, vector<ll> b) {
  int n = sz(a), m = sz(b);
  if (!n || !m) return {};
  if (min(n, m) <= 2500) return convolution_naive(a, b);

  ll mi_a = min(a), mi_b = min(b);
  for (auto& x: a) x -= mi_a;
  for (auto& x: b) x -= mi_b;
  assert(max(a) * max(b) <= 1e18);

  auto Ac = cumsum<ll>(a), Bc = cumsum<ll>(b);
  vl res(n + m - 1);
  for (int k = 0; k < n + m - 1; ++k) {
    int s = max(0, k - m + 1);
    int t = min(n, k + 1);
    res[k] += (t - s) * mi_a * mi_b;
    res[k] += mi_a * (Bc[k - s + 1] - Bc[k - t + 1]);
    res[k] += mi_b * (Ac[t] - Ac[s]);
  }

  static constexpr uint MOD1 = 1004535809;
  static constexpr uint MOD2 = 1012924417;
  using mint1 = modint<MOD1>;
  using mint2 = modint<MOD2>;

  vc<mint1> a1(n), b1(m);
  vc<mint2> a2(n), b2(m);
  rep(i, n) a1[i] = a[i], a2[i] = a[i];
  rep(i, m) b1[i] = b[i], b2[i] = b[i];

  auto c1 = convolution_ntt<mint1>(a1, b1);
  auto c2 = convolution_ntt<mint2>(a2, b2);

  rep(i, n + m - 1) { res[i] += CRT2<ull, MOD1, MOD2>(c1[i].val, c2[i].val); }
  return res;
}

template <typename mint>
vc<mint> convolution(const vc<mint>& a, const vc<mint>& b) {
  int n = sz(a), m = sz(b);
  if (!n || !m) return {};
  if (mint::can_ntt()) {
    if (min(n, m) <= 50) return convolution_karatsuba<mint>(a, b);
    return convolution_ntt(a, b);
  }
  if (min(n, m) <= 200) return convolution_karatsuba<mint>(a, b);
  return convolution_garner(a, b);
}
