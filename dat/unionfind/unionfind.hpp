struct UnionFind{
	vector<int> parents ;
	vector<int> m_size ;
	UnionFind(size_t n){
		init(n) ;
	}

	void init(size_t n) {
		parents.resize(n) ;
		m_size.assign(n, 1) ;
		iota(parents.begin(), parents.end(), 0) ;
	}

	int leader(int i){
		if(parents[i] == i){
			return i ;
		}
		return (parents[i] = leader(parents[i])) ;
	}

	void merge(int a, int b){
		a = leader(a) ;
		b = leader(b) ;
		if(a != b){
			if(m_size[a] < m_size[b]){
				swap(a, b) ;
			}
			parents[b] = a ;
			m_size[a] += m_size[b] ;
		}
	}

	bool same(int a, int b){
		return (leader(a) == leader(b)) ;
	}

	int size(int i){
		return m_size[leader(i)] ;
	}

	// 各連結成分のリストを返す
	// o(n)
	vector<vector<int>> groups(){
		int n = parents.size() ;
		vector<int> g(n, -1) ;
		vector<vector<int>> res ;
		for(int i=0; i<n;i++){
			int r = leader(i) ;
			if(g[r] == -1){
				g[r] = res.size() ;
				res.push_back({}) ;
			}
			res[g[r]].push_back(i) ;
		}
		return res ;
	}

};

