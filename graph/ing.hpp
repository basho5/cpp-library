vvi ing(int n, int m=-1, bool bi=true) {
  if (m == -1) m = n-1;
  vvi to(n);
  rep(i,m) {
    int a, b;
    scanf("%d%d",&a,&b);
    --a; --b;
    to[a].pb(b);
    if (bi) to[b].pb(a);
  }
  return to;
}

template<typename T> 
vv<pair<int,T>> ingw(int n, int m=-1, bool bi=true) {
  if (m == -1) m = n-1;
  vv<pair<int,T>> to(n);
  rep(i,m) {
    int a, b;
    scanf("%d%d",&a,&b);
    --a; --b;
	T c ;cin>>c ;
    to[a].pb({b, c});
    if (bi) to[b].pb({a, c});
  }
  return to;
}
