template <typename VC>
vc<VC> transpose(const vc<VC>& A, int H = -1, int W = -1) {
  if (H == -1) { H = sz(A), W = (sz(A) == 0 ? 0 : sz(A[0])); }
  vc<VC> B(W, VC(H, 0));
  rep(x, H) rep(y, W) B[y][x] = A[x][y];
  return B;
}
