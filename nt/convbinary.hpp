// 文字 c を数値に変換（'0'-'9' および 'A'-'Z' に対応）
int c2v(char c) {
    if (isdigit(c))
        return c - '0';
    return toupper(c) - 'A' + 10;
}

// 数値 v (0～35) を文字に変換（0-9, A-Z）
char v2c(int v) {
    if (v < 10)
        return '0' + v;
    return 'A' + (v - 10);
}

// s: 入力の数値文字列（英数字）、f: 元の進法、t: 変換先の進法
string conv(string s, int f, int t) {
    vector<int> d;
    for (char c : s) {
        d.push_back(c2v(c));
    }
    if (d.size() == 1 && d[0] == 0)
        return "0";
    string r = "";
    while (!d.empty()) {
        int c = 0;
        vector<int> nd;  
        for (int x : d) {
            int cur = c * f + x;
            int q = cur / t;
            c = cur % t;
            if (!nd.empty() || q != 0)
                nd.push_back(q);
        }
        r.push_back(v2c(c));
        d = nd;
    }
    reverse(r.begin(), r.end());
    return r;
}
