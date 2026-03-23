// ull -> Val
template <typename Val>
struct HashMap {
  // n は入れたいものの個数で ok
  HashMap(uint n = 0) { build(n); }
  void build(uint n) {
    uint k = 8;
    while (k < n * 2) k *= 2;
    cap = k / 2, mask = k - 1;
    key.resize(k), val.resize(k), used.assign(k, 0);
  }

  // size を保ったまま. size=0 にするときは build すること.

  void clear() {
    used.assign(sz(used), 0);
    cap = (mask + 1) / 2;
  }
  int size() { return sz(used) / 2 - cap; }

  int index(const ull& k) {
    int i = 0;
    for (i = hash(k); used[i] && key[i] != k; i = (i + 1) & mask) {}
    return i;
  }

  Val& operator[](const ull& k) {
    if (cap == 0) extend();
    int i = index(k);
    if (!used[i]) { used[i] = 1, key[i] = k, val[i] = Val{}, --cap; }
    return val[i];
  }

  Val get(const ull& k, Val default_value) {
    int i = index(k);
    return (used[i] ? val[i] : default_value);
  }

  bool count(const ull& k) {
    int i = index(k);
    return used[i] && key[i] == k;
  }

  // f(key, val)

  template <typename F>
  void enumerate_all(F f) {
    rep(i, sz(used)) if (used[i]) f(key[i], val[i]);
  }

private:
  uint cap, mask;
  vc<ull> key;
  vc<Val> val;
  vc<bool> used;

  ull hash(ull x) {
    static const ull FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
    x += FIXED_RANDOM;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return (x ^ (x >> 31)) & mask;
  }

  void extend() {
    vc<pair<ull, Val>> dat;
    dat.reserve(len(used) / 2 - cap);
    rep(i, sz(used)) {
      if (used[i]) dat.eb(key[i], val[i]);
    }
    build(2 * len(dat));
    for (auto& [a, b]: dat) (*this)[a] = b;
  }
};
