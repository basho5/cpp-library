// Wavelet Matrix (Preprocess: O(N log N), Query: O(log N))
// Bit Vector (for 64-bit non-negative integer)
struct BitVector {
    // block: bit vector
    // count: the number of 1 within each block
    unsigned int n, zeros;
    vector<unsigned long long> block;
    vector<unsigned int> count;
    
    // constructor
    BitVector() {}
    BitVector(const unsigned int num) {
        resize(num);
    }
    void resize(const unsigned int num) {
        n = num;
        block.assign(((num + 1) >> 6) + 1, 0);
        count.assign(block.size(), 0);
    }
    
    // set val(0 or 1) onto i-th bit, get i-th bit of val(0 or 1)
    void set(const unsigned int i, const unsigned long long val = 1LL) {
        assert((i >> 6) < block.size());
        block[i >> 6] |= (val << (i & 63));
    }
    unsigned int get(const unsigned int i) const {
        assert((i >> 6) < block.size());
        return (const unsigned int)(block[i >> 6] >> (i & 63)) & 1;
    }
    void build() {
        for (unsigned int i = 1; i < block.size(); i++) {
            count[i] = count[i - 1] + __builtin_popcountll(block[i - 1]);
        }
        zeros = rank0(n);
    }
    
    // the number of 1 in [0, i)
    unsigned int rank1(const unsigned int i) const {
        assert((i >> 6) < count.size());
        assert((i >> 6) < block.size());
        return count[i >> 6] +
        __builtin_popcountll(block[i >> 6] & ((1ULL << (i & 63)) - 1ULL));
    }
    // the number of 1 in [i, j)
    unsigned int rank1(const unsigned int i, const unsigned int j) const {
        return rank1(j) - rank1(i);
    }
    // the number of 0 in [0, i)
    unsigned int rank0(const unsigned int i) const {
        return i - rank1(i);
    }
    // the number of 0 in [i, j)
    unsigned int rank0(const unsigned int i, const unsigned int j) const {
        return rank0(j) - rank0(i);
    }
    // the number of 0 in [0, n)
    unsigned int rank0() const {
        return zeros;
    }
};

// Wavelet Matrix (must vec[i] >= 0)
template<class T> struct WaveletMatrix {
    // inner data
    unsigned int n, height;
    vector<T> v;
    vector<BitVector> bv;
    vector<vector<long long>> sum;

    // constructor (sigma: the number of characters)
    WaveletMatrix() : n(0) {}
    WaveletMatrix(unsigned int n) : n(n), v(n) {}
    WaveletMatrix(const vector<T> &vec) : n(vec.size()), v(vec) {
        build();
    }
    void add(const T &val) {
        assert(v >= 0);
        v.push_back(v);
        n = v.size();
    }
    void set(unsigned int i, const T &val) {
        assert(i >= 0 && i < n && val >= 0);
        v[i] = val;
    }
    void build() {
        assert(n == (int)v.size());
        T mv = 1;
        for (int i = 0; i < n; ++i) mv = max(mv, v[i]);
        for (height = 1; mv != 0; mv >>= 1) ++height;
        vector<int> left(n), right(n), ord(n);
        iota(ord.begin(), ord.end(), 0);
        bv.assign(height, BitVector(n));
        sum.assign(height + 1, vector<long long>(n + 1, 0));
        for (int h = height - 1; h >= 0; --h) {
            int l = 0, r = 0;
            for (int i = 0; i < n; ++i) {
                if ((v[ord[i]] >> h) & 1) {
                    bv[h].set(i);
                    right[r++] = ord[i];
                } else {
                    left[l++] = ord[i];
                }
            }
            bv[h].build();
            ord.swap(left);
            for (int i = 0; i < r; ++i) ord[i + l] = right[i];
            for (int i = 0; i < n; ++i) sum[h][i + 1] = sum[h][i] + v[ord[i]];
        }
    }
    
    // access v[k]
    T access(int i) {
        T res = 0;
        for (int h = height - 1; h >= 0; --h) {
            int i0 = bv[h].rank0(i);
            if (bv[h].get(i)) {
                i += bv[h].rank0() - i0;
                res |= T(1) << h;
            } else {
                i = i0;
            }
        }
        return res;
    }
    T operator [] (int i) {
        return access(i);
    }
    
    // count "i" s.t. v[i] = val, i \in [l, r)
    int rank(int l, int r, const T &val) {
        assert(0 <= l && l <= r && r <= n);
        for (int h = height - 1; h >= 0; --h) {
            int l0 = bv[h].rank0(l), r0 = bv[h].rank0(r);
            if ((val >> h) & 1) {
                l += bv[h].rank0() - l0;
                r += bv[h].rank0() - r0;
            } else {
                l = l0;
                r = r0;
            }
        }
        return r - l;
    }
    
    // count "i" s.t. v[i] \in [lower, upper), i \in [l, r)
    int range_freq(int l, int r, const T &upper) {
        assert(0 <= l && l <= r && r <= n);
        int res = 0;
        for (int h = height - 1; h >= 0; --h) {
            int l0 = bv[h].rank0(l), r0 = bv[h].rank0(r);
            if ((upper >> h) & 1) {
                l += bv[h].rank0() - l0;
                r += bv[h].rank0() - r0;
                res += r0 - l0;
            } else {
                l = l0;
                r = r0;
            }
        }
        return res;
    }
    int range_freq(int l, int r, const T &lower, const T &upper) {
        return range_freq(l, r, upper) - range_freq(l, r, lower);
    }
    
    // the k-th (0-indexed) smallest value in [l, r)
    T k_th_smallest(int l, int r, int k) {
        assert(0 <= l && l <= r && r <= n);
        T res = 0;
        for (int h = height - 1; h >= 0; --h) {
            int l0 = bv[h].rank0(l), r0 = bv[h].rank0(r);
            if (r0 - l0 <= k) {
                l += bv[h].rank0() - l0;
                r += bv[h].rank0() - r0;
                k -= r0 - l0;
                res |= T(1) << h;
            } else {
                l = l0;
                r = r0;
            }
        }
        return res;
    }
    
    // the k-th (0-indexed) largest value in [l, r)
    T k_th_largest(int l, int r, int k) {
        assert(0 <= l && l <= r && r <= n);
       return k_th_smallest(l, r, r - l - k - 1);
    }
    
    // the sum of the top-k sum in [l, r)
	// [l, r)内の最小のk個の値の総和
    T top_k_sum(int l, int r, int k) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return 0;
        T res = 0, val = 0;
        for (int h = height - 1; h >= 0; --h) {
            int l0 = bv[h].rank0(l), r0 = bv[h].rank0(r);
            if (r0 - l0 <= k) {
                l += bv[h].rank0() - l0;
                r += bv[h].rank0() - r0;
                k -= r0 - l0;
                val |= T(1) << h;
                res += sum[h][r0] - sum[h][l0];
            } else {
                l = l0;
                r = r0;
            }
        }
        res += val * k;
        return res;
    }
    
    // the max value (< val) in [l, r)
    T prev_value(int l, int r, T val) {
        assert(0 <= l && l <= r && r <= n);
        int num = range_freq(l, r, 0, val);
        if (num == 0) return T(-1);
        else return k_th_smallest(num - 1, l, r);
    }
    
    // the min value (>= val) in [l, r)
    T next_value(int l, int r, T val) {
        assert(0 <= l && l <= r && r <= n);
        int num = range_freq(l, r, 0, val);
        if (num == r - l) return T(-1);
        else return k_th_smallest(num, l, r);
    }
};
