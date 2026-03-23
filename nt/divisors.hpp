// sort はしない
vc<ll> divisors_by_pf(const vc<pair<ll, int>>& pf) {
  vl div = {1};
  for (auto&& [p, e]: pf) {
    ll n = sz(div);
    ll pp = 1;
    srep(i, 1, e + 1) {
      pp *= p;
      rep(j, n) div.eb(div[j] * pp);
    }
  }
  return div;
}

// sort はしない
vc<ll> divisors(ll N) {
  auto pf = factor(N);
  return divisors_by_pf(pf);
}

// sort はしない
vc<ll> divisors_by_lpf(ll N, vc<int>& lpf) {
  auto pf = factor_by_lpf(N, lpf);
  return divisors_by_pf(pf);
}
