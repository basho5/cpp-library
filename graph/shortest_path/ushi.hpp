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
template <typename T> 
void chmax(T &a , T b) {a = max(a, b) ;}
struct Edge {int from; int to; ll cost ;} ;
using Graph = vector<vector<Edge>> ;
//O(V+ E)
//二部グラフ判定、白と黒に塗り分けることができるか(dfs,再帰関数) 頂点vをc(色)で塗る
bool dfs(int v, int c, vector<vector<int>> graph, vector<int> &color){
   color[v]= c ;
   rep(i, graph[v].size()){
	   if(color[graph[v][i]] == c) return false ;
	   if(color[graph[v][i]] == 0 && !dfs(graph[v][i], 1 - c, graph, color)){
		   return false ;
	   }
   }
   return true ;
}

bool is_bipertite(vector<vector<int>> graph, vector<int> color){
	rep(i, graph.size()){
		if(color[i] == 0){
			if(!dfs(i, 1, graph, color)){
				return false ;
			}
		}
	}
	return true ;
}


//O(V + E) 
//重みなしグラフの最短距離
void bfs(const Graph &graph, vector<ll> dist , int s){
	fill(dist.begin(), dist.end(), -1);
	queue<int> q ;
	dist[s] = 0 ;
	q.push(s) ;
	while(!q.empty()){
		auto from = q.front();q.pop();
		for(const auto &e:graph[from]){
			if(dist[e.to] != -1) continue;
			dist[e.to] = dist[e.from] + 1 ;
			q.push(e.to) ;
		}
	}
   return ;
}

//重みつきグラフの最短距離(負の重みもあり)
//O(VE)
void bellmanford(const vector<Edge> &edges, vector<ll> &dist, int s){
	fill(dist.begin(), dist.end(), INF);
    dist[s] = 0 ;
	for(int i = 0; i < dist.size() ;i ++){
	  bool updated = false ;
	  for(const auto &e:edges){
		  if(dist[e.from] ==INF ) continue ;
		  const ll d = dist[e.from] + e.cost ;
		  if(d < dist[e.to]){
			  dist[e.to] = d ;
			  updated = true ;
		  }
	  }
	  if(!updated){
		  break ;
	  }

	}
	return ;
}

//O(VE)
//bellmanfordをして、負のサイクルも検出する
bool bellmanford_negative_cycle(const vector<Edge> &edges, vector<ll> &dist, int s){
	fill(dist.begin(), dist.end(), INF);
    dist[s] = 0 ;
	for(int i = 0; i < dist.size() ;i ++){
	  bool updated = false ;
	  for(const auto &e:edges){
		  if(dist[e.from] ==INF ) continue ;
		  const ll d = dist[e.from] + e.cost ;
		  if(d < dist[e.to]){
			  dist[e.to] = d ;
			  updated = true ;
		  }
	  }
	  if(!updated){
		  return false ;
	  }
	}
	return true ;
}

//O(VE)
//bellmafordをして,
//負のサイクルを検出し、最短距離のpathも返す
bool bellmanford_get_path(const vector<Edge> &edges, vector<ll> &dist, int s, int g, vector<int> &path){

	fill(dist.begin(), dist.end(), INF) ;

	 dist[s] = 0 ;
   // pathの配列を用意
    vector<int> p(dist.size(), -1);

	bool updated = false ;

   for(int i = 0 ; i < dist.size(); i++){  
	   updated = false ;
	   for(const auto &edge : edges){
          if(dist[edge.from] == INF) continue;

		  const ll d = dist[edge.from] + edge.cost ;
		  if(d < dist[edge.to]){
			  updated = true ;
			  p[edge.to] = edge.from ;
			  dist[edge.to] = d ;
		  }
	   }
	   if(!updated){
		   break ;
	   }
	   if(updated){
		   for(int i = 0 ; i < dist.size(); i++){
			   for(const auto &edge: edges){
				   if(dist[edge.from] == INF) continue ;

				   const ll d = dist[edge.from] + edge.cost ;
				   if(d < dist[edge.to]){
					   dist[edge.to] = -INF ;
				   }
			   }
		   }
	   }

   }
   if((dist[g] != INF) && (dist[g] != -INF)){
	   for(int i = g; i != -1; i = p[i]){
		   path.push_back(i) ;
	   }
	   reverse(path.begin(), path.end());
   }
   return updated ;
 	 
}

//O((E+V)logV)
//非負整数の重みのグラフの最短距離を返す
//Edgeはto,from,costだけどfromはいらないけど入力する
void dijkstra(const Graph &graph, vector<ll> &dist ,int s){
	fill(dist.begin(), dist.end(), INF) ;
    priority_queue<LP, vector<LP> , greater<LP>> q ;
    dist[s] = 0 ;
	q.push(LP(0, s)) ;
	while(!q.empty()){
		auto [dis, from] = q.top();q.pop() ;
        if(dist[from] < dis) continue ;
		for(const auto &e:graph[from]){
		   const ll d = dist[from] + e.cost ;
		   if(d < dist[e.to]){
			   dist[e.to] = d ;
			   q.push(LP(dist[e.to], e.to));
		   }
		}
	}
	return ;
}

//O((E+V)logV)
//ダイクストラをして、pathも返す
vector<int> dijkstra_get_path(const Graph &graph, vector<ll> &dist, int s, int g){
     vector<int> path;
	 vector<int> p(dist.size(), -1) ;
	 dist[s] = 0 ;
	 priority_queue<LP, vector<LP> , greater<LP>> q ;
	 q.push(LP(0, s)) ;
	 while(!q.empty()){
		 auto [dis, from] = q.top();q.pop() ;
		 if(dis > dist[from]) continue ;
		 for(const auto &e:graph[from]){
			 const ll d = dist[from] + e.cost ;
			 if(d < dist[e.to]) {
				 dist[e.to] = d ;
				 q.push(LP(dist[e.to], e.to));
				 p[e.to] = from ;
			 }
		 }
	 }
	 if(dist[g] != INF){
		 for(int i = g; i != -1; i = p[i]) {
			 path.push_back(i);
		 }
	 }
	 reverse(path.begin(), path.end()) ;

   return path ;
}

//d_i - d_j <= w_ij の制約下でd_t - d_s の最大値を求めるもの
//d_i - d_j <= w_ij の時にjからiにコストw_ijの辺を張る
//d_i <= d_i+1などの時はi+1からiにコスト0の辺を張る
//負閉路があれば存在しない, 初めdistをINFにしておいてINFが帰ってきたらいくらでも大きくできる
ll ushi(const Graph& graph){
	vl dist(sz(graph)) ;
	ll res ;
	dijkstra(graph, dist, 0) ;
	return dist[sz(graph)-1] ;
}

ll ushi_negative(const vector<Edge>&edges, vl dist){
	if(bellmanford_negative_cycle(edges, dist,0)){
		return -1 ;
	}
	bellmanford(edges, dist, 0) ;
	return dist[sz(dist)-1] ;
}


int main() {
	int n, md ,ml ;cin >> n >> md >> ml;
	vc<Edge> edges ;
	vl dist(n) ;
	rep(i, md){
		int a, b,c;cin >> a >> b >> c ;
		--a,--b;edges.pb(Edge{a, b, c}) ;
	}
	rep(i,ml){
		int a, b,c;cin >> a >> b >> c ;
		--a,--b;edges.pb(Edge{b, a, -c}) ;
	}
	rep(i, n-1){
		edges.pb(Edge{i+1, i, 0});
	}
	ll ans = ushi_negative(edges, dist) ;
	if(ans == INF) cout << -2 << endl;
	else cout << ans <<endl;
	


  return 0;
}

