#include <algorithm>
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
#define dame { puts("-1"); return;}
#define yes { puts("Yes"); return;}
#define no { puts("No"); return;}
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
template <typename T> 
void chmin(T &a , T b) {a = min(a, b) ;}

//knapsack_case
//w, v はrepp(i, n)で受け取る

//O(nW) 
//n <= 100 , W <=10^5, vi <= 10^9 
//vi が大きい場合
ll knapsack(vl w, vl v, ll W){
	int n = w.size()-1 ; 
	vvl dp(n + 1, vl (W +1, 0)) ; 
	repp(i, n)rep(j, W + 1){
		if(j - w[i] >= 0){
			dp[i][j] = max(dp[i-1][j], dp[i-1][j-w[i]] + v[i]) ;
		}
		else {
			dp[i][j] = dp[i-1][j] ;
		}
	}
	return dp[n][W] ;
}

//O(n * vi)
//n <= 200 , vi <= 1000 
//wiが大きい場合
ll knapsack1(vl w, vl v, ll W) {
	int n = w.size()-1 ;
    vvl dp(n + 1, vl(100005, (1ll << 60)));
    dp[0][0] = 0;
    repp(i, n){
        rep(j, 100001){
            if (j < v[i]) 
                dp[i][j] = dp[i - 1][j];
            else 
                dp[i][j] = min(dp[i - 1][j], dp[i - 1][j - v[i]] + w[i]);
        }
    }
    ll res = 0 ;
    rep(i, 100001){
        if (dp[n][i] <= W) 
            res = i;
    }
    return res;
}

//O(2^n/2 * n)
//n <= 40 程度つまりbitが使える場合
//これはrep(i, n) で受け取る
ll knapsack2(const vl& weight, const vl& value, ll W) {
    int n = weight.size()-1;
	vl w(n) , v(n) ;
	rep(i, n) {w[i] = weight[i+1];v[i] = value[i+1];}
    int n2 = n / 2;
    vc<LP> ps;
    
    rep(i, 1 << n2) {
        ll sw = 0, sv = 0;
        rep(j, n2) {
            if (i >> j & 1) {
                sw += w[j];
                sv += v[j];
            }
        }
        ps.pb(LP(sw, sv));
    }

    sort(rng(ps)) ;
    int m = 1;
    for (int i = 1; i < (1 << n2); i++) {
        if (ps[m - 1].se < ps[i].se) ps[m++] = ps[i];
    }

    ll res = 0;
    rep(i, 1 << (n - n2)) {
        ll sw = 0, sv = 0;
        rep(j, n - n2) {
            if (i >> j & 1) {
                sw += w[n2 + j];
                sv += v[n2 + j];
            }
        }
        if (sw <= W) {
            ll tv = (lower_bound(ps.begin(), ps.begin() + m, LP(W - sw, LINF)) - 1)->se;
            res = max(res, sv + tv);
        }
    }
    
    return res;
}

//O(n*W)
//個数なしナップサック問題
//これはrep(i, n) で受け取る
ll knapsack_free(vl w, vl v, ll W) {
	int n = w.size()-1 ;
	vl dp(W+1) ;
	rep(i ,n){
		srep(j, w[i], W+1){
			dp[j] = max(dp[j], dp[j-w[i]] + v[i]) ;
		}
	}
    return dp[W];
}


int main() {
	ll n, W ;cin>> n >>W ;
	vl w(n+1) , v(n+1) ;
	repp(i, n) cin >> v[i] >> w[i] ;
	ll mw = 0 , mv = 0 ;
	repp(i, n) {
		mw = max(mw, w[i]) ;
		mv = max(mv, v[i]) ;
	}
	if(n <= 30){
		cout << knapsack2(w, v, W) <<endl;
		return  0 ;
	}
	else if(mw <= 1000){
		cout << knapsack(w, v, W) <<endl;
		return 0 ;
	}
	else if(mv <= 1000){
		cout << knapsack1(w, v, W) <<endl;
		return 0 ;
	}





    return 0 ;
}
