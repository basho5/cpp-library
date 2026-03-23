// Sieve of Eratosthenes
struct Sieve {
    int n;
    vector<int> f, primes;
    vector<int> cum; 

    Sieve(int n=1) : n(n), f(n+1, 0) {
        f[0] = f[1] = -1;
        for (ll i = 2; i <= n; ++i) {
            if (f[i]) continue; 
            primes.push_back(i);
            f[i] = i;
            for (ll j = i * i; j <= n; j += i) {
                if (!f[j]) f[j] = i;
            }
        }
    }
    
    // x が 2～n の範囲で素数なら true を返す
    bool is_prime(int x) const {
        if(x < 2 || x > n) return false;
        return f[x] == x;
    }
    
    // 累積配列 cum を構築する: 1～n までの素数の個数
    void build_cumulative() {
        cum.assign(n+1, 0);
        for (int i = 1; i <= n; i++) {
            cum[i] = cum[i-1] + (is_prime(i) ? 1 : 0);
        }
    }
    
    // 1～n までの素数の個数を返す (xが n を超えた場合は n までのもの)
    int cntp(int x) {
        if(x > n) x = n;
        if(cum.empty()) build_cumulative();
        return cum[x];
    }
    
    // l以上r以下の素数の個数を返す (1 <= l <= r <= n)
    int cntrange(int l, int r) {
        if(l < 1) l = 1;
        if(r > n) r = n;
        if(cum.empty()) build_cumulative();
        return cum[r] - cum[l-1];
    }
};
