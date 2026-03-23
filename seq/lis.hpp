// LIS (trueのとき広義単調増加)
template <typename T> 
ll LIS(vector<T> a, bool A=false){
	int n=sz(a) ;
	vc<T> dp(n, infty<T>) ;
	rep(i, n){
		if(A){
			int k=upper_bound(rng(dp),a[i])-dp.begin() ;
			dp[k]=a[i] ;
		}else{
			int k=lower_bound(rng(dp),a[i])-dp.begin() ;
			dp[k]=a[i] ;
		}
	}
	ll res=0 ;rep(i, n) if(dp[i]!=infty<T>) maxs(res,i+1) ;
	return res ;
}


// LIS (trueのとき広義単調増加)
template <typename T> 
vc<T> LIS_path(vector<T> a, bool A=false){
	int n=sz(a) ;
	vc<T> dp(n, infty<T>) ;
	vi id(n, -1), pre(n) ;
	rep(i, n){
		if(A){
			int k=upper_bound(rng(dp),a[i])-dp.begin() ;
			dp[k]=a[i] ;
			id[k]=i ; pre[i]=(k?id[k-1]:-1) ;
		}else{
			int k=lower_bound(rng(dp),a[i])-dp.begin() ;
			dp[k]=a[i] ;
			id[k]=i ; pre[i]=(k?id[k-1]:-1) ;
		}
	}
	int res=0 ; rep(i, n) if(id[i]!=-1) maxs(res,i) ;
	int j=id[res]; vc<T> p ; 
	while(j!=-1){
		p.pb(a[j]) ; j = pre[j] ;
	}
	reverse(rng(p)) ;
	return p ;
}


// 二次元LIS (trueのとき広義単調増加)
// [a, b] in [c, d] (a < b, c< d )
template <typename T> 
ll LIS2D(vc<pair<T,T>> a , bool A=false){
	int n=sz(a) ;sort(rng(a)) ;
	vc<T> dp(n, infty<T>) ;
	rep(i, n){
		if(A){
			int k=upper_bound(rng(dp),a[i].se)-dp.begin() ;
			dp[k]=a[i].se; 
		}else{
			int k=lower_bound(rng(dp),a[i].se)-dp.begin() ;
			dp[k]=a[i].se; 
		}
	}
	ll res=0 ;rep(i, n) if(dp[i]!=infty<T>) maxs(res,i+1) ;
	return res ;
}

// 二次元LIS復元(trueのとき広義単調増加) 
// [a, b] in [c, d] (a < b, c< d )
template <typename T> 
vc<pair<T,T>> LIS2D_path(vc<pair<T,T>> a, bool A=false){
	int n=sz(a) ;sort(rng(a)) ;
	vc<T> dp(n, infty<T>) ;
	vi id(n, -1) ,pre(n) ;
	rep(i, n){
		if(A){
			int k=upper_bound(rng(dp),a[i].se)-dp.begin() ;
			dp[k]=a[i].se; 
			id[k]=i ; pre[i]=(k?id[k-1]:-1);
		}else{
			int k=lower_bound(rng(dp),a[i].se)-dp.begin() ;
			dp[k]=a[i].se; 
			id[k]=i ; pre[i]=(k?id[k-1]:-1);
		}
	}
	int m=0 ;rep(i, n) if(id[i]!=-1) maxs(m, i) ;
	vc<pair<T,T>> res ; int j=id[m] ;
	while(j!=-1){
		res.eb(a[j]) ;j = pre[j] ;
	}
	reverse(rng(res)) ;return res ;
}
