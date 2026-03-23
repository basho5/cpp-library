// 整数x, yの最大公約数を求める
T gcd(T a , T b ){return b?gcd(b, a%b):a;};

// a, bの最小公倍数
template<typename T> 
T lcm(T a, T b){return a/gcd(a, b)* b;} ;

// 互いに素な整数a, b に対してax + by = gcd(a, b) の解を求める(互いに素じゃないときは解がないため)
// max(|x|, |y|) <= max(|a|, |b|) 
// o(log(min(|a|, |b|)))
template<typename T> 
pair<T,T> extgcd(T a, T b){
	if(b == 0) return {1, 0} ;
	auto [y, x]=extgcd(b, a%b) ;
	y -= a/b * x ;
	return {x, y} ;
};



