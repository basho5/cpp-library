ll digit_sum(ll x) {
  const int K = 100'000; // ここは桁数ごとに変える
  static vi dp(K);
  if (dp[1] == 0) { rep(x, 1, K) dp[x] = dp[x / 10] + (x % 10); }
  int res = 0;
  while (x) {
    res += dp[x % K];
    x /= K;
  }
  return res;
}
