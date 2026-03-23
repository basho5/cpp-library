// ----- 分割統治法による有理関数の和の構成 -----
//
// 各項は 1/(1-A_i*x) で、分子は 1、分母は (1 - A_i*x) となる。
// これらを分割統治法で合成し、最終的に S(x) = P(x)/Q(x) の形にまとめる。
pair<fps, fps> rational_sum(const vector<mint>& A, int L, int R, int deg) {
    if (R - L == 1) {
        // 単一項: 分子は 1, 分母は 1 - A[L]*x
        fps Q = {mint(1), mint(-A[L])};
        fps P = {mint(1)};
        return {P, Q};
    }
    int mid = (L + R) / 2;
    auto left = rational_sum(A, L, mid, deg);
    auto right = rational_sum(A, mid, R, deg);
    // 合成: 2 つの有理関数 P1/Q1 と P2/Q2 の和は
    // (P1*Q2 + P2*Q1) / (Q1*Q2)
    fps P = left.first * right.second + right.first * left.second;
    fps Q = left.second * right.second;
    if ((int)P.size() > deg) P.resize(deg);
    if ((int)Q.size() > deg) Q.resize(deg);
    return {P, Q};
}

// ----- 1/(1-A_i*x) の和の展開を求める関数 -----
//
// 入力: A: 各項の A_i を格納した vector<mint>
//        N: 求める次数（0 次から N 次まで）
// 出力: S(x)=∑_{i=1}^{M} 1/(1-A_i*x) の展開（0 次から N 次まで）
fps compute_series_sum(const vector<mint>& A, int N) {
    int deg = N + 1;
    auto rp = rational_sum(A, 0, A.size(), deg);
    fps P = rp.first, Q = rp.second;
    // Q(x) の逆元を deg 次まで計算し、S(x)=P(x)/Q(x) とする
    fps invQ = Q.inv(deg);
    fps S = P * invQ;
    S.resize(deg);
    return S;
}
