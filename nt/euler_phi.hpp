//1からnまででnと互いに素なものの個数(オイラー関数)
ll euler_phi(ll n) {
  auto pf = factor(n);
  for (auto&& [p, e]: pf) n -= n / p;
  return n;
}

template <typename T>
vc<T> euler_phi_table(ll n) {
  vc<T> A(n + 1);
  repp(i, 1, n + 1) A[i] = T(i);
  divisor_mobius(A);
  return A;
}
