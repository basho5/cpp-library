// 3次元点は tuple<T,T,T> として扱う
template<typename T>
bool cmpTriple(const tuple<T,T,T>& p, const tuple<T,T,T>& q) {
    if(get<0>(p) != get<0>(q)) return get<0>(p) < get<0>(q);
    if(get<1>(p) != get<1>(q)) return get<1>(p) < get<1>(q);
    return get<2>(p) < get<2>(q);
}

template<typename T>
struct PairCmp {
    bool operator()(const pair<T,T>& a, const pair<T,T>& b) const {
        return a.first < b.first;
    }
};

// 3次元LISの長さを求める関数
// 点集合 a は tuple<T,T,T> の vector．
template <typename T>
ll LIS3D(const vector<tuple<T,T,T>>& a, bool A = false) {
    int n = a.size();
    // ソート（x昇順，y昇順，z昇順）
    vector<tuple<T,T,T>> pts = a;
    sort(pts.begin(), pts.end(), cmpTriple<T>);

    // dp_sets[k] : set (ordered by y) of candidate (y,z) の集合，
    // すなわち，長さ k+1 の増加部分列の末尾候補．
    vector< set<pair<T,T>, PairCmp<T>> > dp_sets;
    dp_sets.resize(n);
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        T x = get<0>(pts[i]), y = get<1>(pts[i]), z = get<2>(pts[i]);
        int lo = -1, hi = ans - 1;
        while (lo != hi) {
            int mid = (lo + hi + 1) / 2;
            auto it = dp_sets[mid].lower_bound({y, z});
            bool canExtend = false;
            if (it != dp_sets[mid].begin()) {
                auto prevIt = prev(it);
                if (prevIt->second < z) canExtend = true;
            }
            if (canExtend) lo = mid;
            else hi = mid - 1;
        }
        int k = lo + 1; // 新たに延長する部分列の長さ = lo+1+1
        if (k >= ans) {
            dp_sets[k].insert({y, z});
            ans = k + 1;
        } else {
            auto& st = dp_sets[k];
            auto it = st.lower_bound({y, z});
            while(it != st.end() && it->second >= z)
                it = st.erase(it);
            st.insert({y, z});
        }
    }
    return ans;
}
