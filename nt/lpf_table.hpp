// [0, LIM], 0, 1 には -1 が入る。
vc<int> lpf_table(ll LIM) {
  auto primes = primetable(LIM);
  vc<int> res(LIM + 1, -1);
  drep(i, sz(primes)) {
    auto p = primes[i];
    srep(j, 1, LIM / p + 1) res[p * j] = p;
  }
  return res;
}
