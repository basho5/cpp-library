ll modpow(ll a, ll b, ll mod){
	ll res=1; a%=mod; 
	while(b){
		if(b&1) res=((i128)res*a)%mod ;
		a=((i128)a*a)%mod ;
		b>>=1 ;
	}
	return res ;
} 
