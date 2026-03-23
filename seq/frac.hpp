// p/q 
struct frac {
  ll p, q ;
  frac(ll p=0, ll q=1): p(p), q(q) {} 
  bool operator<(const frac &a)const {
    return p*a.q < q*a.p ;
  } 
  bool operator<=(const frac &a)const {
    return p*a.q <= q*a.p ;
  } 
} ;
