// BIT を利用して、集合の順序統計量 (Order Statistic) を管理する構造体
// 使用メモリは O(N)
struct setbit {
    // 値の範囲は 1 から N までを想定
    int N;
    BIT<int> bit;
    
    setbit(int N) : N(N), bit(N) {}
    
    // 集合に要素 a を追加する (a 番目を 1 にする)
    // ここで a は 1-indexed の値として受け取り、内部では 0-indexed に変換して扱う
    void insert(int a) {
        bit.add(a - 1, 1);
    }
    
    // 集合から要素 a を削除する (a 番目の値を 1 から 0 にする)
    void erase(int a) {
        bit.add(a - 1, -1);
    }
    
    // 要素 a が集合内で何番目に小さいか (0-indexed)
    // つまり、a より小さい要素の個数を返す
    int index(int a) {
        // a は 1-indexed のため、a - 1 までの和を求める
        return bit.sum(a - 1);
    }
    
    // w 番目に小さい要素は何か (w は 0-indexed)
    int find_kth(int w) {
        // BIT.lower_bound は「[0, i) の累積和が w+1 以上となる最小の i (0-indexed)」を返す
        return bit.lower_bound(w + 1);
    }
    
    // operator[] をオーバーロードして、0-indexed の順序統計量アクセスを可能にする
    int operator[](int w) const {
        // const_cast を使って const 版でも find_kth を呼び出す
        return const_cast<setbit&>(*this).find_kth(w);
    }
};
