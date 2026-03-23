//O(ST) 編集距離（レーベンシュタイン距離)
template <typename STRING>
int edit_distance(STRING& S, STRING& T) {
  int N = sz(S), M = sz(T);
  vc<int> dp(M + 1, 1 << 30);
  dp[0] = 0;
  rep(i, N + 1) {
    vc<int> newdp(M + 1, 1 << 30);
    rep(j, M + 1) {
      if (i < N) mins(newdp[j], dp[j] + 1);
      if (j < M) mins(dp[j + 1], dp[j] + 1);
      if (i < N && j < M) mins(newdp[j + 1], dp[j] + 1);
      if (i < N && j < M && S[i] == T[j]) mins(newdp[j + 1], dp[j]);
    }
    if (i < N) swap(dp, newdp);
  }
  return dp[M];
}
