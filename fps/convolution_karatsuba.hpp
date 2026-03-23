#line 2 "fps/convolution_karatsuba.hpp"
// 任意の環でできる
template <typename T>
vc<T> convolution_karatsuba(const vc<T>& f, const vc<T>& g) {
  const int thresh = 30;
  if (min(sz(f), sz(g)) <= thresh) return convolution_naive(f, g);
  int n = max(sz(f), sz(g));
  int m = ceil(n, 2);
  vc<T> f1, f2, g1, g2;
  if (sz(f) < m) f1 = f;
  if (sz(f) >= m) f1 = {f.begin(), f.begin() + m};
  if (sz(f) >= m) f2 = {f.begin() + m, f.end()};
  if (sz(g) < m) g1 = g;
  if (sz(g) >= m) g1 = {g.begin(), g.begin() + m};
  if (sz(g) >= m) g2 = {g.begin() + m, g.end()};
  vc<T> a = convolution_karatsuba(f1, g1);
  vc<T> b = convolution_karatsuba(f2, g2);
  rep(i, sz(f2)) f1[i] += f2[i];
  rep(i, sz(g2)) g1[i] += g2[i];
  vc<T> c = convolution_karatsuba(f1, g1);
  vc<T> F(sz(f) + sz(g) - 1);
  assert(2 * m + sz(b) <= sz(F));
  rep(i, sz(a)) F[i] += a[i], c[i] -= a[i];
  rep(i, sz(b)) F[2 * m + i] += b[i], c[i] -= b[i];
  if (c.back() == T(0)) c.pop_back();
  rep(i, sz(c)) if (c[i] != T(0)) F[m + i] += c[i];
  return F;
}
