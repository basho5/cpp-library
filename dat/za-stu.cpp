// coordinate compression
template<typename T=int>
struct X {
  bool ini; vc<T> d;
  X(): ini(false) {}
  /*
  X(vc<T>& a): ini(true), d(a) {
    init();
    for (T& na : a) na = (*this)(na);
  }// int only */
  void add(const T& x) { assert(!ini); d.pb(x);}
  void init() {
    sort(rng(d));
    d.erase(unique(rng(d)), d.end());
    ini = true;
  }
  int size() { if (!ini) init(); return sz(d);}
  // 座圧前の値
  T operator[](int i) { if (!ini) init(); return d[i];}
  // 座圧後の値
  int operator()(const T& x) {
    if (!ini) init();
    return upper_bound(rng(d),x)-d.begin()-1;
  }
  bool in(const T& x) { if (!ini) init(); return binary_search(rng(d),x);}
};
//
