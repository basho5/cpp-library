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
