struct gridset{
	set<P> g ;
	gridset():g(set<P> {}){}  

	void add(int i, int j){g.insert({i, j});}

	// (i, j)だけ座標をshiftする
	void shift(int i, int j){
		set<P> old ;swap(g,old) ;
		for(auto [x,y]:old) {g.insert({x+i,y+j});}
	}

	// gridset a を (i,j) だけシフトして、g に合流
	void shift_put(int i, int j, gridset a){
		a.shift(i, j) ;
		g.merge(a.g);
	}

	// gridset a をg に合流
	void put(gridset a){g.merge(a.g);}

	// gridset a をg に合流できるか
	bool can_merge(gridset a){
		for(auto i:g){
			if(a.g.count(i)) return false ;
		}
		return true ;
	}

	//g 中の '#' が存在する最小の x,y を(i, j) にシフト
	//デフォルトは(0, 0)にシフト
	void normalize(int i=0, int j=0){
		int li=1e9, lj=1e9 ;
		for(auto [x, y]:g){mins(li,x), mins(lj,y);}
		shift(i-li, j-lj) ;
	}

	// 90° 時計回りに回転,その後(i, j)にシフトnormalize
	void rot(int i=0, int j=0) {
		set<P> old ;swap(g,old) ;
		for(auto [x,y]:old) {g.insert({y,-x});}
		normalize(i, j) ;
	}

	// H × W のグリッドに収まってるかを判定
	bool in(int H, int W) const {
    for (auto [x, y] : g) {
        if (x < 0 || x >= H || y < 0 || y >= W)
            return false;
    }
    return true;
}
} ;
