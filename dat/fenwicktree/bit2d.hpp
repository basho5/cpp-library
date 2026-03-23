template<typename T>
struct BIT_2D {
    int H, W;  // それぞれ行数と列数
    vector<vector<T>> bit;  // BIT の内部配列。サイズは H x W
	// 各計算はo(logH * logW)
    // コンストラクタ: H行W列の 2次元 BIT を作る。
    // 内部は 0 で初期化される。
    BIT_2D(int H_=0, int W_=0) : H(H_), W(W_), bit(H, vector<T>(W)) {}
    // sum(i, j) は、座標 (0,0) から (i,j) までの累積和を返す。
    // 返す範囲は [0, i) x [0, j) の和となる。
    T sum(int i, int j) {
        assert(0 <= i && i <= H);
        assert(0 <= j && j <= W);
        T ans = 0;
        // 外側ループ：i を BIT で逆順に辿る
        for(; i > 0; i -= i & -i)
            // 内側ループ：j についても逆順に辿る
            for(int nj = j; nj > 0; nj -= nj & -nj)
                ans += bit[i-1][nj-1];
        return ans;
    }
    
    // add(i, j, a) は、座標 (i, j) に値 a を加算する操作
    // ここで i,j は 0-indexed で指定するが、内部処理のために i,j を 1-indexed に変換する
    void add(int i, int j, T a) {
        assert(0 <= i && i < H);
        assert(0 <= j && j < W);
        i++; j++; // 1-indexed に変換
        // BIT の更新は上方向・右方向に伝播していく
        for(; i <= H; i += i & -i)
            for(int nj = j; nj <= W; nj += nj & -nj)
                bit[i-1][nj-1] += a;
    }
};
