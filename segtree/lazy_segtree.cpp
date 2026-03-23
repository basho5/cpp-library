#include <bits/stdc++.h>
#include <atcoder/all>
#include <climits>
using namespace std;
using namespace atcoder;
#define rep(i,n) for (int i = 0 ; i < n ; ++i )
#define repp(i,n) for (int i = 1 ; i <= n ; ++i )
using ll = long long;
using P = pair<int , int>;

////RSQ and RAQ 
// struct S{ll value;int size;} ;
// using F = ll ;
// S op(S a, S b){return {a.value + b.value, a.size + b.size};} ;
// S e() {return {0, 0};} ;
// S mp(F f, S x) {return {x.value+f*x.size, x.size};};
// F cmp(F f, F g){return f + g;};
// F id(){return 0;};
// ////////////////////////////////////////////////

////RMQ and RAQ 
// using S = ll ;
// using F = ll ;
// const S INF = 8e18 ;
//
// S op(S a, S b){return min(a, b);}
// S e(){return INF ;} 
// S mp(F f, S x ){return f + x;} 
// F cmp(F f, F g){return f + g;}
// F id(){return 0;}
////////////////////////////////////////////////////

// ////RMQ and RUQ
// using S = ll ;
// using F = ll ;
// const S INF = (INT_MAX) ;
// const F ID = (INT_MAX) ;
//
// S op(S a, S b){return min(a, b);}
// S e(){return INF;}
// S mp(F f, S a){return (f == ID ? a:f);}
// F cmp(F f, F g){return (f == ID ? g:f);}
// F id(){return ID ;}
///////////////////////////////////////////////////////

//RMQ and RAQ 
using S = ll;
using F = ll;
const S INF = (1ll << 60) ;
const F ID = (1ll << 60);
S op(S a , S b){return min(a, b);}
S e(){return INF ;}
F mp(F f, S a){return (f + a);}
F cmp(F f, F g){return f + g; }
F id(){return ID ;}

int main(){
    int n , q;
	cin >> n  >>q ;
	vector<S> init(n, INF) ;
	lazy_segtree<S, op, e, F, mp, cmp, id> seg(init) ;
	rep(i, q){
		int cm ;
		cin >> cm ;
		if(cm == 0){
			int s, t, u;
			cin >> s >>t >> u ;
			seg.apply(s, t + 1, u) ;
		}
		else{
			int s, t ;
			cin>> s>>t ;
			cout << seg.prod(s, t + 1)<<endl;
		}
	}
    return 0;
}

