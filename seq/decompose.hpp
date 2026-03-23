// 区間[l, r)を[2^i*j , 2^i*(j+1)) の区間に分解 
vlp decompose(ll l, ll r){
	vlp res ; 
	int p=0 ;
	while(l<r){
		if(l&1){
			res.eb(l<<p,(l+1)<<p) ;
			l ++ ; 
		}
		if(r&1){
			res.eb((r-1)<<p,r<<p) ;
			r -- ;
		}
		l >>= 1 , r >>= 1, p++ ; 
	}
	sort(rng(res)) ;
	return res ;
}
