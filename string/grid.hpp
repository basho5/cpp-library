// template<typename T=int>
// struct grid{
// 	int h, w ; 
// 	vv<T> g ;
// 	grid(int h, int w):h(h),w(w){g =  vector (h, vc<T>(w)) ;} ;
// 	grid(vv<T> a):h(sz(a)),w(sz(a[0])),g(a){}
// 	vc<T> &operator[](int i){return g[i];}
// 	const vc<T>&operator[](int i)const {return g[i];}
// 	void add(int i, int j, T a){g[i][j]+=a ;}
// 	void rot(){int oh=h,ow=w;vv<T> p=g;g=vv<T>(ow,vc<T>(oh));
// 		rep(i,oh)rep(j,ow) {g[j][oh-i-1]=p[i][j];}swap(h, w) ;
// 	}
// 	bool can_all_put(int i, int j, const grid<T> &a){
// 		return i>=0&&j>=0&&i+a.h<=h&&j+a.w<=w ;
// 	}
// 	bool in(int i, int j){return i>=0&&j>=0&&i<h&&j<w;}
// 	void put(int i, int j, const grid<T> &a) {
// 		int ah=a.h, aw=a.w; 
// 		rep(x, ah)rep(y,aw){
// 			if(!in(x+i,y+j)) continue; 
// 			g[x+i][y+j]=a.g[x][y] ;
// 		}
// 	}
// 	// [i, j]を左上として1のみを貼り付けることはできるか
// 	// 負のでもいける shift_put(-10,-100,a)
// 	// つまり[i, j]だけshiftして1の部分だけを貼り付けれるか判定
// 	// 状況によって#を変更する
// 	bool shift_put(int i, int j, const grid &a){
// 		int ah=a.h,aw=a.w;
// 		rep(x,ah)rep(y,aw){
// 			if(!in(i+x,y+j)&&a.g[x][y]=='#') return false ;
// 		}
// 		rep(x, ah)rep(y,aw){if(a.g[x][y]=='#'){g[i+x][y+j]=a.g[x][y];}}
// 		return true;
// 	}
//
// } ;
struct grid{
	int h, w ; 
	vv<int> g ;
	grid(int h, int w):h(h),w(w),g(vvi(h,vi(w))){} 
	grid(vv<int> a):h(sz(a)),w(sz(a[0])),g(a){} 
	vc<int>&operator[](int i){return g[i]; }
	const vc<int>&operator[](int i)const {return g[i];}

	//90度回転
	void rot(){int oh=h,ow=w;vvi p=g;g=vvi(ow,vi(oh,0));
		rep(i,oh)rep(j,ow) {g[j][oh-i-1]=p[i][j];}swap(h, w) ;
	}

	bool in(int i, int j){return i>=0&&i<h&&j>=0&&j<w;} // 範囲判定
	
	// [i, j]を左上としてgrid aを貼り付ける
	void put(int i, int j,const grid &a){
		int ah=a.h,aw=a.w ;
		rep(x, ah)rep(y, aw){
			if(!in(i+x,j+y))continue; 
			g[i+x][j+y]=a.g[x][y] ;
		}
	}

	// 図形を(i, j)だけシフトする
	// ただし1がはみ出すこともあるので注意
	void shift(int i, int j){
		vvi r=g ;g=vvi(h,vi(w));
		rep(x,h)rep(y,w){
			if(r[x][y]==1){
				if(in(x+i,y+j)) g[x+i][y+j]=r[x][y];
			}
		}
	}

	// 図形を(i, j)に寄せる(デフォルトは左上)
	void normalize(int i=0, int j=0){
		int li=h,lj=w ;
		rep(x, h)rep(y, w){
			if(g[x][y]==1){
				li=min(li,x);
				lj=min(lj,y);
				break ;
			}
		}
		if(li==h||lj==w) return ;
		shift(i-li,j-lj) ;
	}

	// [i, j]を左上としてgrid aを全部貼り付けれるか
	bool can_all_put(int i, int j,const grid a){return i>=0&&j>=0&&i+a.h<=h&&j+a.w<=w;}

	// [i, j]を左上として1のみを貼り付けることはできるか
	// 負のでもいける shift_put(-10,-100,a)
	// つまり[i, j]だけshiftして1の部分だけを貼り付けれるか判定
	bool shift_put(int i, int j, const grid &a){
		int ah=a.h,aw=a.w;
		rep(x,ah)rep(y,aw){
			if(!in(i+x,y+j)&&a.g[x][y]==1) return false ;
		}
		rep(x, ah)rep(y,aw){if(a.g[x][y]==1){g[i+x][y+j]++;}}
		return true;
	}

} ;
