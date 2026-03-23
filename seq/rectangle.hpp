// ヒストグラムの最大長方形問題
ll largest_rectangle(vl a){
	int n = sz(a) ;
	ll res = 0 ;
	vl l(n) , r(n) ;
	{
		stack<int> st; 
		rep(i, n){
			while(sz(st)&&a[st.top()]>=a[i]) st.pop() ;
			if(sz(st) == 0) l[i] = i+1 ; 
			else l[i]=i-st.top() ;
			st.push(i) ;
		}
	};
	{
		stack<int> st; 
		drep(i, n){
			while(sz(st)&&a[st.top()]>a[i]) st.pop() ;
			if(sz(st) == 0) r[i]=n-i; 
			else r[i]=st.top()-i;
			st.push(i) ;
		}
	};
	rep(i, n) maxs(res, (ll)a[i]*(r[i]+l[i]-1)) ;
	return res ;
} ;
