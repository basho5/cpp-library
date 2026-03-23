#include <bits/stdc++.h>
using namespace std;
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
namespace atcoder {

namespace internal {

// @param n `0 <= n`
// @return minimum non-negative `x` s.t. `n <= 2**x`
int ceil_pow2(int n) {
    int x = 0;
    while ((1U << x) < (unsigned int)(n)) x++;
    return x;
}

// @param n `1 <= n`
// @return minimum non-negative `x` s.t. `(n & (1 << x)) != 0`
int bsf(unsigned int n) {
#ifdef _MSC_VER
    unsigned long index;
    _BitScanForward(&index, n);
    return index;
#else
    return __builtin_ctz(n);
#endif
}

}  // namespace internal

}  // namespace atcoder

namespace atcoder {

template <class S,
          S (*op)(S, S),
          S (*e)(),
          class F,
          S (*mapping)(F, S),
          F (*composition)(F, F),
          F (*id)()>
struct lazy_segtree {
  public:
    lazy_segtree() : lazy_segtree(0) {}
    lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}
    lazy_segtree(const std::vector<S>& v) : _n(int(v.size())) {
        log = internal::ceil_pow2(_n);
        size = 1 << log;
        d = std::vector<S>(2 * size, e());
        lz = std::vector<F>(size, id());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }

    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return e();

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push(r >> i);
        }

        S sml = e(), smr = e();
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }

        return op(sml, smr);
    }

    S all_prod() { return d[1]; }

    void apply(int p, F f) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = mapping(f, d[p]);
        for (int i = 1; i <= log; i++) update(p >> i);
    }
    void apply(int l, int r, F f) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return;

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }

        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

    template <bool (*g)(S)> int max_right(int l) {
        return max_right(l, [](S x) { return g(x); });
    }
    template <class G> int max_right(int l, G g) {
        assert(0 <= l && l <= _n);
        assert(g(e()));
        if (l == _n) return _n;
        l += size;
        for (int i = log; i >= 1; i--) push(l >> i);
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!g(op(sm, d[l]))) {
                while (l < size) {
                    push(l);
                    l = (2 * l);
                    if (g(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <bool (*g)(S)> int min_left(int r) {
        return min_left(r, [](S x) { return g(x); });
    }
    template <class G> int min_left(int r, G g) {
        assert(0 <= r && r <= _n);
        assert(g(e()));
        if (r == 0) return 0;
        r += size;
        for (int i = log; i >= 1; i--) push((r - 1) >> i);
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!g(op(d[r], sm))) {
                while (r < size) {
                    push(r);
                    r = (2 * r + 1);
                    if (g(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

  private:
    int _n, size, log;
    std::vector<S> d;
    std::vector<F> lz;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, F f) {
        d[k] = mapping(f, d[k]);
        if (k < size) lz[k] = composition(f, lz[k]);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }
};

}  // namespace atcoder
using S= ll ;
using F=ll; 
const F ID = LINF ;
S op(S a, S b){return a+b;}
S e(){return LINF;}
S mp(F f, S x){
	if(f==ID) return x ; 
	return f ;
}
F cmp(F f, F g){
	if(f==ID) return g ;
	return f ;
}
F id(){return ID ;}


int main() {
	int n,q ;cin>>n>>q ;
	vc<S> a(n,(1LL<<31)-1) ;
	atcoder::lazy_segtree<S,op,e,F, mp,cmp,id> seg(a) ;
	while(q--){
		int op;cin>>op; 
		if(op==0){
			int s,t; ll x;cin>>s>>t>>x; 
			seg.apply(s, t+1, x) ;
		}
		else {
			int s ;cin>>s; 
			auto it=seg.get(s) ;
			cout <<it <<endl;
		}
	}
  return 0;
}

