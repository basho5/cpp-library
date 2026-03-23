#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
#define rep0(n) for(int _=0; _ < (n); ++_)
#define rep1(i,n) for(int i = 0; i < (n); ++i)
#define repp(i,n) for(int i = 1; i <= (n); ++i)
#define srep(i,s,t) for (int i = s; i < (t); ++i)
#define srep1(i,s,t,u) for (int i = s; i < (t); i += (u))
#define drep0(n) for(int _ = (n)-1; _ >= 0; --_)
#define drep1(i,n) for(int i = (n)-1; i >= 0; --i)
#define dsrep(i,s,t) for(int i = (t)-1; i >= s; --i)
#define dsrep1(i,s,t,u) for(int i = (t)-1; i >= s; i -= u)
#define overload4(a, b, c, d, e, ...) e
#define rep(...) overload4(__VA_ARGS__, srep1, srep, rep1, rep0)(__VA_ARGS__)
#define drep(...) \
  overload4(__VA_ARGS__, dsrep1, dsrep, drep1, drep0)(__VA_ARGS__)
#define rng(a) a.begin(),a.end()
#define rrng(a) a.rbegin(),a.rend()
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define em emplace
#define pob pop_back
#define sz(x) (int)(x).size()
#define pcnt __builtin_popcountll
#define koulet srand((unsigned)clock()+(unsigned)time(NULL));
#define newline puts("")
#define vc vector
#define stoi stoll 
template<class T> using vv = vc<vc<T>>;
template<class T> using PQ = priority_queue<T,vc<T>,greater<T>>;
using uint = unsigned; using ull = unsigned long long;
using i128=__int128 ;using u128=unsigned __int128;
using vi = vc<int>; using vvi = vv<int>; using vvvi = vv<vi>;
using ll = long long; using vl = vc<ll>; using vvl = vv<ll>; using vvvl = vv<vl>;
using P = pair<int,int>; using vp = vc<P>; using vvp = vv<P>; using LP = pair<ll,ll>;
using vs = vc<string>; using vb=vc<bool> ; using vlp = vc<LP> ; 
int geti(){int x;scanf("%d",&x);return x;}
vi pm(int n, int s=0) { vi a(n); iota(rng(a),s); return a;}
template<class T1,class T2>istream& operator>>(istream&i,pair<T1,T2>&v){return i>>v.fi>>v.se;}
template<class T1,class T2>ostream& operator<<(ostream&o,const pair<T1,T2>&v){return o<<v.fi<<","<<v.se;}
template<class T>istream& operator>>(istream&i,vc<T>&v){rep(j,sz(v))i>>v[j];return i;}
template<class T>string join(const T&v,const string&d=""){stringstream s;rep(i,sz(v))(i?s<<d:s)<<v[i];return s.str();}
template<class T>ostream& operator<<(ostream&o,const vc<T>&v){if(sz(v))o<<join(v," ");return o;}
template<class T>void vin(vc<T>&a){int n;cin>>n;a=vc<T>(n);cin>>a;}
template<class T>void vin(vv<T>&a){int n,m;cin>>n>>m;a=vv<T>(n,vc<T>(m));cin>>a;}
template<class T1,class T2>void operator--(pair<T1,T2>&a,int){a.fi--;a.se--;}
template<class T1,class T2>void operator++(pair<T1,T2>&a,int){a.fi++;a.se++;}
template<class T>void operator--(vc<T>&a,int){for(T&x:a)x--;}
template<class T>void operator++(vc<T>&a,int){for(T&x:a)x++;}
template<class T>void operator+=(vc<T>&a,T b){for(T&x:a)x+=b;}
template<class T>void operator-=(vc<T>&a,T b){for(T&x:a)x-=b;}
template<class T>void operator*=(vc<T>&a,T b){for(T&x:a)x*=b;}
template<class T>void operator/=(vc<T>&a,T b){for(T&x:a)x/=b;}
template<class T>void operator+=(vc<T>&a,const vc<T>&b){a.insert(a.end(),rng(b));}
template<class T1,class T2>pair<T1,T2>operator+(const pair<T1,T2>&a,const pair<T1,T2>&b){return {a.fi+b.fi,a.se+b.se};}
template<class T1,class T2>pair<T1,T2>operator-(const pair<T1,T2>&a,const pair<T1,T2>&b){return {a.fi-b.fi,a.se-b.se};}
template<class T>pair<T,T>operator*(const pair<T,T>&a,T b){return {a.fi*b,a.se*b};}
template<class T1,class T2>bool mins(T1& x,const T2&y){if(y<x){x=y;return true;}else return false;}
template<class T1,class T2>bool maxs(T1& x,const T2&y){if(x<y){x=y;return true;}else return false;}
template<class T>T min(const vc<T>&a){return *min_element(rng(a));}
template<class T>T max(const vc<T>&a){return *max_element(rng(a));}
template<class Tx,class Ty>Tx dup(Tx x, Ty y){return (x+y-1)/y;}
template<class T>ll suma(const vc<T>&a){ll s=0;for(auto&&x:a)s+=x;return s;}
template<class T>ll suma(const vv<T>&a){ll s=0;for(auto&&x:a)s+=suma(x);return s;}
template<class T>void uni(T&a){sort(rng(a));a.erase(unique(rng(a)),a.end());}
template<class T>void prepend(vc<T>&a,const T&x){a.insert(a.begin(),x);}
template<typename T>T floor(T a, T b){T r=(a%b+b)%b;return (a-r)/b;}
template<typename T>T ceil(T a, T b){return floor(a+b-1,b);}
template<typename T>vc<T> cumsum(vc<T> &a,int off=1){int N=sz(a);vc<T>B(N+1);rep(i, N)B[i+1]=a[i]+B[i];if(off==0)B.erase(B.begin());return B;}
template<class... T>
constexpr auto min(T... a){return min(initializer_list<common_type_t<T...>>{a...});}
template<class... T>
constexpr auto max(T... a){return max(initializer_list<common_type_t<T...>>{a...});}
template<class... T>
void input(T&... a){(cin >> ... >> a);}
#define INT(...) int __VA_ARGS__; input(__VA_ARGS__)
#define LL(...) ll __VA_ARGS__; input(__VA_ARGS__)
#define STR(...) string __VA_ARGS__; input(__VA_ARGS__)
#define CHA(...) char __VA_ARGS__; input(__VA_ARGS__)
#define DBL(...) double __VA_ARGS__; input(__VA_ARGS__)
#define vec(type,name,...) vc<type>name(__VA_ARGS__)
#define VEC(type,name,size) vc<type>name(size);input(name)
#define vv(type,name,h,...) vv<type>name(h,vector<type>(__VA_ARGS__))
#define VV(type,name,h,w) vv<type>name(h,vector<type>(w));input(name)
#define vvv(type,name,h,w,...) vector<vector<vector<type>>>name(h,vector<vector<type>>(w,vector<type>(__VA_ARGS__)))
void scan(int& a){ scanf("%d", &a); }
void scan(unsigned& a){ scanf("%u", &a); }
void scan(long& a){ scanf("%ld", &a); }
void scan(long long& a){ scanf("%lld", &a); }
void scan(unsigned long long& a){ scanf("%llu", &a); }
void scan(char& a){ do{ a = getchar(); }while(a == ' ' || a == '\n'); }
void scan(float& a){ scanf("%f", &a); }
void scan(double& a){ scanf("%lf", &a); }
void scan(long double& a){ scanf("%Lf", &a); }
void scan(vector<bool>& a){ for(unsigned i = 0; i < a.size(); i++){ int b; scan(b); a[i] = b; } }
void scan(char a[]){ scanf("%s", a); }
void scan(string& a){ cin >> a; }
template<class T> void scan(vector<T>&);
template<class T, size_t size> void scan(array<T, size>&);
template<class T, class L> void scan(pair<T, L>&);
template<class T, size_t size> void scan(T(&)[size]);
template<class T> void scan(vector<T>& a){ for(auto&& i : a) scan(i); }
template<class T> void scan(deque<T>& a){ for(auto&& i : a) scan(i); }
template<class T, size_t size> void scan(array<T, size>& a){ for(auto&& i : a) scan(i); }
template<class T, class L> void scan(pair<T, L>& p){ scan(p.first); scan(p.second); }
template<class T, size_t size> void scan(T (&a)[size]){ for(auto&& i : a) scan(i); }
template <std::size_t I = 0, typename... Ts>
typename std::enable_if<I == sizeof...(Ts), void>::type scan_tuple(tuple<Ts...>&){}
template <std::size_t I = 0, typename... Ts>
typename std::enable_if<I < sizeof...(Ts), void>::type scan_tuple(tuple<Ts...>& t) {scan(get<I>(t));scan_tuple<I + 1>(t);}
template <typename... Ts>
void scan(tuple<Ts...>& t) {scan_tuple(t);}
template<class T> void scan(T& a){ cin >> a; }
void in(){}
template <class Head, class... Tail> void in(Head& head, Tail&... tail){ scan(head); in(tail...); }
void print(){ putchar(' '); }
void print(bool a){ printf("%d", a); }
void print(int a){ printf("%d", a); }
void print(unsigned a){ printf("%u", a); }
void print(long a){ printf("%ld", a); }
void print(long long a){ printf("%lld", a); }
void print(unsigned long long a){ printf("%llu", a); }
void print(char a){ printf("%c", a); }
void print(char a[]){ printf("%s", a); }
void print(const char a[]){ printf("%s", a); }
void print(float a){ printf("%.15f", a); }
void print(double a){ printf("%.15f", a); }
void print(long double a){ printf("%.15Lf", a); }
void print(const string& a){ for(auto&& i : a) print(i); }
template<class T> void print(const complex<T>& a){ if(a.real() >= 0) print('+'); print(a.real()); if(a.imag() >= 0) print('+'); print(a.imag()); print('i'); }
template<class T> void print(const vector<T>&);
template<class T, size_t size> void print(const array<T, size>&);
template<class T, class L> void print(const pair<T, L>& p);
template<class T, size_t size> void print(const T (&)[size]);
template<class T> void print(const vector<T>& a){ if(a.empty()) return; print(a[0]); for(auto i = a.begin(); ++i != a.end(); ){ putchar(' '); print(*i); } }
template<class T> void print(const deque<T>& a){ if(a.empty()) return; print(a[0]); for(auto i = a.begin(); ++i != a.end(); ){ putchar(' '); print(*i); } }
template<class T, size_t size> void print(const array<T, size>& a){ print(a[0]); for(auto i = a.begin(); ++i != a.end(); ){ putchar(' '); print(*i); } }
template<class T, class L> void print(const pair<T, L>& p){ print(p.first); putchar(' '); print(p.second); }
template <typename Tuple, size_t... I>
void print_tuple_impl(const Tuple &t, std::index_sequence<I...>) {((I == 0 ? (print(std::get<I>(t))) : (putchar(' '), print(std::get<I>(t)))), ...);}
template <typename... Args>
void print(const tuple<Args...> &t) {print_tuple_impl(t, std::make_index_sequence<sizeof...(Args)>{});}
template<class T, size_t size> void print(const T (&a)[size]){ print(a[0]); for(auto i = a; ++i != end(a); ){ putchar(' '); print(*i); } }
template<class T> void print(const T& a){ cout << a; }
template<class T> int out(const T& t){ print(t); putchar('\n'); return 0; }
template<class Head, class... Tail> int out(const Head& head, const Tail&... tail){ print(head); putchar(' '); out(tail...); return 0; }
const double eps = 1e-10; // a<b -> a<b-eps
const ll LINF = 2'020'000'000'000'000'000;
const int INF = 1001001001;
template <class T>
constexpr T infty = 0;
template <>
constexpr int infty<int> = 1'010'000'000;
template <>
constexpr ll infty<ll> = 2'020'000'000'000'000'000;
template <>
constexpr uint infty<uint> = infty<int>;
template <>
constexpr ull infty<ull> = infty<ll>;
template <>
constexpr i128 infty<i128> = i128(infty<ll>) * 2'000'000'000'000'000'000;
template <>
constexpr double infty<double> = infty<ll>;
template <>
constexpr long double infty<long double> = infty<ll>;
// (0, 1, 2, 3, 4) -> (-1, 0, 1, 1, 2)
int topbit(int x) { return (x == 0 ? -1 : 31 - __builtin_clz(x)); }
int topbit(uint x) { return (x == 0 ? -1 : 31 - __builtin_clz(x)); }
int topbit(ll x) { return (x == 0 ? -1 : 63 - __builtin_clzll(x)); }
int topbit(ull x) { return (x == 0 ? -1 : 63 - __builtin_clzll(x)); }
// (0, 1, 2, 3, 4) -> (-1, 0, 1, 0, 2)
int lowbit(int x) { return (x == 0 ? -1 : __builtin_ctz(x)); }
int lowbit(uint x) { return (x == 0 ? -1 : __builtin_ctz(x)); }
int lowbit(ll x) { return (x == 0 ? -1 : __builtin_ctzll(x)); }
int lowbit(ull x) { return (x == 0 ? -1 : __builtin_ctzll(x)); }
inline ll __lg(ull x){ return 63 - __builtin_clzll(x); }
#define dame { puts("-1"); return 0 ;}
#define yes { puts("Yes"); return 0 ;}
#define no { puts("No"); return 0 ;}
#define rtn(x) { cout<<(x)<<endl;} // flush!
#define yn {puts("Yes");}else{puts("No");}
ll c2(ll n) { return n*(n-1)>>1;}
template<typename T>void rot(T& a,int i){rotate(a.begin(),a.begin()+(i),a.end());}// i回シフト
template<typename T>void rot(vv<T>& a){int h=sz(a),w=sz(a[0]);vv<T> p(w,vc<T>(h));swap(a,p);rep(i,h)rep(j,w)a[j][h-1-i]=p[i][j];}
void rot(vc<string>& a){int h=sz(a),w=sz(a[0]);vc<string> p(w,string(h,'?'));swap(a,p);rep(i,h)rep(j,w)a[j][h-1-i]=p[i][j];}
//90度時計回り回転
const int dx[] = {-1,0,1,0,1,1,-1,-1,}, dy[] = {0,-1,0,1,1,-1,1,-1}; //^<v>↘︎
//^, <, v, >, ↘︎, ↙︎, ↗︎, ↖︎ 

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

#line 2 "fps/transposed_ntt.hpp"
template <class mint>
void transposed_ntt(vector<mint>& a, bool inverse) {
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
    int len = h;
    while (len > 0) {
      if (len == 1) {
        int p = 1 << (h - len);
        mint rot = 1;
        rep(s, 1 << (len - 1)) {
          int offset = s << (h - len + 1);
          rep(i, p) {
            ull l = a[i + offset].val;
            ull r = a[i + offset + p].val;
            a[i + offset] = l + r;
            a[i + offset + p] = (mod + l - r) * rot.val;
          }
          rot *= rate2[topbit(~s & -~s)];
        }
        len--;
      } else {
        int p = 1 << (h - len);
        mint rot = 1, imag = root[2];
        rep(s, (1 << (len - 2))) {
          int offset = s << (h - len + 2);
          mint rot2 = rot * rot;
          mint rot3 = rot2 * rot;
          for (int i = 0; i < p; i++) {
            ull a0 = a[i + offset + 0 * p].val;
            ull a1 = a[i + offset + 1 * p].val;
            ull a2 = a[i + offset + 2 * p].val;
            ull a3 = a[i + offset + 3 * p].val;
            ull x = (mod + a2 - a3) * imag.val % mod;
            a[i + offset] = a0 + a1 + a2 + a3;
            a[i + offset + 1 * p] = (a0 + mod - a1 + x) * rot.val;
            a[i + offset + 2 * p] = (a0 + a1 + 2 * mod - a2 - a3) * rot2.val;
            a[i + offset + 3 * p] = (a0 + 2 * mod - a1 - x) * rot3.val;
          }
          rot *= rate3[topbit(~s & -~s)];
        }
        len -= 2;
      }
    }
  } else {
    mint coef = mint(1) / mint(sz(a));
    rep(i, sz(a)) a[i] *= coef;
    int len = 0;
    while (len < h) {
      if (len == h - 1) {
        int p = 1 << (h - len - 1);
        mint irot = 1;
        rep(s, 1 << len) {
          int offset = s << (h - len);
          rep(i, p) {
            auto l = a[i + offset];
            auto r = a[i + offset + p] * irot;
            a[i + offset] = l + r;
            a[i + offset + p] = l - r;
          }
          irot *= irate2[topbit(~s & -~s)];
        }
        len++;
      } else {
        int p = 1 << (h - len - 2);
        mint irot = 1, iimag = iroot[2];
        for (int s = 0; s < (1 << len); s++) {
          mint irot2 = irot * irot;
          mint irot3 = irot2 * irot;
          int offset = s << (h - len);
          for (int i = 0; i < p; i++) {
            ull mod2 = ull(mod) * mod;
            ull a0 = a[i + offset].val;
            ull a1 = ull(a[i + offset + p].val) * irot.val;
            ull a2 = ull(a[i + offset + 2 * p].val) * irot2.val;
            ull a3 = ull(a[i + offset + 3 * p].val) * irot3.val;
            ull a1na3imag = (a1 + mod2 - a3) % mod * iimag.val;
            ull na2 = mod2 - a2;
            a[i + offset] = a0 + a2 + a1 + a3;
            a[i + offset + 1 * p] = a0 + a2 + (2 * mod2 - (a1 + a3));
            a[i + offset + 2 * p] = a0 + na2 + a1na3imag;
            a[i + offset + 3 * p] = a0 + na2 + (mod2 - a1na3imag);
          }
          irot *= irate3[topbit(~s & -~s)];
        }
        len += 2;
      }
    }
  }
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

#line 2 "library/poly/fft.hpp"
namespace CFFT {
    using real = double;
    struct C {
        real x, y;

        C() : x(0), y(0) {}

        C(real x, real y) : x(x), y(y) {}

        inline C operator+(const C &c) const {
            return C(x + c.x, y + c.y);
        }

        inline C operator-(const C &c) const {
            return C(x - c.x, y - c.y);
        }

        inline C operator*(const C &c) const {
            return C(x * c.x - y * c.y, x * c.y + y * c.x);
        }

        inline C conj() const {
            return C(x, -y);
        }
    };
    const real PI = acosl(-1);
    int base = 1;
    vector<C> rts = {{0, 0}, {1, 0}};
    vector<int> rev = {0, 1};
    void ensure_base(int nbase) {
        if (nbase <= base)
            return;
        rev.resize(1 << nbase);
        rts.resize(1 << nbase);
        for (int i = 0; i < (1 << nbase); i++) {
            rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));
        }
        while (base < nbase) {
            real angle = PI * 2.0 / (1 << (base + 1));
            for (int i = 1 << (base - 1); i < (1 << base); i++) {
                rts[i << 1] = rts[i];
                real angle_i = angle * (2 * i + 1 - (1 << base));
                rts[(i << 1) + 1] = C(cos(angle_i), sin(angle_i));
            }
            ++base;
        }
    }
    void fft(vector<C> &a, int n) {
        assert((n & (n - 1)) == 0);
        int zeros = __builtin_ctz(n);
        ensure_base(zeros);
        int shift = base - zeros;
        for (int i = 0; i < n; i++) {
            if (i < (rev[i] >> shift)) {
                swap(a[i], a[rev[i] >> shift]);
            }
        }
        for (int k = 1; k < n; k <<= 1) {
            for (int i = 0; i < n; i += 2 * k) {
                for (int j = 0; j < k; j++) {
                    C z = a[i + j + k] * rts[j + k];
                    a[i + j + k] = a[i + j] - z;
                    a[i + j] = a[i + j] + z;
                }
            }
        }
    }
} // namespace CFFT

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

template <typename R>
vc<double> convolution_fft(const vc<R>& a, const vc<R>& b) {
    using C = CFFT::C;
    int need = (int)a.size() + (int)b.size() - 1;
    int nbase = 1;
    while ((1 << nbase) < need) nbase++;
    CFFT::ensure_base(nbase);
    int sz = 1 << nbase;
    vector<C> fa(sz);
    for (int i = 0; i < sz; i++) {
        double x = (i < (int)a.size() ? a[i] : 0);
        double y = (i < (int)b.size() ? b[i] : 0);
        fa[i] = C(x, y);
    }
    CFFT::fft(fa, sz);
    
    C r(0, -0.25 / (sz >> 1)), s(0, 1), t(0.5, 0);
    for (int i = 0; i <= (sz >> 1); i++) {
        int j = (sz - i) & (sz - 1);
        C z = (fa[j] * fa[j] - (fa[i] * fa[i]).conj()) * r;
        fa[j] = (fa[i] * fa[i] - (fa[j] * fa[j]).conj()) * r;
        fa[i] = z;
    }
    for (int i = 0; i < (sz >> 1); i++) {
        C A0 = (fa[i] + fa[i + (sz >> 1)]) * t;
        C A1 = (fa[i] - fa[i + (sz >> 1)]) * t * CFFT::rts[(sz >> 1) + i];
        fa[i] = A0 + A1 * s;
    }
    CFFT::fft(fa, sz >> 1);
    
    vector<double> ret(need);
    for (int i = 0; i < need; i++) {
        ret[i] = (i & 1 ? fa[i >> 1].y : fa[i >> 1].x);
    }
    return ret;
}

vector<ll> convolution(const vector<ll>& a, const vector<ll>& b) {
    int n = sz(a), m = sz(b);
    if (!n || !m) return {};
    if (min(n, m) <= 2500) return convolution_naive(a, b);

    ll abs_sum_a = 0, abs_sum_b = 0;
    ll LIM = 1e15;
    rep(i, n) abs_sum_a = min(LIM, abs_sum_a + abs(a[i]));
    rep(i, m) abs_sum_b = min(LIM, abs_sum_b + abs(b[i]));

    if (i128(abs_sum_a) * abs_sum_b < 1e15) {
        vc<double> c = convolution_fft<ll>(a, b);
        vc<ll> res(sz(c));
        rep(i, sz(c)) res[i] = ll(floor(c[i] + .5));
        return res;
    }

    static constexpr unsigned long long MOD1 = 754974721;  // 2^24
    static constexpr unsigned long long MOD2 = 167772161;  // 2^25
    static constexpr unsigned long long MOD3 = 469762049;  // 2^26
    static constexpr unsigned long long M2M3 = MOD2 * MOD3;
    static constexpr unsigned long long M1M3 = MOD1 * MOD3;
    static constexpr unsigned long long M1M2 = MOD1 * MOD2;
    static constexpr unsigned long long M1M2M3 = MOD1 * MOD2 * MOD3;

    static const unsigned long long i1 = mod_inv(MOD2 * MOD3, MOD1);
    static const unsigned long long i2 = mod_inv(MOD1 * MOD3, MOD2);
    static const unsigned long long i3 = mod_inv(MOD1 * MOD2, MOD3);

    using mint1 = modint<MOD1>;
    using mint2 = modint<MOD2>;
    using mint3 = modint<MOD3>;

    vc<mint1> a1(n), b1(m);
    vc<mint2> a2(n), b2(m);
    vc<mint3> a3(n), b3(m);
    rep(i, n) {
        a1[i] = a[i];
        a2[i] = a[i];
        a3[i] = a[i];
    }
    rep(i, m) {
        b1[i] = b[i];
        b2[i] = b[i];
        b3[i] = b[i];
    }

    auto c1 = convolution_ntt<mint1>(a1, b1);
    auto c2 = convolution_ntt<mint2>(a2, b2);
    auto c3 = convolution_ntt<mint3>(a3, b3);

    vc<ll> c(n + m - 1);
    rep(i, n + m - 1) {
        ull x = 0;
        x += (c1[i].val * i1) % MOD1 * M2M3;
        x += (c2[i].val * i2) % MOD2 * M1M3;
        x += (c3[i].val * i3) % MOD3 * M1M2;
        ll diff = c1[i].val - ((long long)(x) % (long long)(MOD1));
        if (diff < 0) diff += MOD1;
        static constexpr unsigned long long offset[5] = {
            0, 0, M1M2M3, 2 * M1M2M3, 3 * M1M2M3
        };
        x -= offset[diff % 5];
        c[i] = x;
    }
    return c;
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

#line 2 "fps/convolution2d.hpp"
template <typename T>
vc<vc<T>> convolution2d(vc<vc<T>>& f, vc<vc<T>>& g) {
  auto shape = [&](vc<vc<T>>& f) -> LP {
    ll H = sz(f);
    ll W = (H == 0 ? 0 : sz(f[0]));
    return {H, W};
  };
  auto [H1, W1] = shape(f);
  auto [H2, W2] = shape(g);
  ll H = H1 + H2 - 1;
  ll W = W1 + W2 - 1;
  vc<T> ff(H1 * W);
  vc<T> gg(H2 * W);
  rep(x, H1) rep(y, W1) ff[W * x + y] = f[x][y];
  rep(x, H2) rep(y, W2) gg[W * x + y] = g[x][y];
  auto hh = convolution(ff, gg);
  vc<vc<T>> h(H, vc<T>(W));
  rep(x, H) rep(y, W) h[x][y] = hh[W * x + y];
  return h;
}

#line 2 "poly/ntt_doubling.hpp"
// 2^k 次多項式の長さ 2^k が与えられるので 2^k+1 にする
template <typename mint, bool transposed = false>
void ntt_doubling(vector<mint>& a) {
  static array<mint, 30> root;
  static bool prepared = 0;
  if (!prepared) {
    prepared = 1;
    const int rank2 = mint::ntt_info().fi;
    root[rank2] = mint::ntt_info().se;
    drep(i, rank2) { root[i] = root[i + 1] * root[i + 1]; }
  }

  if constexpr (!transposed) {
    const int M = (int)a.size();
    auto b = a;
    ntt(b, 1);
    mint r = 1, zeta = root[topbit(2 * M)];
    rep(i, M) b[i] *= r, r *= zeta;
    ntt(b, 0);
    copy(begin(b), end(b), back_inserter(a));
  } else {
    const int M = len(a) / 2;
    vc<mint> tmp = {a.begin(), a.begin() + M};
    a = {a.begin() + M, a.end()};
    transposed_ntt(a, 0);
    mint r = 1, zeta = root[topbit(2 * M)];
    rep(i, M) a[i] *= r, r *= zeta;
    transposed_ntt(a, 1);
    rep(i, M) a[i] += tmp[i];
  }
}

template <typename mint>
int count_terms(const vc<mint>& f) {
  int t = 0;
  rep(i, sz(f)) if (f[i] != mint(0))++ t;
  return t;
}

struct fps : vm {
#define d (*this)
#define s int(vm::size())
  template<class...Args> fps(Args...args): vm(args...) {}
  fps(initializer_list<mint> a): vm(rng(a)) {}
  int size() const { return vm::size();}
  void rsz(int n) { if (s < n) resize(n);}
  fps& low_(int n) { resize(n); return d;}
  fps low(int n) const { return fps(d).low_(n);}
  fps low(fps a, int n) const { return a.low_(n);}
  fps& rev_() { reverse(rng(d)); return d;}
  fps rev() const { return fps(d).rev_();}
  fps rev(fps a) const { return a.rev_();}
  fps odd(int si=1) const { fps r(s/2); for(int i=si;i<s;i+=2) r[i>>1]=d[i]; return r;}
  inline fps& normalize(){
		while(!d.empty()&&d.back()==0)  d.pop_back() ;
		return d;
}
  inline fps pre(int n)const {return fps(d.begin(),d.begin()+min(sz(d),n)) ;}
  mint& operator[](int i) { rsz(i+1); return vm::operator[](i);}
  mint operator[](int i) const { return i<s ? vm::operator[](i) : 0;}
  mint operator()(mint x) const { mint r; drep(i,s) r = r*x+d[i]; return r;}
  fps operator<<(int a) const { fps r(d); r.insert(r.begin(), a, 0); return r;}
  fps operator>>(int a) const { fps r(d); r.rsz(a); r.erase(r.begin(), r.begin()+a); return r;}
  fps& fit() { while (s && !back().val) pop_back(); return d;}
  fps operator-() const { fps r(d); rep(i,s) r[i] = -r[i]; return r;}
  // inline fps& operator+=(const fps& a) { rsz(sz(a)); rep(i,sz(a)) d[i] += a[i]; return this->normalize();}
  fps& operator+=(const fps& a) { rsz(sz(a)); rep(i,sz(a)) d[i] += a[i]; return d ;}
  //inline fps& operator-=(const fps& a) { rsz(sz(a)); rep(i,sz(a)) d[i] -= a[i];return this->normalize();}
  fps& operator-=(const fps& a) { rsz(sz(a)); rep(i,sz(a)) d[i] -= a[i];return d;}
  fps& operator*=(const fps& a) {return d = convolution(d, a) ;}
  fps& operator/=(const fps& a) {
		assert(!a.empty()) ;assert(a.back() != 0) ; d.normalize() ;
		if(s < sz(a)){ d=fps(1,0) ; return d; } 
		int w=s-sz(a)+1 ;
	    return d=(d.rev().pre(w) * (a.rev()).inv(w)).pre(w).rev() ;
  }

  fps& operator%=(const fps& a) {
		assert(!a.empty());
		assert(a.back() != 0) ;
		d.normalize() ; fps q=d/a; 
		return d -= q*a; 
  }
  fps& operator*=(mint a) { rep(i,s) d[i] *= a; return d;}
  fps& operator/=(mint a) { return d *= ~(a);}
  fps& operator*=(int a) { return d *= mint(a);}
  fps& operator/=(int a) { return d /= mint(a);}
  fps operator+(const fps& a) const { return fps(d) += a;}
  fps operator-(const fps& a) const { return fps(d) -= a;}
  fps operator*(const fps& a) const { return fps(d) *= a;}
  fps operator/(const fps& a) const { return fps(d) /= a;}
  fps operator%(const fps& a) const { return fps(d) %= a;}
  fps operator*(mint a) const { return fps(d) *= a;}
  fps operator/(mint a) const { return fps(d) *= ~(a);}
  fps operator*(int a) const { return fps(d) *= mint(a);}
  fps operator/(int a) const { return fps(d) /= mint(a);}
  fps& mul1(mint a) { pb(0); drep(i,s-1) d[i+1] += d[i], d[i] *= a; return d;} // *=(x+a), /=(x+a)
  fps& div1(mint a) { mint pre = back(); pop_back(); drep(i,s) std::swap(pre, d[i]), pre -= d[i]*a; return d;}
  fps dif() const{if(s<=1){return {};}fps r(s-1);repp(i,sz(r))r[i-1]=d[i]*i; return r;}

  // [L , R] で積分
  mint integ(mint L, mint R){
		mint I=0 ; mint pow_L=1,pow_R=1;
		rep(i,sz(d)){pow_L *= L, pow_R*=R ; I+=~mint(i+1)*d[i]*(pow_R-pow_L) ;}
		return I ;
  }
  fps integ() const { fps r(s+1); repp(i,s) r[i] = d[i-1]/(mint)i; return r;}
   
 //   // f/g. f の長さで出力される.
	// inline friend fps div_sparse(const fps&f, const fps&g, int deg=-1){
	// 	int n=(deg==-1?sz(f):deg) ;
	// 	fps fj=f, gi=g ;
	// 	if(g[0]!=mint(1)){
	// 		mint cf=g[0].inv() ;for(auto &&x:fj) x *= cf;for(auto &&x:gi) x *=cf; 
	// 	}
	// 	vc<pair<int,mint>> dat ;
	// 	rep(i,1,sz(g))if(gi[i]!=mint(0)) dat.eb(i,-gi[i]) ;
	// 	rep(i, sz(f)) for(auto&&[j, x]:dat)if(i>=j) fj[i]+=x*fj[i-j] ;
	// 	fj.resize(n) ;return fj ;
	// }
	//
	// template<bool SPARSE=false>
	// inline friend fps div(const fps &f, const fps&g, int deg=-1){
	// 	fps gi=g ,fj=f ;
	// 	int n=(deg==-1?sz(f):deg) ;
	// 	if(SPARSE||count_terms(g)<200) return div_sparse(f,g,n) ;
	// 	gi.resize(n) ;gi=g.inv() ; fj=convolution(f,gi) ;fj.resize(n);
	// 	return fj ;
	// }

	// sparse 版：出力項数を deg とする（deg=-1 の場合は sz(f) を使う）
	inline friend fps inv_sparse(const fps &f, int deg=-1) {
	  int N = (deg == -1 ? sz(f) : deg);
	  vc<pair<int, mint>> dat;
	  rep(i, 1, min(sz(f), N)) { 
		if (f[i] != mint(0)) dat.eb(i, f[i]);
	  }
	  vm g(N, mint(0));
	  mint g0 = mint(1) / f[0];
	  g[0] = g0;
	  rep(i, 1, N) {
		mint rhs = 0;
		for (auto&& [k, fk] : dat) {
		  if (k > i) break;
		  rhs -= fk * g[i - k];
		}
		g[i] = rhs * g0;
	  }
	  return g;
	}

	// dense 版：NTT版
	inline friend fps inv_dense_ntt(const fps &F, int deg=-1) {
	  vm G = {F[0].inv()};
	  if(deg==-1) deg=sz(F) ;
	  ll N = deg, n = 1;
	  G.reserve(N);
	  while(n < N) {
		vc<mint> f(2*n), g(2*n);
		rep(i, min((int)sz(F), (int)(2*n))) f[i] = F[i];
		rep(i, n) g[i] = G[i];
		ntt(f, false), ntt(g, false);
		rep(i, 2*n) f[i] *= g[i];
		ntt(f, true);
		rep(i, n) f[i] = 0;
		ntt(f, false);
		rep(i, 2*n) f[i] *= g[i];
		ntt(f, true);
		rep(i, n, min((int)N, (int)(2*n))) G.eb(-f[i]);
		n *= 2;
	  }
	  G.resize(N);
	  return G;
	}

	// dense 版：NTTが使えない場合
	inline friend fps inv_dense(const fps &F, int deg=-1) {
	  if (mint::can_ntt()) return inv_dense_ntt(F, deg);
	  const int N = (deg==-1?sz(F):deg);
	  vm R = {mint(1) / F[0]};
	  vm p;
	  int m = 1;
	  while (m < N) {
		p = convolution(R, R);
		p.resize(m + m);
		vm f = {F.begin(), F.begin() + min(m + m, (int)sz(F))};
		p = convolution(p, f);
		R.resize(m + m);
		rep(i, m + m) R[i] = R[i] + R[i] - p[i];
		m += m;
	  }
	  R.resize(N);
	  return R;
	}

	// friend 版：deg の指定を追加。deg が -1 なら sz(f) を使う
	inline friend fps fps_inv(const fps &f, int deg = -1) {
	  int di = (deg == -1 ? sz(f) : deg);
	  assert(f[0] != mint(0));
	  int n = count_terms(f);
	  int t = (mint::can_ntt() ? 160 : 820);
	  return (n <= t ? inv_sparse(f, di) : inv_dense(f, di));
	}

  fps inv(int w)const {return fps_inv(d, w);}
  fps inv() const {return inv(s);}

  inline friend fps gcd(const fps &f, const fps &g){
		if(g.empty()) return f; 
		return gcd(g, f%g) ;
  }
  
  // log(f) = \int f'/f dx, f[0] must be 1
  fps log(int w)const {return fps_log(d, w);}
  fps log() const {return log(s);}

  inline friend fps log_dense(const fps &f, int deg=-1){
		assert(f[0]==mint(1)) ;
		int N = (deg == -1 ? sz(f) : deg);
		fps F = f; F.resize(N);vm df = F;
		rep(i, N) df[i] *= mint(i);
		df.erase(df.begin()); // df は (f[1]*1, f[2]*2, ... )
		fps f_inv = F.inv();
		auto g = convolution(df, f_inv);
		g.resize(N - 1);
		g.insert(g.begin(), 0);
		rep(i, N) g[i] *= invs(i);
		return g;
  }
  
  inline friend fps fps_log(const fps& f, int deg = -1){
		assert(f[0] == mint(1)) ;int n = count_terms(f);
		int t = (mint::can_ntt() ? 200 : 1200);
  return (n<= t?log_sparse(f, deg):log_dense(f, deg));
}

  inline friend fps log_sparse(const fps& f, int deg = -1) {
	  int N = (deg == -1 ? f.size() : deg);
	  vc<mint> F = f;
	  F.resize(N);
	  vc<pair<int, mint>> dat;
	  rep(i, 1, N) if (F[i] != mint(0)) dat.eb(i, F[i]);
	  vc<mint> g(N - 1, mint(0));
	  vc<mint> res(N, mint(0));
	  for (int n = 0; n < N - 1; ++n) {
		mint rhs = mint(n + 1) * F[n + 1];
		for (auto&& [i, fj] : dat) {
		  if (i > n) break;
		  rhs -= fj * g[n - i];
		}
		g[n] = rhs;
		res[n + 1] = rhs * invs(n + 1);
	  }
	  return res;
}

  // exp(f), f[0] must be 0
  inline friend fps exp_dense(const fps &H, int deg=-1){
		fps h = H ;
		if(deg==-1) deg=sz(h) ;
	    const int n = sz(h);
		assert(n > 0 && h[0] == mint(0));
		if (mint::can_ntt()) {
		vm f = h;
		vm b = {1, (1 < n ? f[1] : 0)};
		vm c = {1}, z1, z2 = {1, 1};
		while (sz(b) < deg) {
		  int m = sz(b);
		  auto y = b;
		  y.resize(2 * m);
		  ntt(y, 0);
		  z1 = z2;
		  vc<mint> z(m);
		  rep(i, m) z[i] = y[i] * z1[i];
		  ntt(z, 1);
		  rep(i, m / 2) z[i] = 0;
		  ntt(z, 0);
		  rep(i, m) z[i] *= -z1[i];
		  ntt(z, 1);
		  c.insert(c.end(), z.begin() + m / 2, z.end());
		  z2 = c;
		  z2.resize(2 * m);
		  ntt(z2, 0);

		  vc<mint> x(f.begin(), f.begin() + m);
		  rep(i, sz(x) - 1) x[i] = x[i + 1] * mint(i + 1);
		  x.back() = 0;
		  ntt(x, 0);
		  rep(i, m) x[i] *= y[i];
		  ntt(x, 1);

		  rep(i, m - 1) x[i] -= b[i + 1] * mint(i + 1);

		  x.resize(m + m);
		  rep(i, m - 1) x[m + i] = x[i], x[i] = 0;
		  ntt(x, 0);
		  rep(i, m + m) x[i] *= z2[i];
		  ntt(x, 1);
		  drep(i,sz(x) - 1) x[i + 1] = x[i] * invs(i + 1);
		  x[0] = 0;

		  rep(i, m, min(deg, m + m)) x[i] += f[i];
		  rep(i, m) x[i] = 0;
		  ntt(x, 0);
		  rep(i, m + m) x[i] *= y[i];
		  ntt(x, 1);
		  b.insert(b.end(), x.begin() + m, x.end());
		}
		b.resize(deg);
		return b;
	  }
	  const int L = (deg==-1?sz(h):deg) ;
	  assert(L > 0 && h[0] == mint(0));
	  int LOG = 0;
	  while (1 << LOG < L) ++LOG;
	  h.resize(1 << LOG);
	  auto dh = h.dif();
	  vc<mint> f = {1}, g = {1};
	  int m = 1;
	  fps p;
	  rep(LOG) {
		p = convolution(f, g);
		p.resize(m);
		p = convolution(p, g);
		p.resize(m);
		g.resize(m);
		rep(i, m) g[i] += g[i] - p[i];
		p = {dh.begin(), dh.begin() + m - 1};
		p = convolution(f, p);
		p.resize(m + m - 1);
		rep(i, m + m - 1) p[i] = -p[i];
		rep(i, m - 1) p[i] += mint(i + 1) * f[i + 1];
		p = convolution(p, g);

		p.resize(m + m - 1);
		rep(i, m - 1) p[i] += dh[i];
		p = p.integ() ;
		rep(i, m + m) p[i] = h[i] - p[i];
		p[0] += mint(1);
		f = convolution(f, p);
		f.resize(m + m);
		m += m;
	  }
	  f.resize(L);
	  return f;
  } 

  inline friend fps exp_sparse(const fps &f, int deg=-1){
	  int N=(deg==-1?sz(f):deg) ;
	  if (sz(f) == 0) return {mint(1)};
	  assert(f[0] == 0);
	  vc<pair<int, mint>> dat;
	  rep(i, 1, sz(f)) if (f[i] != mint(0)) dat.eb(i - 1, mint(i) * f[i]) ;
	  vc<mint> F(N);
      F[0] = 1;
	  rep(n, 1, N) {
		mint rhs = 0;
		for (auto&& [k, fk]: dat) {
		  if (k > n - 1) break;
		  rhs += fk * F[n - 1 - k];
		}
		F[n] = rhs * invs(n);
	  }
	  return F;
  } 

  inline friend fps fps_exp(const fps&f, int deg=-1){
		if(deg==-1) deg=sz(f) ;
		int n=count_terms(f) ;int t=(mint::can_ntt()?320:3000) ;
		return (n<=t?exp_sparse(f,deg):exp_dense(f,deg)) ;
  }

  fps exp(int w)const {return fps_exp(d, w);}
  fps exp()const {return exp(s);}

  inline friend fps pow_1_sparse(const fps&f, mint k, int deg=-1){
		int N=(deg==-1?sz(f):deg) ;assert(N == 0 || f[0] == mint(1)) ;
		vc<pair<int,mint>> dat ; 
		rep(i, 1,sz(f)) if(f[i] != mint(0)) dat.eb(i,f[i]) ;
		vm g(N) ;g[0]=1; 
		rep(n, N-1){
			mint &x=g[n+1] ;
			for(auto &&[di, cf]:dat){
				if(di>n+1) break ;
				mint t=cf*g[n-di+1] ;
				x += t*(k*mint(di)-mint(n-di+1)) ;
			}
			x *= invs(n+1) ;
		}
		return g ;
  }

  inline friend fps pow_1_dense(const fps&f, mint k, int deg=-1){
		int N=(deg==-1?sz(f):deg) ;assert(f[0] == mint(1)) ;
		auto log_f=f.log(N) ;
		rep(i, N)  log_f[i]*=k ; 
		return exp_dense(log_f, N) ;
  }

  inline friend fps pow_1(const fps&f, mint k, int deg=-1){
		int n=count_terms(f) ;int t=(mint::can_ntt()?100:100) ;
		return (n<=t?pow_1_sparse(f,k,deg):pow_1_dense(f,k,deg)) ;
  }

  inline friend fps fps_pow(const fps &f, ll k, int deg=-1){
		assert(0 <= k) ; int n=sz(f) ;if(deg==-1) deg=n ;
		if(k == 0) {fps g(deg);g[0]=mint(1); return g ;}
		int di=n ; drep(i, n)if(f[i]!=mint(0)) di=i ; 
		if(di>=ceil<ll>(deg,k)){ fps g(deg) ; return g ;}
		ll off=di*k ;mint c=f[di] ; mint c_inv=c.inv() ;
		fps g_part(deg-off) ;
		rep(i, deg-off){
			if(di + i < n) g_part[i]=f[di+i]*c_inv ; 
			else g_part[i]=mint(0);
		}
		g_part=pow_1(g_part,mint(k),deg-off) ;
		fps h(deg) ;c = c.pow(k) ;rep(i, sz(g_part)) h[off+i]=g_part[i]*c ;
		return h ;
  }
  // fps の k 乗を求める。k >= 0 の前提である
  // 定数項が 1 で、k が mint の場合には、fps_pow_1 を使うこと 
  // ・dense な場合： log, exp を使う O(NlogN) 
  // ・sparse な場合： O(NK)

  fps pow(ll k, int deg)const {return fps_pow(d, k, deg);}
  fps pow(ll k)const {return pow(k, s);}

   
  // sparse は 基本的には 非零の項が10以下くらいが適切
  // sparse の乗算
  fps &operator*=(vector<pair<int,mint>> g){
		int n=sz(d) ;
		auto [a, c]=g.front() ;
		if(a == 0) g.erase(g.begin()) ;
		else c=0 ;
		drep(i, n){
			d[i]*= c;
			for(auto &[j, b]:g){
				if(j>i) break  ;
				d[i] += d[i-j]*b ; 
			}
		}
		return d;
	}

   // sparse の 徐算
   fps &operator/=(vector<pair<int, mint>> g) {
		    int n = (*this).size();
		    auto [a, c] = g.front();
		    assert(a == 0 && c != mint(0));
		    mint cmi = c ;
		    mint ic = mint(1)/mint(c) ;
		    g.erase(g.begin());
		    for(ll i = 0; i<n ;i++){
			      for (auto &&[j, b] : g) {
				        if (j > i) break;
				        (*this)[i] -= (*this)[i-j] * b;
				      }
			      (*this)[i] *= ic;
			    }
		    return *this;
  }

  vm operator()(const vm& x) const {
    int n = sz(x), n2 = n<<1;
    vc<fps> t(n2);
    rep(i,n) t[n+i] = {-x[i],1};
    for (int i = n-1; i; --i) t[i] = t[i<<1]*t[i<<1|1];
    t[1] = d%t[1];
    srep(i,2,n2) t[i] = t[i>>1]%t[i];
    vm r(n);
    rep(i,n) r[i] = t[n+i][0];
    return r;
  }

  fps taylorShift(mint c) const {
	const int n = s ;
    fps res, a(n), b(n,1);
    rep(i,s) a[i] = d[i]*facs(i);
    drep(i,s-1) b[i] = b[i+1]*c;
    rep(i,s) b[i] *= ifacs(s-1-i);
    a *= b;
    rep(i,s) res[i] = a[s-1+i]*ifacs[i];
    return res;
  }
  fps combConv(bool _inv=true) const {
	const int n = s ;
    fps res, a(n), b(n);
    rep(i,s) a[i] = d[i]*ifacs(i);
    rep(i,s) b[i] = ifacs(i);
    if (_inv) rep(i,s) if (i&1) b[i] = -b[i];
    a *= b;
    rep(i,s) res[i] = a[i]*facs(i);
    return res;
  }
  // find [x^N] P(x)/Q(x)
  // O(K log K log N), K = max(deg(P(x)), deg(Q(x)))
  mint bostanMori(ll n, fps p={1}) const {
    if (n == 0) return p[0]/d[0];
    fps q(*this); for (int i = 1; i < s; i += 2) q[i] = -q[i];
    p = (p*q).odd(n&1);
    q = (d*q).odd(0);
    return q.bostanMori(n>>1,p);
  }
#undef s
#undef d
};

#line 2 "fps/fps_div.hpp"
// f/g. f の長さで出力される.
template <typename mint, bool SPARSE = false>
vc<mint> fps_div(vc<mint> f, vc<mint> g) {
  if (SPARSE || count_terms(g) < 200) return fps_div_sparse(f, g);
  int n = sz(f);
  g.resize(n);
  fps gi=g ;
  g = gi.inv() ;
  f = convolution(f, g);
  f.resize(n);
  return f;
}

// f/g ただし g は sparse
template <typename mint>
vc<mint> fps_div_sparse(vc<mint> f, vc<mint>& g) {
  if (g[0] != mint(1)) {
    mint cf = g[0].inv();
    for (auto&& x: f) x *= cf;
    for (auto&& x: g) x *= cf;
  }

  vc<pair<int, mint>> dat;
  rep(i, 1, sz(g)) if (g[i] != mint(0)) dat.eb(i, -g[i]);
  rep(i, sz(f)) {
    for (auto&& [j, x]: dat) {
      if (i >= j) f[i] += x * f[i - j];
    }
  }
  return f;
}

#line 1 "random/random.hpp"
struct RandomNumberGenerator {
  mt19937 mt;
  RandomNumberGenerator() : mt(chrono::steady_clock::now().time_since_epoch().count()) {}
  ll operator()(ll a, ll b) {  // [a, b)
    uniform_int_distribution<ll> dist(a, b - 1);
    return dist(mt);
  }
  ll operator()(ll b) {  // [0, b)
    return (*this)(0, b);
  }
};

#line 2 "mod/mod_sqrt.hpp"
template <typename mint>
mint mod_sqrt(mint a) {
  int p = mint::get_mod();
  if (p == 2) return a;
  if (a == 0) return 0;
  int k = (p - 1) / 2;
  if (a.pow(k) != 1) return 0;
  RandomNumberGenerator RNG;
  auto find = [&]() -> pair<mint, mint> {
    while (1) {
      mint b = RNG(2, p);
      mint D = b * b - a;
      if (D == 0) return {b, D};
      if (D.pow(k) != mint(1)) return {b, D};
    }
  };
  auto [b, D] = find();
  if (D == 0) return b;
  ++k;
  // (b + sqrt(D))^k
  mint f0 = b, f1 = 1;
  mint g0 = 1, g1 = 0;
  while (k) {
    if (k & 1) { tie(g0, g1)=make_pair(f0 * g0 + D * f1 * g1, f1 * g0 + f0 * g1); }
    tie(f0, f1)=make_pair(f0 * f0 + D * f1 * f1, mint(2) * f0 * f1);
    k >>= 1;
  }
  return g0;
}


#line 2 "fps/fps_sqrt.hpp"
template <typename mint>
vc<mint> fps_sqrt_dense(vc<mint>& f, int deg=-1) {
  assert(f[0] == mint(1));
  int n = (deg==-1?sz(f):deg);
  vc<mint> R = {1};
  while (sz(R) < n) {
    int m = min(2 * int(sz(R)), n);
    R.resize(m);
    vc<mint> tmp = {f.begin(), f.begin() + m};
	fps Rj = fps(R).inv() ;
    tmp = convolution(tmp,Rj);
    tmp.resize(m);
    rep(i, m) R[i] += tmp[i];
    mint c = mint(1) / mint(2);
    rep(i, sz(R)) R[i] *= c;
  }
  R.resize(n);
  return R;
}

template <typename mint>
vc<mint> fps_sqrt_sparse(vc<mint>& f, int deg=-1) {
  if(deg==-1) deg=sz(f) ;
  return pow_1_sparse(fps(f), inv<mint>(2), deg);
}

// sqrt(f), f[0] must be 1
template <typename mint>
vc<mint> fps_sqrt(vc<mint>& f, int deg=-1) {
  deg=(deg==-1?sz(f):deg) ;
  if (count_terms(f) <= 200) return fps_sqrt_sparse(f,deg);
  return fps_sqrt_dense(f,deg);
}

// sqrt(f) f[0] != 1 の場合にも対応する
// 存在しなかったら空の配列を返す 
template <typename mint>
vc<mint> fps_sqrt_any(vc<mint>& f, int deg=-1) {
  int n = (deg==-1?sz(f):deg);
  int d = n;
  drep(i, n) if (f[i] != 0) d = i;
  if (d == n) return f;
  if (d & 1) return {};
  mint y = f[d];
  mint x = mod_sqrt(y);
  if (x * x != y) return {};
  mint c = mint(1) / y;
  vc<mint> g(n - d);
  rep(i, n - d) g[i] = f[d + i] * c;
  g = fps_sqrt(g);
  rep(i, sz(g)) g[i] *= x;
  g.resize(n);
  drep(i, n) {
    if (i >= d / 2)
      g[i] = g[i - d / 2];
    else
      g[i] = 0;
  }
  return g;
}

// n, m 次多項式 (n>=m) a, b → n-m 次多項式 c
// c[i] = sum_j b[j]a[i+j]
template <typename mint>
vc<mint> middle_product(vc<mint>& a, vc<mint>& b) {
  assert(sz(a) >= sz(b));
  if (b.empty()) return vc<mint>(sz(a) - sz(b) + 1);
  if (min(sz(b), sz(a) - sz(b) + 1) <= 60) {
    return middle_product_naive(a, b);
  }
  if (!(mint::can_ntt())) {
    return middle_product_garner(a, b);
  } else {
    int n = 1 << __lg(2 * sz(a) - 1);
    vc<mint> fa(n), fb(n);
    copy(a.begin(), a.end(), fa.begin());
    copy(b.rbegin(), b.rend(), fb.begin());
    ntt(fa, 0), ntt(fb, 0);
    rep(i, n) fa[i] *= fb[i];
    ntt(fa, 1);
    fa.resize(sz(a));
    fa.erase(fa.begin(), fa.begin() + sz(b) - 1);
    return fa;
  }
}

template <typename mint>
vc<mint> middle_product_garner(vc<mint>& a, vc<mint> b) {
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
  auto c0 = middle_product<mint0>(a0, b0);
  auto c1 = middle_product<mint1>(a1, b1);
  auto c2 = middle_product<mint2>(a2, b2);
  vc<mint> c(sz(c0));
  rep(i, n - m + 1) {
    c[i] = CRT3<mint, p0, p1, p2>(c0[i].val, c1[i].val, c2[i].val);
  }
  return c;
}

template <typename mint>
vc<mint> middle_product_naive(vc<mint>& a, vc<mint>& b) {
  vc<mint> res(sz(a) - sz(b) + 1);
  rep(i, sz(res)) rep(j, sz(b)) res[i] += b[j] * a[i + j];
  return res;
}

#line 2 "fps/compositional.hpp"
// f(g(x)), O(Nlog^2N)
template <typename mint>
vc<mint> composition(vc<mint> f, vc<mint> g) {
  assert(sz(f) == sz(g));
  if (f.empty()) return {};
  // [x^0]g=0 に帰着しておく
  if (g[0] != mint(0)) {
	fps fj=f ;
	f = fj.taylorShift(g[0]) ;
    g[0] = 0;
  }
  int n0 = sz(f);
  int n = 1;
  while (n < sz(f)) n *= 2;
  f.resize(n), g.resize(n);
  vc<mint> W(n);
  {
    // bit reverse order
    vc<int> btr(n);
    int log = topbit(n);
    rep(i, n) {
      btr[i] = (btr[i >> 1] >> 1) + ((i & 1) << (log - 1));
    }
    int t = mint::ntt_info().fi;
    mint r = mint::ntt_info().se;
    mint dw = r.inv().pow((1 << t) / (2 * n));
    mint w = 1;
    for (auto& i: btr) {
      W[i] = w, w *= dw;
    }
  }
  auto rec = [&](auto& rec, int n, int k, vc<mint>& Q) -> vc<mint> {
    if (n == 1) {
      reverse(rng(f));
      transposed_ntt(f, 1);
      mint c = mint(1) / mint(k);
      for (auto& x: f) x *= c;
      vc<mint> p(4 * k);
      rep(i, k) p[2 * i] = f[i];
      return p;
    }
    auto doubling_y = [&](vc<mint>& A, int l, int r, bool t) -> void {
      mint z = W[k / 2].inv();
      vc<mint> f(k);
      if (!t) {
        rep(i, l, r) {
          rep(j, k) 
            f[j] = A[2 * n * j + i];
          ntt(f, 1);
          mint r = 1;
          rep(j, 1, k) {
            r *= z;
            f[j] *= r;
          }
          ntt(f, 0);
          rep(j, k)
            A[2 * n * (k + j) + i] = f[j];
        }
      } else {
        rep(i, l, r) {
          rep(j, k)
            f[j] = A[2 * n * (k + j) + i];
          transposed_ntt(f, 0);
          mint r = 1;
          rep(j, 1, k) {
            r *= z;
            f[j] *= r;
          }
          transposed_ntt(f, 1);
          rep(j, k)
            A[2 * n * j + i] += f[j];
        }
      }
    };

    auto FFT_x = [&](vc<mint>& A, int l, int r, bool t) -> void {
      vc<mint> f(2 * n);
      if (!t) {
        rep(j, l, r) {
          move(A.begin() + 2 * n * j, A.begin() + 2 * n * (j + 1), f.begin());
          ntt(f, 0);
          move(rng(f), A.begin() + 2 * n * j);
        }
      } else {
        rep(j, l, r) {
          move(A.begin() + 2 * n * j, A.begin() + 2 * n * (j + 1), f.begin());
          transposed_ntt(f, 0);
          move(rng(f), A.begin() + 2 * n * j);
        }
      }
    };

    if (n <= k) {
      doubling_y(Q, 1, n, false);
      FFT_x(Q, 0, 2 * k, false);
    } else {
      FFT_x(Q, 0, k, false);
      doubling_y(Q, 0, 2 * n, false);
    }
    rep(i, 2 * n * k) Q[i] += 1;
    rep(i, 2 * n * k, 4 * n * k) Q[i] -= 1;

    vc<mint> nxt_Q(4 * n * k);
    vc<mint> F(2 * n), G(2 * n), f(n), g(n);
    rep(j, 2 * k) {
      move(Q.begin() + 2 * n * j, Q.begin() + 2 * n * j + 2 * n, G.begin());
      rep(i, n) { 
        g[i] = G[2 * i] * G[2 * i + 1];
      }
      ntt(g, 1);
      move(g.begin(), g.begin() + n / 2, nxt_Q.begin() + n * j);
    }
    rep(j, 4 * k) nxt_Q[n * j] = 0;

    vc<mint> p = rec(rec, n / 2, k * 2, nxt_Q);
    drep(j, 2 * k) {
      move(p.begin() + n * j, p.begin() + n * j + n / 2, f.begin());
      move(Q.begin() + 2 * n * j, Q.begin() + 2 * n * j + 2 * n, G.begin());
      fill(f.begin() + n / 2, f.end(), mint(0));
      transposed_ntt(f, 1);
      rep(i, n) {
        f[i] *= W[i];
        F[2 * i] = G[2 * i + 1] * f[i];
        F[2 * i + 1] = -G[2 * i] * f[i];
      }
      move(F.begin(), F.end(), p.begin() + 2 * n * j);
    }
    if (n <= k) {
      FFT_x(p, 0, 2 * k, true);
      doubling_y(p, 0, n, true);
    } else {
      doubling_y(p, 0, 2 * n, true);
      FFT_x(p, 0, k, true);
    }
    return p;
  };
  vc<mint> Q(4 * n);
  rep(i, n) Q[i] = -g[i];
  vc<mint> p = rec(rec, n, 1, Q);
  p.resize(n);
  reverse(rng(p));
  p.resize(n0);
  return p;
}


#line 2 "fps/power_projection.hpp"
// \sum_j[x^j]f^i を i=0,1,...,m
template <typename mint>
vc<mint> power_projection(vc<mint> f, vc<mint> wt, int m) {
  assert(sz(f) == sz(wt));
  if (f.empty()) {
    return vc<mint>(m + 1, mint(0));
  }
  if (f[0] != mint(0)) {
    mint c = f[0];
    f[0] = 0;
    vc<mint> A = power_projection(f, wt, m);
    rep(p, m + 1)
      A[p] *= fact_inv<mint>(p);
    vc<mint> B(m + 1);
    mint pow = 1;
    rep(q, m + 1) {
      B[q] = pow * fact_inv<mint>(q);
      pow *= c;
    }
    A = convolution<mint>(A, B);
    A.resize(m + 1);
    rep(i, m + 1)
      A[i] *= fact<mint>(i);
    return A;
  }
  
  int n = 1;
  while (n < sz(f))
    n *= 2;
  
  for (auto& x : f)
    x = -x;
  f.resize(n), wt.resize(n);
  reverse(rng(wt));
  vc<mint>& P = wt, &Q = f;
  P.resize(4 * n), Q.resize(4 * n);
  
  vc<mint> W(n);
  {
    // bit reverse order
    vc<int> btr(n);
    int log = topbit(n);
    rep(i, n) {
      btr[i] = (btr[i >> 1] >> 1) + ((i & 1) << (log - 1));
    }
    int t = mint::ntt_info().fi;
    mint r = mint::ntt_info().se;
    mint dw = r.inv().pow((1 << t) / (2 * n));
    mint w = 1;
    for (auto& i : btr) {
      W[i] = w;
      w *= dw;
    }
  }
  
  int k = 1;
  while (n > 1) {
    auto doubling_y = [&](vc<mint>& A, int l, int r) -> void {
      mint z = W[k / 2].inv();
      vc<mint> f(k);
      rep(i, l, r) {
        rep(j, k)
          f[j] = A[2 * n * j + i];
        ntt(f, 1);
        mint r = 1;
        rep(j, k) {
          f[j] *= r;
          r *= z;
        }
        ntt(f, 0);
        rep(j, k)
          A[2 * n * (k + j) + i] = f[j];
      }
    };
    
    auto FFT_x = [&](vc<mint>& A, int l, int r) -> void {
      vc<mint> f(2 * n);
      rep(j, l, r) {
        move(A.begin() + 2 * n * j, A.begin() + 2 * n * (j + 1), f.begin());
        ntt(f, 0);
        move(rng(f), A.begin() + 2 * n * j);
      }
    };
    
    if (n <= k) {
      doubling_y(P, 0, n);
      doubling_y(Q, 1, n);
      FFT_x(P, 0, 2 * k);
      FFT_x(Q, 0, 2 * k);
    } else {
      FFT_x(P, 0, k);
      FFT_x(Q, 0, k);
      doubling_y(P, 0, 2 * n);
      doubling_y(Q, 0, 2 * n);
    }
    rep(i, 2 * n * k)
      Q[i] += 1;
    rep(i, 2 * n * k, 4 * n * k)
      Q[i] -= 1;
    
    vc<mint> F(2 * n), G(2 * n), f(n), g(n);
    rep(j, 2 * k) {
      move(P.begin() + 2 * n * j, P.begin() + 2 * n * j + 2 * n, F.begin());
      move(Q.begin() + 2 * n * j, Q.begin() + 2 * n * j + 2 * n, G.begin());
      rep(i, n) {
        f[i] = W[i] * (F[2 * i] * G[2 * i + 1] - F[2 * i + 1] * G[2 * i]);
        g[i] = G[2 * i] * G[2 * i + 1];
      }
      ntt(f, 1), ntt(g, 1);
      fill(f.begin() + n / 2, f.end(), mint(0));
      fill(g.begin() + n / 2, g.end(), mint(0));
      move(rng(f), P.begin() + n * j);
      move(rng(g), Q.begin() + n * j);
    }
    fill(P.begin() + 2 * n * k, P.end(), mint(0));
    fill(Q.begin() + 2 * n * k, Q.end(), mint(0));
    rep(j, 2 * k)
      Q[n * j] = 0;
    
    n /= 2;
    k *= 2;
  }
  
  rep(i, k)
    P[i] = P[2 * i];
  P.resize(k);
  mint c = mint(1) / mint(k);
  for (auto& x : P)
    x *= c;
  ntt(P, 1);
  reverse(rng(P));
  P.resize(m + 1);
  return P;
}

#line 2 "fps/compositional_inverse.hpp"
// f^-1(x) を求める 
// f(x)に対して f(g(x))=g(f(x))=x を満たす g(x)を返す
// o(Nlog^2N)
template <typename mint>
vc<mint> compositional_inverse(vc<mint> f) {
  // 仮定：[x^1]f = c は 0 ではない.
  const int n = sz(f) - 1;
  if (n == -1)
    return {};
  assert(f[0] == mint(0));
  if (n == 0)
    return f;
  assert(f[1] != mint(0));
  // 定数項の係数 c を抽出し、f を正規化: f := f / c.
  mint c = f[1];
  mint ic = (c).inv();
  for (auto &x : f)
    x *= ic;
  vc<mint> wt(n + 1);
  wt[n] = 1;
  vc<mint> A = power_projection<mint>(f, wt, n);
  // Lagrange 反転公式により g(x) の係数を求める:
  // [x^{n-i}] g(x) = n * A[i] / i  (for i=1,...,n)
  vc<mint> g(n);
  rep(i, 1, n + 1)
    g[n - i] = mint(n) * A[i] * inv<mint>(i);
  fps gj=g ;
  g = pow_1(gj,-inv<mint>(n)) ;
  g.insert(g.begin(), 0);
  mint pow = 1;
  rep(i, sz(g)) {
    g[i] *= pow;
    pow *= ic;
  }
  return g;
}

// G->F(G), G->DF(G) を与える
// len(G) まで求める. len(F) まで求めてもいいよ.
// 計算量は合成とだいたい同等
template <typename mint, typename F1, typename F2>
vc<mint> compositional_inverse(const vc<mint>& F, F1 comp_F, F2 comp_DF) {
  const int N = sz(F);
  assert(N <= 0 || F[0] == mint(0));
  assert(N <= 1 || F[1] != mint(0));
  vc<mint> G(2);
  G[1] = mint(1) / F[1];
  while (sz(G) < N) {
    int n = sz(G);
    // G := G(x) - (F(G(x)) - x) / DF(G(x))
    vc<mint> G2 = comp_DF(G);
    G.resize(2 * n);
    vc<mint> G1 = comp_F(G);
    // G1 を下位 n 個分を捨て、後半部分を用いる
    G1 = {G1.begin() + n, G1.end()};
    G1 = fps_div(G1, G2);
    rep(i, n)
      G[n + i] -= G1[i];
  }
  G.resize(N);
  return G;
}

#line 2 "fps/coef_of_rational_fps.hpp"
template <typename mint>
mint coef_of_rational_fps_small(vector<mint> P, vector<mint> Q, ll N) {
  assert(sz(Q) <= 16);
  int m = sz(Q) - 1;
  assert(sz(P) == m);
  if (m == 0) return mint(0);
  vc<uint> Q32(m + 1);
  rep(i, m + 1) Q32[i] = (-Q[i]).val;
  using poly = vc<ull>;
  auto dfs = [&](auto& dfs, const ll N) -> poly {
    // x^N mod G
    if (N == 0) return {1};
    poly f = dfs(dfs, N / 2);
    poly g(sz(f) * 2 - 1 + (N & 1));
    rep(i, sz(f)) rep(j, sz(f)) { g[i + j + (N & 1)] += f[i] * f[j]; }
    rep(i, sz(g)) g[i] = mint(g[i]).val;
    drep(i, sz(g)) {
      g[i] = mint(g[i]).val;
      if (i >= m) rep(j, 1, sz(Q)) g[i - j] += Q32[j] * g[i];
    }
    g.resize(m);
    return g;
  };
  poly f = dfs(dfs, N);
  rep(i, m) { rep(j, 1, i + 1) P[i] -= Q[j] * P[i - j]; }
  ull res = 0;
  rep(i, m) res += f[i] * P[i].val;
  return res;
}

template <typename mint>
mint coef_of_rational_fps_ntt(vector<mint> P, vector<mint> Q, ll N) {
  int log = 0;
  while ((1 << log) < sz(Q)) ++log;
  int n = 1 << log;
  P.resize(2 * n), Q.resize(2 * n);
  ntt(P, 0), ntt(Q, 0);
  vc<int> btr(n);
  rep(i, n) { btr[i] = (btr[i >> 1] >> 1) + ((i & 1) << (log - 1)); }

  int t = mint::ntt_info().fi;
  mint r = mint::ntt_info().se;
  mint dw = r.inv().pow((1 << t) / (2 * n));

  vc<mint> S, T;
  while (N >= n) {
    mint w = inv<mint>(2);
    T.resize(n);
    rep(i, n) T[i] = Q[2 * i + 0] * Q[2 * i + 1];
    S.resize(n);
    if (N & 1) {
      for (auto& i: btr) {
        S[i] = (P[2 * i] * Q[2 * i + 1] - P[2 * i + 1] * Q[2 * i]) * w;
        w *= dw;
      }
    } else {
      rep(i, n) {
        S[i] = (P[2 * i] * Q[2 * i + 1] + P[2 * i + 1] * Q[2 * i]) * w;
      }
    }
    swap(P, S), swap(Q, T);
    N >>= 1;
    if (N < n) break;
    ntt_doubling(P);
    ntt_doubling(Q);
  }
  ntt(P, 1), ntt(Q, 1);return fps_div(P, Q)[N];
}

template <typename mint>
mint coef_of_rational_fps_convolution(vector<mint> P, vector<mint> Q, ll N) {
  P.resize(sz(Q) - 1);
  if (sz(P) == 0) return 0;
  while (N >= sz(P)) {
    vc<mint> Q1 = Q;
    rep(i, sz(Q1)) if (i & 1) Q1[i] = -Q1[i];
    P = convolution(P, Q1);
    Q = convolution(Q, Q1);
    rep(i, sz(Q1)) Q[i] = Q[2 * i];
    rep(i, sz(Q1) - 1) P[i] = P[2 * i | (N & 1)];
    P.resize(sz(Q1) - 1);
    Q.resize(sz(Q1));
    N /= 2;
  }
   return fps_div(P, Q)[N];
}

template <typename mint>
mint coef_of_rational_fps(vector<mint> P, vector<mint> Q, ll N) {
  assert(sz(P) < sz(Q) && Q[0] == mint(1));
  if (N == 0) return (P.empty() ? mint(0) : P[0]);
  int n = sz(Q);
  if (mint::ntt_info().fi != -1) {
    if (n <= 10) {
      return coef_of_rational_fps_small(P, Q, N);
    } else {
      return coef_of_rational_fps_ntt(P, Q, N);
    }
  }
  return (n <= 16 ? coef_of_rational_fps_small(P, Q, N)
                  : coef_of_rational_fps_convolution(P, Q, N));
}

// nth_sequence: k項間漸化式の初項と係数から、n 番目の項を計算する
// n は 0-index なのを注意 ! 
// 引数:
//    a  : 初項の列を表す vector<mint>
//         つまり、u(0), u(1), ..., u(k-1) が与えられる（漸化式の初期条件）
//    c  : 漸化式の係数の列を表す vector<mint>
//         A(n) = c[0]*A(n-1) + c[1]*A(n-2) + ... + c[k-1]*A(n-k)　（n ≥ k）
//    N  : 求めたい項の添字（u(N) を計算する）
template <typename mint>
mint nth_sequence(vc<mint> a, vc<mint> c, long long N) {
    if (N < (ll)a.size()) return a[N];
	vc<mint> g=c ;
	for(auto &&x:g) x=-x; g.insert(g.begin(),1) ;
	auto f=convolution(a, g) ;f.resize(sz(a)) ;
	return coef_of_rational_fps(f,g,N) ;
}

// 有理式の和を計算する。分割統治 O(Nlog^2N)。N は次数の和。
// pair<vc<mint>, vc<mint>> fi: a(x) , se: b(x) -> sum of a(x)/b(x) 
// 返り値は [F(x), G(x)] -> F(x)/G(x) 
template <typename mint>
pair<vc<mint>, vc<mint>> sum_of_rationals(vc<pair<vc<mint>, vc<mint>>> dat) {
  if (sz(dat) == 0) {
    vc<mint> f = {0}, g = {1};
    return {f, g};
  }
  using PM = pair<vc<mint>, vc<mint>>;
  auto add = [&](PM& a, PM& b) -> PM {
    int na = sz(a.fi) - 1, da = sz(a.se) - 1;
    int nb = sz(b.fi) - 1, db = sz(b.se) - 1;
    int n = max(na + db, da + nb);
    vc<mint> num(n + 1);
    {
      auto f = convolution(a.fi, b.se);
      rep(i, sz(f)) num[i] += f[i];
    }
    {
      auto f = convolution(a.se, b.fi);
      rep(i, sz(f)) num[i] += f[i];
    }
    auto den = convolution(a.se, b.se);
    return {num, den};
  };
  while (sz(dat) > 1) {
    int n = sz(dat);
    rep(i, 1, n, 2) { dat[i - 1] = add(dat[i - 1], dat[i]); }
    rep(i, ceil(n, 2)) dat[i] = dat[2 * i];
    dat.resize(ceil(n, 2));
  }
  return dat[0];
}

// sum wt[i]/(1-A[i]x) = G(x)/F(x) 
//  出力 [G(x), F(x)]
template <typename mint>
pair<vc<mint>, vc<mint>> sum_of_rationals_1(vc<mint> A, vc<mint> wt) {
  using poly = vc<mint>;
  if (!mint::can_ntt()) {
    vc<pair<poly, poly>> rationals;
    rep(i, sz(A)) rationals.eb(poly({wt[i]}), poly({mint(1), -A[i]}));
    return sum_of_rationals(rationals);
  }
  int n = 1;
  while (n < sz(A)) n *= 2;
  int k = topbit(n);
  vc<mint> F(n), G(n);
  vc<mint> nxt_F(n), nxt_G(n);
  rep(i, sz(A)) F[i] = -A[i], G[i] = wt[i];
  int D = 6;

  rep(d, k) {
    int b = 1 << d;
    if (d < D) {
      fill(rng(nxt_F), mint(0)), fill(rng(nxt_G), mint(0));
      for (int L = 0; L < n; L += 2 * b) {
        rep(i, b) rep(j, b) nxt_F[L + i + j] += F[L + i] * F[L + b + j];
        rep(i, b) rep(j, b) nxt_G[L + i + j] += F[L + i] * G[L + b + j];
        rep(i, b) rep(j, b) nxt_G[L + i + j] += F[L + b + i] * G[L + j];
        rep(i, b) nxt_F[L + b + i] += F[L + i] + F[L + b + i];
        rep(i, b) nxt_G[L + b + i] += G[L + i] + G[L + b + i];
      }
    }else if(d == D) {
      for (int L = 0; L < n; L += 2 * b) {
        poly f1 = {F.begin() + L, F.begin() + L + b};
        poly f2 = {F.begin() + L + b, F.begin() + L + 2 * b};
        poly g1 = {G.begin() + L, G.begin() + L + b};
        poly g2 = {G.begin() + L + b, G.begin() + L + 2 * b};
        f1.resize(2 * b), f2.resize(2 * b), g1.resize(2 * b), g2.resize(2 * b);
        ntt(f1, 0), ntt(f2, 0), ntt(g1, 0), ntt(g2, 0);
        rep(i, b) f1[i] += 1, f2[i] += 1;
        rep(i, b, 2 * b) f1[i] -= 1, f2[i] -= 1;
        rep(i, 2 * b) nxt_F[L + i] = f1[i] * f2[i] - 1;
        rep(i, 2 * b) nxt_G[L + i] = g1[i] * f2[i] + g2[i] * f1[i];
      }
    }
    else {
      for (int L = 0; L < n; L += 2 * b) {
        poly f1 = {F.begin() + L, F.begin() + L + b};
        poly f2 = {F.begin() + L + b, F.begin() + L + 2 * b};
        poly g1 = {G.begin() + L, G.begin() + L + b};
        poly g2 = {G.begin() + L + b, G.begin() + L + 2 * b};
        ntt_doubling(f1), ntt_doubling(f2), ntt_doubling(g1), ntt_doubling(g2);
        rep(i, b) f1[i] += 1, f2[i] += 1;
        rep(i, b, 2 * b) f1[i] -= 1, f2[i] -= 1;
        rep(i, 2 * b) nxt_F[L + i] = f1[i] * f2[i] - 1;
        rep(i, 2 * b) nxt_G[L + i] = g1[i] * f2[i] + g2[i] * f1[i];
      }
    }
    swap(F, nxt_F), swap(G, nxt_G);
  }
  if (k - 1 >= D) ntt(F, 1), ntt(G, 1);
  F.eb(1);
  reverse(rng(F)), reverse(rng(G));
  F.resize(sz(A) + 1);
  G.resize(sz(A));
  return {G, F};
}

// productPolyUnified: 与えられた数列 A, B, C と整数 N に対して、
// F(x)=∏_{i=0}^{n-1} (a_i + b_i*x)^(c_i) の 0 次から N 次までの係数展開（fps）を返す
fps productPolyUnified(const vector<int>& A, const vector<int>& B, const vector<int>& C, int N) {
    int n = A.size();
// 各項 (a_i + b_i*x)^(c_i) = a_i^(c_i) * (1 + (b_i/a_i)x)^(c_i)
// よって、定数因子は ∏ a_i^(c_i)、
    mint const_factor = mint(1);
    vector<int> d(n); // d[i] = b_i * inv(a_i) mod mod
    rep(i, n){
        const_factor *= mint(A[i]).pow(C[i]);
        mint invA = ~mint(A[i]);
        mint d_val = mint(B[i]) * invA;
        d[i] = d_val.val; 
    }
	vm A2, wt2 ; 
	rep(i, n){
		A2.pb(mint(d[i])) ;wt2.pb(mint(C[i])) ;
	}
    int deg = N + 2;
	auto rat=sum_of_rationals_1(A2,wt2) ;
    fps P = rat.first, Q = rat.second;
    fps invQ = Q.inv(deg);
    fps R_poly = P * invQ;
    R_poly.resize(deg);
    fps logFprime(N+1, mint(0));
    for (int k = 0; k <= N; k++){
        mint sign = (k % 2 == 0 ? mint(1) : mint(mod - 1));
        if(k+1 < (int)R_poly.size()) logFprime[k] = sign * R_poly[k+1];
        else logFprime[k] = mint(0);
    }
    fps logF = logFprime.integ();logF.resize(N+1);fps F = logF.exp(N+1);
    F.resize(N+1);
    for (int i = 0; i <= N; i++){
        F[i] *= const_factor;
    }
    return F;
}

// 目的の積の 0 次から N 次までの展開を O(M + N log N) 
// productSparse 関数
// //
// // 入力:
// //   a    : 各項の指数 a_i のリスト
// //   N    : 0 次から N 次までの展開を求める
// //   mode : 以下の4種類のモード
// //          mode == 0 :  Π (1 + x^(a_i))
// //                     → log(1+x^(a_i)) = x^(a_i) - x^(2a_i)/2 + x^(3a_i)/3 - ... 
// //                     ※各項の対数展開で係数は c(j)= (-1)^(j-1)/j
// //
// //          mode == 1 :  Π (1 - x^(a_i))^(-1)
// //                     → log((1-x^(a_i))^(-1)) = x^(a_i) + x^(2a_i)/2 + x^(3a_i)/3 + ...
// //                     ※各項の対数展開で係数は c(j)= 1/j
// //
// //          mode == 2 :  Π (1 - x^(a_i))
// //                     → log(1-x^(a_i)) = - x^(a_i) - x^(2a_i)/2 - x^(3a_i)/3 - ...
// //                     ※各項の対数展開で係数は c(j)= -1/j
// //
// //          mode == 3 :  Π (1 + x^(a_i))^(-1)
// //                     → log((1+x^(a_i))^(-1)) = - x^(a_i) + x^(2a_i)/2 - x^(3a_i)/3 + ...
// //                     ※各項の対数展開で係数は c(j)= -(-1)^(j-1)/j
// //
fps productSparse(const vector<int>& a, int N, int mode) {
    vector<int> cnt(N+1, 0); for (int ai : a)if (ai <= N) cnt[ai]++;
    fps L(N+1, mint(0)); invs(N+2) ;
    for (int n = 1; n <= N; n++) {
        if (cnt[n] == 0) continue;
        for (int j = 1; j * n <= N; j++) {
            mint coef = mint(cnt[n])*invs[j];
            if (mode == 0) { 
                if ((j & 1) == 0) coef = -coef;
            } else if (mode == 1) {
            } else if (mode == 2) {
                coef = -coef;
            } else if (mode == 3) {
                if ((j & 1) == 0) {
                } else {
                    coef = -coef;
                }
            }
            L[j*n] += coef;
        }
    }
    fps F = L.exp(N+1);F.resize(N+1); return F;
}

// マージテク：区間 [l, r) の多項式の積を返す再帰関数
// 多項式の総次数をMとしたときo(M(logM)^2) 
fps mergePolys(const vector<fps>& polys, int l, int r) {
    if(r - l == 1) return polys[l];
    int mid = (l + r) / 2;
    fps left = mergePolys(polys, l, mid);
    fps right = mergePolys(polys, mid, r);
    fps res = left * right;
    return res;
}

// (1-x^(a_i))/(1-x) の積を展開する関数
// 引数: 
//   a : 各 a_i のリスト（a_i は非負整数）
//   N : 0次から N次まで求める（N+1 項）
// ※ ここで m = a.size() が項数（もともとの (1-x^(a_i))/(1-x) の積）
fps polyfactor(const vector<int> &a, int N){
	int m=sz(a) ;fps f1=productSparse(a, N, 2) ;
	fps f2(N+1) ;rep(k, N+1) f2[k]=comb(m+k-1, k) ;
	fps res=f1*f2; res.resize(N+1) ;
	return res ;
}

using sfps = vector<pair<int,mint>> ;

int main() {










  return 0;
}



