template <typename E>
struct ActedMonoid_CntSum_Affine { 
  using Monoid_X = Monoid_Add_Pair<E>; // {個数, 総和}
  using Monoid_A = Monoid_Affine<E>;
  using X = typename Monoid_X::value_type;
  using A = typename Monoid_A::value_type;
  static constexpr X act(const X &x, const A &a, const ll &size) {
    return {x.fi, x.se * a.fi + x.fi * a.se};
  }
};
