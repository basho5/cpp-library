const int mod = 998244353;
// const int mod = 1000000007;
template<int mod>
struct Modint {
  long long x;
  constexpr Modint(long long v = 0) noexcept : x(v % mod) { if(x < 0) x += mod; }
  constexpr int getmod() const { return mod; }
  constexpr Modint operator-() const noexcept { return Modint(x ? mod - x : 0); }
  constexpr Modint& operator+=(const Modint &r) noexcept { x += r.x; if(x >= mod) x -= mod; return *this; }
  constexpr Modint& operator-=(const Modint &r) noexcept { x -= r.x; if(x < 0) x += mod; return *this; }
  constexpr Modint& operator*=(const Modint &r) noexcept { x = x * r.x % mod; return *this; }
  constexpr Modint& operator/=(const Modint &r) noexcept { return *this *= ~(r); }
  constexpr Modint operator+(const Modint &r) const noexcept { return Modint(*this) += r; }
  constexpr Modint operator-(const Modint &r) const noexcept { return Modint(*this) -= r; }
  constexpr Modint operator*(const Modint &r) const noexcept { return Modint(*this) *= r; }
  constexpr Modint operator/(const Modint &r) const noexcept { return Modint(*this) /= r; }
  constexpr bool operator==(const Modint &r) const noexcept { return x == r.x; }
  constexpr bool operator!=(const Modint &r) const noexcept { return x != r.x; }
  constexpr Modint pow(long long n) const noexcept {
    if(n == 0) return Modint(1);
    if(n < 0) return (~(*this)).pow(-n);
    Modint t = this->pow(n / 2); t *= t;
    if(n & 1) t *= *this; return t;
  }
  constexpr Modint operator~() const noexcept { return this->pow(mod - 2); }
  constexpr Modint ppow(ll t)const {int p=mod-1; return pow((t%p+p)%p);}
};
istream& operator>>(istream &is, Modint<mod> &a) { ll v; is >> v; a = Modint<mod>(v); return is; }
ostream& operator<<(ostream &os, const Modint<mod> &a) { return os << a.x; }

using mint = Modint<mod> ; 
using vm = vector<mint>;
using vvm = vector<vm>;

struct modinv {
  int n; vector<mint> d;
  modinv(): n(2), d({mint(0), mint(1)}) {}
  mint operator()(int i) { while(n <= i) d.push_back(-d[mod % n] * mint(mod / n)), ++n; return d[i]; }
  mint operator[](int i) const { return d[i]; }
} invs;
struct modfact {
  int n; vector<mint> d;
  modfact(): n(2), d({mint(1), mint(1)}) {}
  mint operator()(int i) { while(n <= i) d.push_back(d.back() * mint(n)), ++n; return d[i]; }
  mint operator[](int i) const { return d[i]; }
} facs;
struct modfactinv {
  int n; vector<mint> d;
  modfactinv(): n(2), d({mint(1), mint(1)}) {}
  mint operator()(int i) { while(n <= i) d.push_back(d.back() * invs(n)), ++n; return d[i]; }
  mint operator[](int i) const { return d[i]; }
} ifacs;
mint comb(int a, int b) { return (a < b || b < 0) ? mint(0) : facs(a) * ifacs(b) * ifacs(a-b); }

namespace NTT {
    long long modpow(long long a, long long n, int mod) {
        long long res = 1;
        while (n > 0) {
            if (n & 1) res = res * a % mod;
            a = a * a % mod;
            n >>= 1;
        }
        return res;
    }

    long long modinv(long long a, int mod) {
        long long b = mod, u = 1, v = 0;
        while (b) {
            long long t = a / b;
            a -= t * b, swap(a, b);
            u -= t * v, swap(u, v);
        }
        u %= mod;
        if (u < 0) u += mod;
        return u;
    }

    int calc_primitive_root(int mod) {
        if (mod == 2) return 1;
        if (mod == 167772161) return 3;
        if (mod == 469762049) return 3;
        if (mod == 754974721) return 11;
        if (mod == 998244353) return 3;
        int divs[20] = {};
        divs[0] = 2;
        int cnt = 1;
        long long x = (mod - 1) / 2;
        while (x % 2 == 0) x /= 2;
        for (long long i = 3; i * i <= x; i += 2) {
            if (x % i == 0) {
                divs[cnt++] = i;
                while (x % i == 0) x /= i;
            }
        }
        if (x > 1) divs[cnt++] = x;
        for (int g = 2;; g++) {
            bool ok = true;
            for (int i = 0; i < cnt; i++) {
                if (modpow(g, (mod - 1) / divs[i], mod) == 1) {
                    ok = false;
                    break;
                }
            }
            if (ok) return g;
        }
    }

    int get_fft_size(int N, int M) {
        int size_a = 1, size_b = 1;
        while (size_a < N) size_a <<= 1;
        while (size_b < M) size_b <<= 1;
        return max(size_a, size_b) << 1;
    }

    // number-theoretic transform
    template<class mint> void trans(vector<mint>& v, bool inv = false) {
        if (v.empty()) return;
        int N = (int)v.size();
        int MOD = v[0].getmod();
        int PR = calc_primitive_root(MOD);
        static bool first = true;
        static vector<long long> vbw(30), vibw(30);
        if (first) {
            first = false;
            for (int k = 0; k < 30; ++k) {
                vbw[k] = modpow(PR, (MOD - 1) >> (k + 1), MOD);
                vibw[k] = modinv(vbw[k], MOD);
            }
        }
        for (int i = 0, j = 1; j < N - 1; j++) {
            for (int k = N >> 1; k > (i ^= k); k >>= 1);
            if (i > j) swap(v[i], v[j]);
        }
        for (int k = 0, t = 2; t <= N; ++k, t <<= 1) {
            long long bw = vbw[k];
            if (inv) bw = vibw[k];
            for (int i = 0; i < N; i += t) {
                mint w = 1;
                for (int j = 0; j < t/2; ++j) {
                    int j1 = i + j, j2 = i + j + t/2;
                    mint c1 = v[j1], c2 = v[j2] * w;
                    v[j1] = c1 + c2;
                    v[j2] = c1 - c2;
                    w *= bw;
                }
            }
        }
        if (inv) {
            long long invN = modinv(N, MOD);
            for (int i = 0; i < N; ++i) v[i] = v[i] * invN;
        }
    }

    // for garner
    static constexpr int MOD0 = 754974721;
    static constexpr int MOD1 = 167772161;
    static constexpr int MOD2 = 469762049;
    using mint0 = Modint<MOD0>;
    using mint1 = Modint<MOD1>;
    using mint2 = Modint<MOD2>;
    static const mint1 imod0 = 95869806; // modinv(MOD0, MOD1);
    static const mint2 imod1 = 104391568; // modinv(MOD1, MOD2);
    static const mint2 imod01 = 187290749; // imod1 / MOD0;

    // small case (T = mint, long long)
    template<class T> vector<T> naive_mul 
    (const vector<T>& A, const vector<T>& B) {
        if (A.empty() || B.empty()) return {};
        int N = (int)A.size(), M = (int)B.size();
        vector<T> res(N + M - 1);
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                res[i + j] += A[i] * B[j];
        return res;
    }

    // mint
    template<class mint> vector<mint> mul
    (const vector<mint>& A, const vector<mint>& B) {
        if (A.empty() || B.empty()) return {};
        int N = (int)A.size(), M = (int)B.size();
        if (min(N, M) < 30) return naive_mul(A, B);
        int MOD = A[0].getmod();
        int size_fft = get_fft_size(N, M);
        if (MOD == 998244353) {
            vector<mint> a(size_fft), b(size_fft), c(size_fft);
            for (int i = 0; i < N; ++i) a[i] = A[i];
            for (int i = 0; i < M; ++i) b[i] = B[i];
            trans(a), trans(b);
            vector<mint> res(size_fft);
            for (int i = 0; i < size_fft; ++i) res[i] = a[i] * b[i];
            trans(res, true);
            res.resize(N + M - 1);
            return res;
        }
        vector<mint0> a0(size_fft, 0), b0(size_fft, 0), c0(size_fft, 0);
        vector<mint1> a1(size_fft, 0), b1(size_fft, 0), c1(size_fft, 0);
        vector<mint2> a2(size_fft, 0), b2(size_fft, 0), c2(size_fft, 0);
        for (int i = 0; i < N; ++i)
            a0[i] = A[i].x, a1[i] = A[i].x, a2[i] = A[i].x;
        for (int i = 0; i < M; ++i)
            b0[i] = B[i].x, b1[i] = B[i].x, b2[i] = B[i].x;
        trans(a0), trans(a1), trans(a2), trans(b0), trans(b1), trans(b2);
        for (int i = 0; i < size_fft; ++i) {
            c0[i] = a0[i] * b0[i];
            c1[i] = a1[i] * b1[i];
            c2[i] = a2[i] * b2[i];
        }
        trans(c0, true), trans(c1, true), trans(c2, true);
        static const mint mod0 = MOD0, mod01 = mod0 * MOD1;
        vector<mint> res(N + M - 1);
        for (int i = 0; i < N + M - 1; ++i) {
            int y0 = c0[i].x;
            int y1 = (imod0 * (c1[i] - y0)).x;
            int y2 = (imod01 * (c2[i] - y0) - imod1 * y1).x;
            res[i] = mod01 * y2 + mod0 * y1 + y0;
        }
        return res;
    }

    // long long
    vector<long long> mul_ll
    (const vector<long long>& A, const vector<long long>& B) {
        if (A.empty() || B.empty()) return {};
        int N = (int)A.size(), M = (int)B.size();
        if (min(N, M) < 30) return naive_mul(A, B);
        int size_fft = get_fft_size(N, M);
        vector<mint0> a0(size_fft, 0), b0(size_fft, 0), c0(size_fft, 0);
        vector<mint1> a1(size_fft, 0), b1(size_fft, 0), c1(size_fft, 0);
        vector<mint2> a2(size_fft, 0), b2(size_fft, 0), c2(size_fft, 0);
        for (int i = 0; i < N; ++i)
            a0[i] = A[i], a1[i] = A[i], a2[i] = A[i];
        for (int i = 0; i < M; ++i)
            b0[i] = B[i], b1[i] = B[i], b2[i] = B[i];
        trans(a0), trans(a1), trans(a2), trans(b0), trans(b1), trans(b2);
        for (int i = 0; i < size_fft; ++i) {
            c0[i] = a0[i] * b0[i];
            c1[i] = a1[i] * b1[i];
            c2[i] = a2[i] * b2[i];
        }
        trans(c0, true), trans(c1, true), trans(c2, true);
        static const long long mod0 = MOD0, mod01 = mod0 * MOD1;
        vector<long long> res(N + M - 1);
        for (int i = 0; i < N + M - 1; ++i) {
            int y0 = c0[i].x;
            int y1 = (imod0 * (c1[i] - y0)).x;
            int y2 = (imod01 * (c2[i] - y0) - imod1 * y1).x;
            res[i] = mod01 * y2 + mod0 * y1 + y0;
        }
        return res;
    }
};

struct fps : vm {
#define d (*this)
#define s int(vm::size())
  template<class...Args> fps(Args...args): vm(args...) {}
  fps(initializer_list<mint> a): vm(rng(a)) {}
  int size() const { return vm::size();}
  void rsz(int n) { if (s < n) resize(n);}
  fps& low_(int n) { resize(n); return d;}
  fps low(int n) const { return fps(d).low_(n);}
  fps low(fps a, int n) const { return a.low_(n);}
  fps& rev_() { reverse(rng(d)); return d;}
  fps rev() const { return fps(d).rev_();}
  fps rev(fps a) const { return a.rev_();}
  fps odd(int si=1) const { fps r(s/2); for(int i=si;i<s;i+=2) r[i>>1]=d[i]; return r;}
  inline fps& normalize(){
		while(!d.empty()&&d.back()==0)  d.pop_back() ;
		return d;
}
  inline fps pre(int n)const {return fps(d.begin(),d.begin()+min(sz(d),n)) ;}
  mint& operator[](int i) { rsz(i+1); return vm::operator[](i);}
  mint operator[](int i) const { return i<s ? vm::operator[](i) : 0;}
  mint operator()(mint x) const { mint r; drep(i,s) r = r*x+d[i]; return r;}
  fps operator<<(int a) const { fps r(d); r.insert(r.begin(), a, 0); return r;}
  fps operator>>(int a) const { fps r(d); r.rsz(a); r.erase(r.begin(), r.begin()+a); return r;}
  fps& fit() { while (s && !back().x) pop_back(); return d;}
  fps operator-() const { fps r(d); rep(i,s) r[i] = -r[i]; return r;}
  // inline fps& operator+=(const fps& a) { rsz(sz(a)); rep(i,sz(a)) d[i] += a[i]; return this->normalize();}
  fps& operator+=(const fps& a) { rsz(sz(a)); rep(i,sz(a)) d[i] += a[i]; return d ;}
  //inline fps& operator-=(const fps& a) { rsz(sz(a)); rep(i,sz(a)) d[i] -= a[i];return this->normalize();}
  fps& operator-=(const fps& a) { rsz(sz(a)); rep(i,sz(a)) d[i] -= a[i];return d;}
  fps& operator*=(const fps& a) { return d = NTT::mul(d, a);}
  fps& operator/=(const fps& a) {
		assert(!a.empty());
		assert(a.back() != 0) ;
		d.normalize() ; 
		if(s < sz(a)){ d=fps(1,0) ; return d; }
		int w = s-sz(a)+1;;
    return d=(d.rev().pre(w) * (a.rev()).inv(w)).pre(w).rev() ;
  }
  fps& operator%=(const fps& a) {
		assert(!a.empty());
		assert(a.back() != 0) ;
		d.normalize() ; fps q=d/a; 
		return d -= q*a; 
  }
  fps& operator*=(mint a) { rep(i,s) d[i] *= a; return d;}
  fps& operator/=(mint a) { return d *= ~(a);}
  fps& operator*=(int a) { return d *= mint(a);}
  fps& operator/=(int a) { return d /= mint(a);}
  fps operator+(const fps& a) const { return fps(d) += a;}
  fps operator-(const fps& a) const { return fps(d) -= a;}
  fps operator*(const fps& a) const { return fps(d) *= a;}
  fps operator/(const fps& a) const { return fps(d) /= a;}
  fps operator%(const fps& a) const { return fps(d) %= a;}
  fps operator*(mint a) const { return fps(d) *= a;}
  fps operator/(mint a) const { return fps(d) *= ~(a);}
  fps operator*(int a) const { return fps(d) *= mint(a);}
  fps operator/(int a) const { return fps(d) /= mint(a);}
  fps& mul1(mint a) { pb(0); drep(i,s-1) d[i+1] += d[i], d[i] *= a; return d;} // *=(x+a), /=(x+a)
  fps& div1(mint a) { mint pre = back(); pop_back(); drep(i,s) std::swap(pre, d[i]), pre -= d[i]*a; return d;}
  fps dif() const { fps r(s-1); repp(i,sz(r)) r[i-1] = d[i]*i; return r;}
  fps integ() const { fps r(s+1); repp(i,s) r[i] = d[i-1]/(mint)i; return r;}
  fps inv() const { return inv(s);}
  fps inv(int w) const {
	assert(d[0] != 0) ;if(w<0) w=sz(d) ;
    fps r({~(d[0])});
    for (int i = 1; i < w; i <<= 1)r=(r+r-r*r*(d.pre(i<<1))).pre(i<<1) ;
	r.resize(w) ;
    return r;
  }

  inline friend fps gcd(const fps &f, const fps &g){
		if(g.empty()) return f; 
		return gcd(g, f%g) ;
  }
  
  // log(f) = \int f'/f dx, f[0] must be 1
  inline friend fps log(const fps &f, int w){
		assert(f[0]==1) ;
		fps r= (f.dif()*f.inv(w)).integ() ; r.resize(w) ;return r ;
	}
  inline friend fps log(const fps &f){return log(f, sz(f));}

  // exp(f), f[0] must be 0
  inline friend fps exp(const fps &f, int w){
		assert(f[0] == 0) ;
		fps r(1,1) ;
		for(int i=1; i<w;i<<=1){
			r=r*(f.pre(i<<1)-log(r,i<<1)+fps(1,1)).pre(i<<1) ;
		}
		r.resize(w) ;return r ;
  }
  inline friend fps exp(const fps &f){return exp(f,sz(f));}

  fps fps_pow_parse(fps &f, mint k){
		int N = f.size() ;
		vector<pair<int, mint>> dat;
        for (int i = 1; i < N; ++i) if (f[i] != mint(0)) dat.emplace_back(i, f[i]);
        fps g(N);
        g[0] = 1;
        for (int n = 0; n < N - 1; ++n) {
			mint &x = g[n + 1];
            for (auto &&[di, cf]: dat) {
				if (di > n + 1) break;
				mint t = cf * g[n - di + 1];
				x += t * (k * mint(di) - mint(n - di + 1));
			}
			x *= invs((n+1));
		}
		return g;
	}
	// sparse  {f(x)}^k 
  fps pow_sparse(ll k) {
	int n = s ;
	if(k==0){fps g(n);g[0] = mint(1);return d = g;}
	int di = n;
	for (int i = n - 1; i >= 0; --i) if (d[i] != mint(0)) di = i;
	if (k > 0 && di >= (n + k - 1) / k) return d = fps(n, 0);
	ll off = di * k;
	mint c = d[di];
	mint c_inv = mint(1) / mint(c);
	fps g(n - off);
	for (int i = 0; i < n - off; ++i) g[i] = d[di + i] * c_inv;
	g = fps_pow_parse(g, mint(k)) ;
	fps h(n);
	c = c.pow(k);
	for (int i = 0; i < int(g.size()); ++i) h[off + i] = g[i] * c;
	return d = h;
}

  // pow(f) = exp(e * log f)
   inline friend fps pow(const fps& f, long long e, int deg) {
    if(deg < 0) deg = sz(f); 
    if(e == 0){
        fps r(deg, 0); 
        r[0] = 1; 
        return r;
    } 
	int cnt=0 ;
	rep(i, sz(f)){if(f[i]!=mint(0)) cnt ++ ;}
	if(cnt<=10){fps g(deg);rep(i, min(deg,sz(f))) g[i]=f[i];return g.pow_sparse(e);} 
    ll i = 0;
    while(i < sz(f) && f[i] == 0) ++i;
    if(i == sz(f) || i > (deg-1)/e) return fps(deg, 0);
    mint k = f[i];fps res = f >> i; 
    res /= k;res = log(res,deg);res *= mint(e) ;res = exp(res, deg) ;
	res *= mint(k).ppow(e) ;res = res<<(e*i) ; res.resize(deg) ;return res ;
}
  inline friend fps pow(const fps &f, ll e){return pow(f,e,sz(f));}
	

  // sqrt(f), f[0] must be 1
  inline friend fps sqrt_base(const fps &f,int w){
		assert(f[0] == 1) ;mint inv2=~(mint(2)) ;fps r(1,1) ;
		for(int i=1;i<w;i<<=1){
			r=(r+f.pre(i<<1))*(r.inv(i<<1)).pre(i<<1) ;
			for(mint &x:r) x*=inv2; 
		}
		r.resize(w) ;return r;
  }
  inline friend fps sqrt_base(const fps &f){return sqrt_base(f,sz(f));}

   
  // sparse は 基本的には 非零の項が10以下くらいが適切
  // sparse の乗算
  fps &operator*=(vector<pair<int,mint>> g){
		int n=sz(d) ;
		auto [a, c]=g.front() ;
		if(a == 0) g.erase(g.begin()) ;
		else c=0 ;
		drep(i, n){
			d[i]*= c;
			for(auto &[j, b]:g){
				if(j>i) break  ;
				d[i] += d[i-j]*b ; 
			}
		}
		return d;
	}

   // sparse の 徐算
   fps &operator/=(vector<pair<int, mint>> g) {
		    int n = (*this).size();
		    auto [a, c] = g.front();
		    assert(a == 0 && c != mint(0));
		    mint cmi = c ;
		    mint ic = mint(1)/mint(c) ;
		    g.erase(g.begin());
		    for(ll i = 0; i<n ;i++){
			      for (auto &&[j, b] : g) {
				        if (j > i) break;
				        (*this)[i] -= (*this)[i-j] * b;
				      }
			      (*this)[i] *= ic;
			    }
		    return *this;
		  }


  vm operator()(const vm& x) const {
    int n = sz(x), n2 = n<<1;
    vc<fps> t(n2);
    rep(i,n) t[n+i] = {-x[i],1};
    for (int i = n-1; i; --i) t[i] = t[i<<1]*t[i<<1|1];
    t[1] = d%t[1];
    srep(i,2,n2) t[i] = t[i>>1]%t[i];
    vm r(n);
    rep(i,n) r[i] = t[n+i][0];
    return r;
  }

  fps taylorShift(mint c) const {
	const int n = s ;
    fps res, a(n), b(n,1);
    rep(i,s) a[i] = d[i]*facs(i);
    drep(i,s-1) b[i] = b[i+1]*c;
    rep(i,s) b[i] *= ifacs(s-1-i);
    a *= b;
    rep(i,s) res[i] = a[s-1+i]*ifacs[i];
    return res;
  }
  fps combConv(bool _inv=true) const {
	const int n = s ;
    fps res, a(n), b(n);
    rep(i,s) a[i] = d[i]*ifacs(i);
    rep(i,s) b[i] = ifacs(i);
    if (_inv) rep(i,s) if (i&1) b[i] = -b[i];
    a *= b;
    rep(i,s) res[i] = a[i]*facs(i);
    return res;
  }
  // find [x^N] P(x)/Q(x)
  // O(K log K log N), K = max(deg(P(x)), deg(Q(x)))
  mint bostanMori(ll n, fps p={1}) const {
    if (n == 0) return p[0]/d[0];
    fps q(*this); for (int i = 1; i < s; i += 2) q[i] = -q[i];
    p = (p*q).odd(n&1);
    q = (d*q).odd(0);
    return q.bostanMori(n>>1,p);
  }
#undef s
#undef d
};

// --- 分割統治法による多項式積の実装 ---
// 一次式 (a*x + b) を表す fps は {b, a} とする
fps polyproduct(const vector<fps> &polys, int l, int r) {
  if (r - l == 1) return polys[l];
  int mid = (l + r) / 2;
  fps left = polyproduct(polys, l, mid);
  fps right = polyproduct(polys, mid, r);
  return left * right;
}

// productPolyUnified: 与えられた数列 A, B, C と整数 N に対して、
// F(x)=∏_{i=0}^{n-1} (a_i + b_i*x)^(c_i) の 0 次から N 次までの係数展開（fps）を返す
fps productPolyUnified(const vector<int>& A, const vector<int>& B, const vector<int>& C, int N) {
    int n = A.size();
// 各項 (a_i + b_i*x)^(c_i) = a_i^(c_i) * (1 + (b_i/a_i)x)^(c_i)
// よって、定数因子は ∏ a_i^(c_i)、
    mint const_factor = mint(1);
    vector<int> d(n); // d[i] = b_i * inv(a_i) mod mod
    for (int i = 0; i < n; i++){
        const_factor *= mint(A[i]).pow(C[i]);
        mint invA = ~mint(A[i]);
        mint d_val = mint(B[i]) * invA;
        d[i] = d_val.x; // mod 内の値として int に格納
    }
    
    // ----- buildRational の処理 -----
    // 各葉で r_i(x)= c_i/(1 - d_i*x) を展開する。
    // ここでは deg = N+2 次まで必要とする。
    int deg = N + 2;
    // buildRational を分割統治法で構成する再帰関数をラムダで定義
    function<pair<fps, fps>(int, int)> buildRational = [&](int L, int R) -> pair<fps, fps> {
        if (R - L == 1) {
            // 各葉： r_i(x)= c_i/(1 - d_i*x)
            // 展開すると： Q_i(x)= 1 - d_i*x, P_i(x)= c_i.
            fps Q = { mint(1), mint(-d[L]) };
            fps P = { mint(C[L]) };
            return {P, Q};
        }
        int mid = (L + R) / 2;
        auto left = buildRational(L, mid);
        auto right = buildRational(mid, R);
        // 全体として、R(x)=∑ r_i(x)= P(x)/Q(x) となるように合成
        fps P = left.first * right.second;
        fps tmp = right.first * left.second;
        if(P.size() < tmp.size()) P.resize(tmp.size());
        for (size_t i = 0; i < tmp.size(); i++) {
            P[i] = P[i] + tmp[i];
        }
        fps Q = left.second * right.second;
        if(P.size() > (size_t)deg) P.resize(deg);
        if(Q.size() > (size_t)deg) Q.resize(deg);
        return {P, Q};
    };
    
    auto rat = buildRational(0, n);
    fps P = rat.first, Q = rat.second;
    // R(x)= P(x)/Q(x) を deg 次まで展開する
    fps invQ = Q.inv(deg);
    fps R_poly = P * invQ;
    R_poly.resize(deg);
    
    // ----- computeF の処理 -----
    // (log F)'(x) = ∑_{k>=0} (-1)^k * r_{k+1} * x^k,
    // ただし、r_k は R_poly の係数。
    fps logFprime(N+1, mint(0));
    for (int k = 0; k <= N; k++){
        mint sign = (k % 2 == 0 ? mint(1) : mint(mod - 1));
        if(k+1 < (int)R_poly.size()) logFprime[k] = sign * R_poly[k+1];
        else logFprime[k] = mint(0);
    }
    // 積分して log F(x) を求める（定数項は 0 とする）
    fps logF = logFprime.integ();
    logF.resize(N+1);
    // F(x) = exp(log F(x)) を計算（N+1 次まで）
    fps F = exp(logF, N+1);
    F.resize(N+1);
    for (int i = 0; i <= N; i++){
        F[i] *= const_factor;
    }
    return F;
}

// 目的の積の 0 次から N 次までの展開を O(M + N log N) 
// productSparse 関数
// //
// // 入力:
// //   a    : 各項の指数 a_i のリスト
// //   N    : 0 次から N 次までの展開を求める
// //   mode : 以下の4種類のモード
// //          mode == 0 :  Π (1 + x^(a_i))
// //                     → log(1+x^(a_i)) = x^(a_i) - x^(2a_i)/2 + x^(3a_i)/3 - ... 
// //                     ※各項の対数展開で係数は c(j)= (-1)^(j-1)/j
// //
// //          mode == 1 :  Π (1 - x^(a_i))^(-1)
// //                     → log((1-x^(a_i))^(-1)) = x^(a_i) + x^(2a_i)/2 + x^(3a_i)/3 + ...
// //                     ※各項の対数展開で係数は c(j)= 1/j
// //
// //          mode == 2 :  Π (1 - x^(a_i))
// //                     → log(1-x^(a_i)) = - x^(a_i) - x^(2a_i)/2 - x^(3a_i)/3 - ...
// //                     ※各項の対数展開で係数は c(j)= -1/j
// //
// //          mode == 3 :  Π (1 + x^(a_i))^(-1)
// //                     → log((1+x^(a_i))^(-1)) = - x^(a_i) + x^(2a_i)/2 - x^(3a_i)/3 + ...
// //                     ※各項の対数展開で係数は c(j)= -(-1)^(j-1)/j
// //
fps productSparse(const vector<int>& a, int N, int mode) {
    vector<int> cnt(N+1, 0); for (int ai : a)if (ai <= N) cnt[ai]++;
    fps L(N+1, mint(0)); invs(N+2) ;
    for (int n = 1; n <= N; n++) {
        if (cnt[n] == 0) continue;
        for (int j = 1; j * n <= N; j++) {
            mint coef = mint(cnt[n])*invs[j];
            if (mode == 0) { 
                if ((j & 1) == 0) coef = -coef;
            } else if (mode == 1) {
            } else if (mode == 2) {
                coef = -coef;
            } else if (mode == 3) {
                if ((j & 1) == 0) {
                } else {
                    coef = -coef;
                }
            }
            L[j*n] += coef;
        }
    }
    fps F = exp(L, N+1);F.resize(N+1); return F;
}


// マージテク：区間 [l, r) の多項式の積を返す再帰関数
// 多項式の総次数をMとしたときo(M(logM)^2) 
fps mergePolys(const vector<fps>& polys, int l, int r) {
    if(r - l == 1) return polys[l];
    int mid = (l + r) / 2;
    fps left = mergePolys(polys, l, mid);
    fps right = mergePolys(polys, mid, r);
    fps res = left * right;
    return res;
}

// (1-x^(a_i))/(1-x) の積を展開する関数
// 引数: 
//   a : 各 a_i のリスト（a_i は非負整数）
//   N : 0次から N次まで求める（N+1 項）
// ※ ここで m = a.size() が項数（もともとの (1-x^(a_i))/(1-x) の積）
fps polyfactor(const vector<int> &a, int N){
	int m=sz(a) ;fps f1=productSparse(a, N, 2) ;
	fps f2(N+1) ;rep(k, N+1) f2[k]=comb(m+k-1, k) ;
	fps res=f1*f2; res.resize(N+1) ;
	return res ;
}


using sfps = vector<pair<int,mint>>  ;
