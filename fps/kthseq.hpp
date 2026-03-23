// 先頭K項 init と、係数 coeff (それぞれK個) を与えたとき、
// 漸化式 a_n = c_1 a_{n-1} + c_2 a_{n-2} + ... + c_K a_{n-K} (n>=K)
// の第 N 項 a_N (mod mod) を返す関数
// o(klogklogN)
mint kth_sequences(int K, ll N, const vector<mint>& init, const vector<mint>& coeff) {
    if(N < K) return init[N];
    // A(x) = sum_{i=0}^{K-1} init[i] x^i
    fps A(K);
    for (int i = 0; i < K; i++){
        A[i] = init[i];
    }
    // Q(x) = 1 - c_1 x - c_2 x^2 - ... - c_K x^K
    fps Q(K+1);
    Q[0] = 1;
    for (int i = 0; i < K; i++){
        // 係数 coeff[i] は c_{i+1} とみなす
        Q[i+1] = -coeff[i];
    }
    Q.normalize();
    fps P = A * Q;
    P.resize(K); // 長さ K まで打ち切る
    // Bostan–Mori 法により A(x) = P(x) / Q(x) の x^N の係数を計算
    mint ans = Q.bostanMori(N, P);
    return ans;
}
