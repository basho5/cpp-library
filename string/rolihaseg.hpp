struct RollingHash {
    // 内部ノード：各ノードは、mod1, mod2 でのハッシュ値と区間の長さを保持
    struct Node {
        ll h1, h2;
        int len;
    };
    
    static const int base = 9973;
    static const ll mod1, mod2;
    
    string S;
    int n;
    
    vector<ll> power1, power2;
    static vector<ll>* power1_ptr;
    static vector<ll>* power2_ptr;
    
    static Node op(const Node &L, const Node &R) {
        Node res;
        res.h1 = (L.h1 * ((*power1_ptr)[R.len]) + R.h1) % mod1;
        res.h2 = (L.h2 * ((*power2_ptr)[R.len]) + R.h2) % mod2;
        res.len = L.len + R.len;
        return res;
    }
    static Node e() {
        return {0, 0, 0};
    }
	RollingHash(){}
	RollingHash(string a){init(a);}
    atcoder::segtree<Node, op, e> segF;
    atcoder::segtree<Node, op, e> segR;
    void init(const string &cs) {
        S = cs;
        n = S.size();
        power1.resize(n+1); power2.resize(n+1);
        power1[0] = 1; power2[0] = 1;
        for (int i = 0; i < n; i++){
            power1[i+1] = (power1[i] * base) % mod1;
            power2[i+1] = (power2[i] * base) % mod2;
        }
        power1_ptr = &power1;
        power2_ptr = &power2;
        
        vector<Node> initNodes(n);
        for (int i = 0; i < n; i++){
            ll val = (ll)S[i];
            initNodes[i] = {val, val, 1};
        }
        segF = atcoder::segtree<Node, op, e>(initNodes);
        
        string srev = S;
        reverse(srev.begin(), srev.end());
        vector<Node> initNodesR(n);
        for (int i = 0; i < n; i++){
            ll val = (ll)srev[i];
            initNodesR[i] = {val, val, 1};
        }
        segR = atcoder::segtree<Node, op, e>(initNodesR);
    }
    
    // update: S の pos 番目 (0-indexed) の文字を c に更新する。前方と逆順両方を更新。
    void update(int pos, char c) {
        S[pos] = c;
        Node nd = {(ll)c, (ll)c, 1};
        segF.set(pos, nd);
        segR.set(n-1-pos, nd);
    }
    
    // get: 区間 [l, r) (0-indexed) のハッシュ値を返す。id = 0 なら mod1, id = 1 なら mod2
    ll get(int l, int r, int id = 0) const {
        Node nd = segF.prod(l, r);
        return (id == 0 ? nd.h1 : nd.h2);
    }
    
    // getLCP: S[a:] と S[b:] の LCP 長を返す（単純な二分探索）
    int getLCP(int a, int b) const {
        int len = min(n - a, n - b);
        int low = -1, high = len + 1;
        while (high - low > 1) {
            int mid = (low + high) / 2;
            if (segF.prod(a, a+mid).h1 == segF.prod(b, b+mid).h1 &&
                segF.prod(a, a+mid).h2 == segF.prod(b, b+mid).h2)
                low = mid;
            else
                high = mid;
        }
        return low;
    }
    
    // palindrome: S の [L, R] (1-indexed、両端含む) の部分文字列が回文なら true、そうでなければ false を返す。
    bool palindrome(int L, int R) const {
        int l = L - 1, r = R; // [l, r) が対象
        Node f = segF.prod(l, r);
        // 逆順側では、対応する区間は [n - r, n - l)
        Node rev = segR.prod(n - r, n - l);
        return (f.h1 == rev.h1 && f.h2 == rev.h2);
    }
};
const ll RollingHash::mod1 = 999999937LL;
const ll RollingHash::mod2 = 1000000007LL;
vector<ll>* RollingHash::power1_ptr = nullptr;
vector<ll>* RollingHash::power2_ptr = nullptr;
