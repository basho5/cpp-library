struct ActedMonoid {
  using Monoid_X = Mono; //操作対象の型 
  using Monoid_A = Monoid_Add_Pair<mint>; // 作用(更新操作)の型
  using X = typename Monoid_X::value_type;
  using A = typename Monoid_A::value_type;
  // mapping x -> A(x)
  static X act(const X &x, const A &f, const ll &size) { 
    auto [a, b] = f;
    return {x[0], x[1] + a * x[0], x[2] + b * x[0],
            x[3] + b * x[1] + a * x[2] + a * b * x[0]};
  }
};
