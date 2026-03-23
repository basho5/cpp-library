template <typename T>
void divisor_zeta(vc<T>& A) {
  assert(A[0] == 0);
  int N = sz(A) - 1;
  auto P = primetable(N);
  for (auto&& p: P) { rep(x, 1, N / p + 1) A[p * x] += A[x]; }
}

template <typename T>
void divisor_mobius(vc<T>& A) {
  assert(A[0] == 0);
  int N = sz(A) - 1;
  auto P = primetable(N);
  for (auto&& p: P) { drep(x, 1, N / p + 1) A[p * x] -= A[x]; }
}

template <typename T>
void multiplier_zeta(vc<T>& A) {
  assert(A[0] == 0);
  int N = sz(A) - 1;
  auto P = primetable(N);
  for (auto&& p: P) { drep(x, 1, N / p + 1) A[x] += A[p * x]; }
}

template <typename T>
void multiplier_mobius(vc<T>& A) {
  assert(A[0] == 0);
  int N = sz(A) - 1;
  auto P = primetable(N);
  for (auto&& p: P) { rep(x, 1, N / p + 1) A[x] -= A[p * x]; }
}
