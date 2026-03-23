struct Mono {
  using value_type = array<mint, 4>;// モノイドの型
  using X = value_type; 
  static X op(X x, X y) { // モノイドの二項演算 op 
    rep(i, 4) x[i] += y[i];
    return x;
  }
  static constexpr X unit() { return {0, 0, 0, 0}; } // モノイドの単位元 
  static constexpr bool commute = 1; // opが可換かどうか op(y,x)=op(x,y)
};
