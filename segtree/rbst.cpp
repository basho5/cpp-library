#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define repp(i,n) for(int i = 1; i <= (n); ++i)
#define drep(i,n) for(int i = (n)-1; i >= 0; --i)
#define srep(i,s,t) for (int i = s; i < (t); ++i)
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
using namespace std;
template<class T> using vv = vc<vc<T>>;
template<class T> using PQ = priority_queue<T,vc<T>,greater<T>>;
using uint = unsigned; using ull = unsigned long long;
using vi = vc<int>; using vvi = vv<int>; using vvvi = vv<vi>;
using ll = long long; using vl = vc<ll>; using vvl = vv<ll>; using vvvl = vv<vl>;
using P = pair<int,int>; using vp = vc<P>; using vvp = vv<P>; using LP = pair<ll,ll>;
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
const double eps = 1e-10;
const ll LINF = 1001002003004005006ll;
const int INF = 1001001001;
#define dame { puts("-1"); return 0 ;}
#define yes { puts("Yes"); return 0 ;}
#define no { puts("No"); return 0 ;}
#define rtn(x) { cout<<(x)<<endl;} // flush!
#define yn {puts("Yes");}else{puts("No");}
ll c2(ll n) { return n*(n-1)>>1;}

// Mod int
uint mod = 998244353;//*/
uint md(ll x) { x%=mod; return x<0?x+mod:x;}
ll md(ll x, ll m) { x%=m; return x<0?x+m:x;}
struct mint {
  uint x;
  mint(): x(0) {}
  mint(ll x):x(md(x)) {}
  mint operator-() const { return mint(0) - *this;}
  mint operator~() const { return mint(1) / *this;}
  mint& operator+=(const mint& a) { if((x+=a.x)>=mod) x-=mod; return *this;}
  mint& operator-=(const mint& a) { if((x+=mod-a.x)>=mod) x-=mod; return *this;}
  mint& operator*=(const mint& a) { x=(ull)x*a.x%mod; return *this;}
  mint& operator/=(const mint& a) { x=(ull)x*a.pow(mod-2).x%mod; return *this;}
  mint operator+(const mint& a) const { return mint(*this) += a;}
  mint operator-(const mint& a) const { return mint(*this) -= a;}
  mint operator*(const mint& a) const { return mint(*this) *= a;}
  mint operator/(const mint& a) const { return mint(*this) /= a;}
  mint pow(ll t) const {
    mint res = 1; for (mint p=x;t;p*=p,t>>=1) if (t&1) res *= p; return res;
  }
  mint ppow(ll t) const { int p=mod-1; return pow((t%p+p)%p);}
  bool operator<(const mint& a) const { return x < a.x;}
  bool operator==(const mint& a) const { return x == a.x;}
  bool operator!=(const mint& a) const { return x != a.x;}
};
mint ex(mint x, ll t) { return x.pow(t);}
istream& operator>>(istream&i,mint&a) {i>>a.x;return i;}
//*
ostream& operator<<(ostream&o,const mint&a) {o<<a.x;return o;}
/*/
ostream& operator<<(ostream&o, const mint&x) {
  int a = x.x, b = 1;
  rep(s,2)rep1(i,1000) {
    int y = ((s?-x:x)*i).x; if (abs(a)+b > y+i) a = s?-y:y, b = i;
  }
  o<<a; if (b != 1) o<<'/'<<b; return o;
}//*/
using vm = vector<mint>;
using vvm = vector<vm>;
struct modinv {
  int n; vm d;
  modinv(): n(2), d({0,1}) {}
  mint operator()(int i) { while (n <= i) d.pb(-d[mod%n]*(mod/n)), ++n; return d[i];}
  mint operator[](int i) const { return d[i];}
} invs;
struct modfact {
  int n; vm d;
  modfact(): n(2), d({1,1}) {}
  mint operator()(int i) { while (n <= i) d.pb(d.back()*n), ++n; return d[i];}
  mint operator[](int i) const { return d[i];}
} facs;
struct modfactinv {
  int n; vm d;
  modfactinv(): n(2), d({1,1}) {}
  mint operator()(int i) { while (n <= i) d.pb(d.back()*invs(n)), ++n; return d[i];}
  mint operator[](int i) const { return d[i];}
} ifacs;
mint comb(int a, int b) {
  if (a < b || b < 0) return 0;
  return facs(a)*ifacs(b)*ifacs(a-b);
}
struct modpow {
  mint x; int n; vm d;
  modpow(mint x=2): x(x), n(1), d(1,1) {}
  mint operator()(int i) { while (n <= i) d.pb(d.back()*x), ++n; return d[i];}
  mint operator[](int i) const { return d[i];}
} two(2);//, owt(invs(2));
//
// ========== RBSTBase ==========
template <typename Node>
struct RBSTBase {
  using Ptr = Node*;
  template <typename... Args>
  inline Ptr my_new(Args&&... args) {
    return new Node(std::forward<Args>(args)...);
  }
  inline void my_del(Ptr t) { delete t; }
  inline Ptr make_tree() const { return nullptr; }

  int size(Ptr t) const { return count(t); }

  Ptr merge(Ptr l, Ptr r) {
    if (!l || !r) return l ? l : r;
    if (int((rngs() * (l->cnt + r->cnt)) >> 32) < l->cnt) {
      push(l);
      l->r = merge(l->r, r);
      return update(l);
    } else {
      push(r);
      r->l = merge(l, r->l);
      return update(r);
    }
  }

  pair<Ptr, Ptr> split(Ptr t, int k) {
    if (!t) return {nullptr, nullptr};
    push(t);
    if (k <= count(t->l)) {
      auto s = split(t->l, k);
      t->l = s.second;
      return {s.first, update(t)};
    } else {
      auto s = split(t->r, k - count(t->l) - 1);
      t->r = s.first;
      return {update(t), s.second};
    }
  }

  Ptr build(int l, int r, const vector<decltype(Node::key)> &v) {
    if (l + 1 == r) return my_new(v[l]);
    int m = (l + r) >> 1;
    Ptr pm = my_new(v[m]);
    if (l < m) pm->l = build(l, m, v);
    if (m + 1 < r) pm->r = build(m + 1, r, v);
    return update(pm);
  }

  Ptr build(const vector<decltype(Node::key)> &v) {
    return build(0, (int)v.size(), v);
  }

  template <typename... Args>
  void insert(Ptr &t, int k, const Args &... args) {
    auto x = split(t, k);
    t = merge(merge(x.first, my_new(args...)), x.second);
  }

  void erase(Ptr &t, int k) {
    auto x = split(t, k);
    auto y = split(x.second, 1);
    my_del(y.first);
    t = merge(x.first, y.second);
  }

protected:
  static uint64_t rngs() {
    static uint64_t x_ = 88172645463325252ULL;
    x_ ^= x_ << 7; 
    x_ ^= x_ >> 9;
    return x_ & 0xFFFFFFFFull;
  }

  inline int count(const Ptr t) const { return t ? t->cnt : 0; }

  virtual void push(Ptr) = 0;
  virtual Ptr update(Ptr) = 0;
};

// ========== LazyReversibleRBSTNode (S,F) ==========
template <typename S, typename F>
struct LazyReversibleRBSTNode {
  typename RBSTBase<LazyReversibleRBSTNode>::Ptr l, r;
  S key, sum;
  F lazy;
  int cnt;
  bool rev;
  
  LazyReversibleRBSTNode(const S &s = S(), const F &f = F())
      : l(nullptr), r(nullptr), key(s), sum(s), lazy(f), cnt(1), rev(false) {}
};

// ========== LazyReversibleRBST (S,F,op,mapping,composition,ts) ==========
template <typename S, typename F,
          S (*op)(S, S),           // 区間合成
          S (*mapping)(S, F),      // 値に F を適用
          F (*composition)(F, F),  // F の合成
          S (*ts)(S)>              // 反転時に区間合成結果へ作用
struct LazyReversibleRBST
  : public RBSTBase<LazyReversibleRBSTNode<S, F>> {

  using Node = LazyReversibleRBSTNode<S, F>;
  using base = RBSTBase<Node>;
  using typename base::Ptr;

  LazyReversibleRBST() = default;

  void toggle(Ptr t) {
    if (!t) return;
    swap(t->l, t->r);
    t->sum = ts(t->sum);
    t->rev ^= true;
  }

  S fold(Ptr &t, int a, int b) {
    auto x = base::split(t, a);
    auto y = base::split(x.second, b - a);
    S ret = sum(y.first);
    t = base::merge(x.first, base::merge(y.first, y.second));
    return ret;
  }

  void reverse(Ptr &t, int a, int b) {
    auto x = base::split(t, a);
    auto y = base::split(x.second, b - a);
    toggle(y.first);
    t = base::merge(x.first, base::merge(y.first, y.second));
  }

  void apply(Ptr &t, int a, int b, const F &f) {
    auto x = base::split(t, a);
    auto y = base::split(x.second, b - a);
    propagate(y.first, f);
    t = base::merge(x.first, base::merge(y.first, y.second));
  }

protected:
  inline S sum(const Ptr t) const { return t ? t->sum : S(); }

  Ptr update(Ptr t) override {
    push(t);
    t->cnt = 1;
    t->sum = t->key;
    if (t->l) {
      t->cnt += t->l->cnt;
      t->sum = op(t->l->sum, t->sum);
    }
    if (t->r) {
      t->cnt += t->r->cnt;
      t->sum = op(t->sum, t->r->sum);
    }
    return t;
  }

  void push(Ptr t) override {
    if (!t) return;
    if (t->rev) {
      if (t->l) toggle(t->l);
      if (t->r) toggle(t->r);
      t->rev = false;
    }
    // lazy != F() の判定は「恒等更新」と比較
    if (t->lazy != F()) {
      if (t->l) propagate(t->l, t->lazy);
      if (t->r) propagate(t->r, t->lazy);
      t->lazy = F(); // 恒等更新に戻す
    }
  }

  void propagate(Ptr t, const F &x) {
    t->lazy = composition(t->lazy, x);
    t->key = mapping(t->key, x);
    t->sum = mapping(t->sum, x);
  }
};

// ========== 統合ラッパー：rbst (S,F,op,mapping,composition,ts) ==========
template <typename S, typename F,
          S (*op)(S, S),
          S (*mapping)(F, S),
          F (*composition)(F, F),
          S (*ts)(S)>
struct rbst : public LazyReversibleRBST<S, F, op, mapping, composition, ts> {
  using Node = LazyReversibleRBSTNode<S, F>;
  using Base = LazyReversibleRBST<S, F, op, mapping, composition, ts>;
  using typename Base::Ptr;
  
  // 木全体の根
  Ptr root;

  rbst() : root(nullptr) {}

  // 木のサイズを返す
  int size() const { return Base::size(root); }

  // pos 番目に val を挿入する（0-indexed）
  void insert(int pos, const S &val) {
    Base::insert(root, pos, val);
  }

  // pos 番目の要素を削除する（0-indexed）
  void erase(int pos) {
    Base::erase(root, pos);
  }

  // 区間 [l, r) の反転を行う
  void reverse(int l, int r) {
    Base::reverse(root, l, r);
  }

  // 区間 [l, r) に対して lazy 値 f を適用する
  void apply(int l, int r, const F &f) {
    Base::apply(root, l, r, f);
  }

  // 区間 [l, r) の値を合成して返す
  S fold(int l, int r) {
    return Base::fold(root, l, r);
  }

  // ベクターから木を構築する
  void build(const vector<S> &v) {
    root = Base::build(v);
  }
  
   // ★ get(int p): p 番目(0-indexed) の要素を取得
  S get(int p) {
    // 1) [0, p) と [p, ...) に split
    auto x = Base::split(root, p);
    // 2) [p, p+1) と [p+1, ...) に split
    auto y = Base::split(x.second, 1);
    // y.first が要素1個の木
    S val = y.first->key; // ここで欲しい値を取得

    // 3) merge で木を元に戻す
    //    x.first : [0, p)
    //    y.first : [p, p+1) ← 1要素
    //    y.second: [p+1, end)
    root = Base::merge(x.first, Base::merge(y.first, y.second));

    return val;
  }
	 
};

using S= ll;
using F=ll ; 
S op(S a, S b){return a+b ;}
S mp(F f , S x){return x;}
F cmp(F f, F g){return 0;}
S ts(ll x){return x ;}

int main() {
	int n ;cin>>n ; 
	vl p(n) ;cin>>p ;
	p--;
	vl a={};
	rbst<S,F,op,mp,cmp,ts> rb ;
	rep(i, n){
		int pi=p[i] ;
		ll v=i+1 ; 
		rb.insert(pi, v) ;
	}
	rep(i, n){
		cout <<rb.get(i) <<endl;
	}


    return 0;
}
