// using mint = modint61 ;
// mint base  ; 
// (= RNG(mint::get_mod()))
struct Mono {
  using value_type = tuple<mint, mint, mint>;
  using X = value_type;
  static X op(X x, X y) {
    auto [x1, x2, px] = x;
    auto [y1, y2, py] = y;
    return {x1 + y1 * px, x2 * py + y2, px * py};
  }
  static constexpr X unit() { return {mint(0), mint(0), mint(1)}; }
  static constexpr bool commute = 0;
};

// char cにしたときのtupleを返す
tuple<mint,mint,mint>conv(char c){
	return {mint(c), mint(c), base} ;
} ;
