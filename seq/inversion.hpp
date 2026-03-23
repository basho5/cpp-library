vector<int> compress(vector<int> a){
	int n = a.size();
	vector<int> res = a ;
	sort(a.begin(), a.end()) ;
	a.erase(unique(a.begin(), a.end()), a.end());
    rep(i, n){
		int r = lower_bound(a.begin(), a.end(), res[i]) - a.begin();
	  res[i] = r ;
	}
	return  res ;
}

template <typename T> 
ll tentou(const vector<T> &s){
	vector<T> inver = compress(s) ;
	fenwick_tree<T> f(inver.size());
	ll res = 0 ;
	for(int i = 0 ; i < inver.size() ; i ++){
		res += i - f.sum(0, inver[i]) ;
		f.add(inver[i], 1) ;
	}
	return res ;
}
