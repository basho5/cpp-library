bool equal(double a, double b) { return abs(a-b) < eps;}
// ここでは eps は浮動小数点型用の許容誤差。
// テンプレート型 T が整数の場合は使わず、T による比較は厳密な比較になります。
// 2次元の点（またはベクトル）を表すテンプレート構造体
template<typename T>
struct V {
    T x, y;
    V(T x = 0, T y = 0): x(x), y(y) {}
    
    // 基本の四則演算
    V operator+(const V& t) const { return V(x + t.x, y + t.y); }
    V operator-(const V& t) const { return V(x - t.x, y - t.y); }
    V operator*(T t) const { return V(x * t, y * t); }
    V operator/(T t) const { return V(x / t, y / t); }
    
    // 複素数的な乗算・除算（実数 T で動作）
    // (x, y) を複素数 x+iy とみなす
    V operator*(const V& t) const { return V(x * t.x - y * t.y, x * t.y + y * t.x); }
    // 除算は、掛ける相手の複素共役で割る形
    V operator/(const V& t) const { 
        // 注意: t.norm2() は T 型（整数の場合もある）ですが、除算には double にキャスト
        return *this * V(t.x, -t.y) / (double)t.norm2(); 
    }
    
    // 複合代入演算子
    V& operator+=(const V& t) { x += t.x; y += t.y; return *this; }
    V& operator-=(const V& t) { x -= t.x; y -= t.y; return *this; }
    V& operator*=(T t) { x *= t; y *= t; return *this; }
    V& operator/=(T t) { x /= t; y /= t; return *this; }
    V& operator*=(const V& t) { return *this = *this * t; }
    V& operator/=(const V& t) { return *this = *this / t; }
    
    // 内積と外積
    T dot(const V& t) const { return x * t.x + y * t.y; }
    T cross(const V& t) const { return x * t.y - y * t.x; }
    
    // ノルム関連：norm2 は T 型、norm は double 型で返す
    T norm2() const { return x * x + y * y; }
    double norm() const { return sqrt((double)norm2()); }
	double dist(V x, V y){return (x-y).norm() ;} 
	T dist2(V x, V y){return (x-y).norm2() ;} 
    // 反転（符号反転）
    V rev() const { return V(-x, -y); }
    
    // 正規化（単位ベクトル化）; 結果は double 型のベクトルに変換して返す
    V<double> normalize() const { 
        double n = norm();
        return V<double>(x / n, y / n); 
    }
    
    // 90度回転（反時計回り）
    V rotate90() const { return V(-y, x); }
    
    // 点 a を中心に rad ラジアンだけ回転させる
    V rotate(const V& a, double rad) const {
        return V(a.x + cos(rad) * (x - a.x) - sin(rad) * (y - a.y),
                 a.y + sin(rad) * (x - a.x) + cos(rad) * (y - a.y));
    }
    
    // 比較演算子（T が浮動小数点の場合は eps を用いて判定）
    bool operator<(const V& a) const { 
        if constexpr (is_floating_point<T>::value)
            return (fabs((double)x - (double)a.x) > eps ? x < a.x : y < a.y);
        else
            return (x == a.x ? y < a.y : x < a.x);
    }
    bool operator==(const V& a) const { 
        if constexpr (is_floating_point<T>::value)
            return (fabs((double)x - (double)a.x) < eps && fabs((double)y - (double)a.y) < eps);
        else
            return (x == a.x && y == a.y);
    }
};
template<typename T>
istream& operator>>(istream& is, V<T>& v){is >> v.x >> v.y; return is;}
template<typename T>
ostream& operator<<(ostream& os, const V<T>& v) {os << v.x << "," << v.y;return os;}
 
template<typename T > 
T dist(V<T> x, V<T> y){return (x-y).norm2() ;} 
