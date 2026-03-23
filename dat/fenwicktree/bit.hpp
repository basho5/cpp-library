template<typename T>  // 0-indexed
struct BIT {
    int n;
    std::vector<T> bit;
    BIT(int N = 0) : n(N), bit(N) {}

    // [0, i) の和を返す（iは 0 <= i <= n）
    T sum(int i) {
        assert(0 <= i && i <= n);
        T res = 0;
        for (; i > 0; i -= i & -i)
            res += bit[i - 1];
        return res;
    }

    // [l, r) の和を返す（0 <= l <= r <= n）
    T sum(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        return sum(r) - sum(l);
    }

    // i 番目（0-indexed）の要素に a を加算する
    void add(int i, T a) {
        assert(0 <= i && i < n);
        // BIT内部は1-indexedの考え方なので i+1 から更新
        for (++i; i <= n; i += i & -i)
            bit[i - 1] += a;
    }

    // lower_bound:
    // 「[0, i) までの累積和が k 以上となる最小の i」を返す
    // ただし、k > sum(n) の場合は n を返す
    int lower_bound(T k) {
        if (k <= 0)
            return 0;
        if (k > sum(n))
            return n;
        int idx = 0;
        int bit_mask = 1;
        while (bit_mask < n)
            bit_mask <<= 1;
        for (; bit_mask; bit_mask >>= 1) {
            int next = idx + bit_mask;
            if (next <= n && bit[next - 1] < k) {
                k -= bit[next - 1];
                idx = next;
            }
        }
        return idx;
    }
};
