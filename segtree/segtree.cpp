#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
#define rep(i,n) for (int i = 0 ; i < n ; ++i )
using ll = long long;
using P = pair<int , int>;
const int INF = INT_MAX ;

struct RSQ{
	int seg_len ;
    vector<int> seg;

    RSQ(int n) {
        // n より大きい最小の2の冪乗を計算
        seg_len = 1;
        while (seg_len < n) seg_len *= 2;
        seg.assign(2 * seg_len, 0);
    }

	void add(int id, int v){
		id += seg_len ;
		seg[id] += v ;
		while(id > 1){
			id /= 2 ;
			seg[id] = seg[id * 2] + seg[id * 2 + 1] ;
		}
	}

	int get_sum(int l, int r){
		l += seg_len ; r += seg_len ;
		int res = 0 ;
		while(l < r){
			if(l % 2 == 1){
				res += seg[l];
				l ++ ;
			}
            l /= 2 ;
			if(r % 2 == 1){
				res += seg[r - 1] ;
				r -- ;
			}
			r /= 2 ;
		}
		return res ;
	}
};


struct RAQ{
	int seg_len ;
    vector<int> seg;

    RAQ(int n) {
        // n より大きい最小の2の冪乗を計算
        seg_len = 1;
        while (seg_len < n) seg_len *= 2;
        seg.assign(2 * seg_len, 0);
    }

	int get(int id){
		id += seg_len ;
		int res = seg[id] ;
		while(true){
			id /= 2 ;
			if(id == 0) break ;
			res += seg[id] ;
		}
		return res ;
	}

	void add(int l, int r, int x){
		l += seg_len ; r += seg_len ;
		while(l < r){
			if(l % 2 == 1){
				seg[l] += x ;
				l ++ ;
			}
            l /= 2 ;
			if(r % 2 == 1){
				seg[r - 1] += x ;
				r -- ;
			}
			r /= 2 ;
		}
	}
};

struct RUQ {
    int seg_len;
    vector<P> seg;

    RUQ(int n) {
        // n より大きい最小の2の冪乗を計算
        seg_len = 1;
        while (seg_len < n) seg_len *= 2;
        seg.assign(2 * seg_len, P(INT32_MAX, 0));
    }

    int get(int id) {
        id += seg_len;
        P res = seg[id];
        while (id > 0) {
            if (seg[id].second > res.second) {
                res = seg[id];
            }
            id /= 2;
        }
        return res.first;
    }

    void update(int l, int r, int x, int t, int k = 1, int a = 0, int b = -1) {
        if (b == -1) b = seg_len;
        if (r <= a || b <= l) return;
        if (l <= a && b <= r) {
            seg[k] = P(x, t);
            return;
        }
        int m = (a + b) / 2;
        update(l, r, x, t, 2 * k, a, m);
        update(l, r, x, t, 2 * k + 1, m, b);
    }
};

struct RMQ {
    int seg_len;
    vector<int> seg;

    RMQ(int n) {
        // n より大きい最小の2の冪乗を計算
        seg_len = 1;
        while (seg_len < n) seg_len *= 2;
        seg.assign(2 * seg_len, INF);
    }

	void update(int id, int x){
		id += seg_len ;
		seg[id] = x ;
		while(id > 0){
			id /= 2 ;
			seg[id] = min(seg[id * 2], seg[id * 2 + 1]) ;
		}
	}

    int get(int l, int r, int k = 1, int a = 0, int b = -1) {
        if (b == -1) b = seg_len;
		if (r <= a || b <= l) return INF ;
        if (l <= a && b <= r) {
            return seg[k];
        }
        int m = (a + b) / 2;
        int res1 = get(l, r, 2 * k, a, m);
        int res2 = get(l, r, 2 * k + 1, m, b);
		return min(res1, res2) ;
    }
};

// インデックスは全て0スタートで、区間は全て半開半閉区間つまり[l, r)となることに注意せよ!!!!


int main(){
     int n, q ;
	 cin >> n >>q ;
	 RAQ seg(n) ;
	 rep(i, q){
		 int a, b, c, d ;
		 cin >> a ;
		 if(a == 0){
			 cin >> b >> c >> d ;
			 seg.add(b, c + 1, d);
		 }
		 if(a == 1){
			 cin >> b  ;
			 cout << seg.get(b) <<endl;
		 }
	 }
    return 0;
}

