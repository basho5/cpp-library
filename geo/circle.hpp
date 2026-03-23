// Poly: 多角形を表すための、点の vector
template<typename T>
using Poly = vector<V<T>>;
 
// Circle: 円を表すテンプレート構造体
template<typename T>
struct Circle {
    V<T> o;
    T r;
    Circle(V<T> o = V<T>(0,0), T r = 0): o(o), r(r) {}
    
    // 2 つの円の交点を求める（内部計算は double で行い、結果は V<double> で返す）
    vector<V<double>> xp(const Circle<T>& c) const {
        vector<V<double>> res;
        // 中心間距離
        double d = (V<double>(o.x, o.y) - V<double>(c.o.x, c.o.y)).norm();
        if(d > (double)r + (double)c.r) return res;  // 離れている
        if(d + min((double)r, (double)c.r) < max((double)r, (double)c.r) + eps) return res; // 一方に内包
        double rcos = (d*d + (double)r*(double)r - (double)c.r*(double)c.r) / (2.0*d);
        double rsin = sqrt((double)r*(double)r - rcos*rcos);
        V<double> a = (V<double>(c.o.x, c.o.y) - V<double>(o.x, o.y)).normalize();
        res.push_back(V<double>(o.x, o.y) + V<double>(a.x * rcos - a.y * rsin, a.x * rsin + a.y * rcos));
        res.push_back(V<double>(o.x, o.y) + V<double>(a.x * rcos + a.y * rsin, -a.x * rsin + a.y * rcos));
        return res;
    }
    
    // 点 p が円の内部または境界上にあるかを判定（すべて整数演算）
    bool in(const V<T>& p) const {
        return (p - o).norm2() <= r * r;
    }
    // 2 つの円が交わる（または接する）か判定する（整数の二乗比較で）
    // 条件: (|r1 - r2|)^2 <= d^2 <= (r1 + r2)^2
    bool touch(const Circle<T>& c) const {
        T d2 = (o - c.o).norm2();
        T sum = r + c.r;
        T diff = (r >= c.r ? r - c.r : c.r - r);
        return (diff * diff <= d2 && d2 <= sum * sum);
    }
    
    // 2 つの円の間の距離を返す（円が重なっている場合は 0 を返す）
    double distCC(const Circle<T>& c) const {
        double d = (V<double>(o.x, o.y) - V<double>(c.o.x, c.o.y)).norm();
        return max(d - (double)r - (double)c.r, 0.0);
    }
};
