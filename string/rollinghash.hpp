struct RollingHash {
    const int base = 9973;
    const vector<int> mod = {999999937LL, 1000000007LL,998244353LL};
    string S;
    vector<long long> hash[3], power[3];

    // construct
    RollingHash(){}
    RollingHash(const string &cs) { init(cs); }
    void init(const string &cs) {
        S = cs;
        int n = (int)S.size();
        for (int iter = 0; iter < mod.size() ; ++iter) {
            hash[iter].assign(n+1, 0);
            power[iter].assign(n+1, 1);
            for (int i = 0; i < n; ++i) {
                hash[iter][i+1] = (hash[iter][i] * base + S[i]) % mod[iter];
                power[iter][i+1] = power[iter][i] * base % mod[iter];
            }
        }
    }
    // get hash of S[left:right]　半開半閉区間であることに注意
    inline long long get(int l, int r, int id = 0) const {
        long long res = hash[id][r] - hash[id][l] * power[id][r-l] % mod[id];
        if (res < 0) res += mod[id];
        return res;
    }
    // get lcp of S[a:] and S[b:]
    inline int getLCP(int a, int b) const {
        int len = min((int)S.size()-a, (int)S.size()-b);
        int low = -1, high = len + 1;
        while (high - low > 1) {
            int mid = (low + high) / 2;
            if (get(a, a+mid, 0) != get(b, b+mid, 0)) high = mid;
            else if (get(a, a+mid, 1) != get(b, b+mid, 1)) high = mid;
            else low = mid;
        }
        return low;
    }
    // get lcp of S[a:] and T[b:]
    inline int getLCP(const RollingHash &t, int a, int b) const {
        int len = min((int)S.size()-a, (int)S.size()-b);
        int low = -1, high = len + 1;
        while (high - low > 1) {
            int mid = (low + high) / 2;
            if (get(a, a+mid, 0) != t.get(b, b+mid, 0)) high = mid;
            else if (get(a, a+mid, 1) != t.get(b, b+mid, 1)) high = mid;
            else low = mid;
        }
        return low;
    }
};
inline ll convert(ll h0, ll h1) {
    return h0*1000000007LL+h1;
}
