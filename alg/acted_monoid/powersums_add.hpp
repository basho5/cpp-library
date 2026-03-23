// 0, 1, ..., K 乗和
template <typename T>
struct ActedMonoid_Power_Sums_Add {
  using Monoid_X = Monoid_Add_Array<T, 3>;
  using Monoid_A = Monoid_Add<T>;
  using X = typename Monoid_X::value_type;
  using A = typename Monoid_A::value_type;
  static constexpr X act(const X &x, const A &a, const ll &size) {
		X y ; 
		auto[s0,s1,s2]=x ;
		y[0]=size ;
		y[1]=s1+a*size ;
		y[2]=s2+2*a*s1+a*a*size;
		return y ;
  }
};
