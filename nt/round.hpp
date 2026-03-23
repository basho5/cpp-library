// 整数部の四捨五入（k>=0, k: 末尾から何桁目までを考慮するか。
// ここでは k=0 なら1の位, k=1 なら10の位, ... を丸める）
string round_n_integer(const string &s, int k) {
    int roundLen = k + 1; // 対象となる下位桁数
    int n = s.size();
    string prefix, r;
    if(n > roundLen) {
        prefix = s.substr(0, n - roundLen);
        r = s.substr(n - roundLen);
    } else {
        prefix = "";
        r = string(roundLen - n, '0') + s;
    }
    string T = "5" + string(k, '0'); // 丸めるための閾値
    if(r >= T) {
        // 繰り上げが必要
        if(prefix == "") {
            return "1" + string(roundLen, '0');
        } else {
            int carry = 1;
            for (int pos = prefix.size() - 1; pos >= 0 && carry; pos--) {
                int d = (prefix[pos] - '0') + carry;
                prefix[pos] = char('0' + (d % 10));
                carry = d / 10;
            }
            if(carry)
                prefix.insert(prefix.begin(), '1');
            return prefix + string(roundLen, '0');
        }
    } else {
        // 切り捨て
        if(prefix == "") return "0";
        return prefix + string(roundLen, '0');
    }
}
 
// 整数部の切り捨て（k>=0の場合）
string round_down_integer(const string &s, int k) {
    int roundLen = k + 1;
    int n = s.size();
    if(n > roundLen) {
        return s.substr(0, n - roundLen) + string(roundLen, '0');
    } else {
        return "0";
    }
}
 
// 少数の場合の四捨五入
// k < 0 のとき、d = -k が小数部の桁数
string round_n_decimal(const string &s, int k) {
    // s に小数点があると仮定
    int pos = s.find('.');
    string intPart = s.substr(0, pos);
    string fracPart = s.substr(pos + 1);
    if(k >= 0) {
        // 整数部に対して丸め（小数部は切り捨て）
        return round_n_integer(intPart, k);
    } else {
        int d = -k;  // 小数部で残す桁数
        // 小数部を十分な長さに調整
        if((int)fracPart.size() < d + 1) {
            fracPart.append(d + 1 - fracPart.size(), '0');
        }
        char rDigit = fracPart[d];  // 丸め判断に使う桁
        string kept = fracPart.substr(0, d);
 
        if(rDigit >= '5') {
            // kept を数値として+1（右から繰り上げ）
            int carry = 1;
            for (int i = d - 1; i >= 0 && carry; i--) {
                int digit = kept[i] - '0' + carry;
                kept[i] = char('0' + (digit % 10));
                carry = digit / 10;
            }
            if(carry) {
                // 小数部全体が繰り上がった場合、整数部に加算
                int i = intPart.size() - 1;
                carry = 1;
                string newInt = intPart;
                while(i >= 0 && carry) {
                    int digit = newInt[i] - '0' + carry;
                    newInt[i] = char('0' + (digit % 10));
                    carry = digit / 10;
                    i--;
                }
                if(carry)
                    newInt.insert(newInt.begin(), '1');
                intPart = newInt;
            }
        }
        // kept は常に d 桁になる（必要なら先頭に'0'が入っている）
        if(d > 0)
            return intPart + "." + kept;
        else
            return intPart;
    }
}
 
// 少数の場合の切り捨て
string round_down_decimal(const string &s, int k) {
    int pos = s.find('.');
    string intPart = s.substr(0, pos);
    string fracPart = s.substr(pos + 1);
    if(k >= 0) {
        // 整数部について切り捨て
        return round_down_integer(intPart, k);
    } else {
        int d = -k;
        if((int)fracPart.size() < d)
            fracPart.append(d - fracPart.size(), '0');
        else
            fracPart = fracPart.substr(0, d);
        return intPart + (d > 0 ? "." + fracPart : "");
    }
}
 

// 10^k の位を四捨五入(小数点以下は負の値)
string round_n(const string &s, int k) {
    if(s.find('.') == string::npos) {
        // 整数の場合
        if(k >= 0)
            return round_n_integer(s, k);
        else {
            // 整数で少数部の桁指定なら、整数部はそのままで小数部は 0 を付加
            return s + "." + string(-k, '0');
        }
    } else {
        return round_n_decimal(s, k);
    }
}
 
// 10^k の位を切り捨て(小数点以下は負の値)
string round_down(const string &s, int k) {
    if(s.find('.') == string::npos) {
        if(k >= 0)
            return round_down_integer(s, k);
        else {
            return s + "." + string(-k, '0');
        }
    } else {
        return round_down_decimal(s, k);
    }
}
