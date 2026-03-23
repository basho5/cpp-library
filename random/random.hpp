ull RNG_64() {
  static ull x_ = ull(chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count()) * 10150724397891781847ULL;
  x_ ^= x_ << 7;
  return x_ ^= x_ >> 9;
}
// [0, LIM)
ull RNG(ull lim) { return RNG_64() % lim; }
// [l, r)
ll RNG(ll l, ll r) { return l + RNG_64() % (r - l); }
