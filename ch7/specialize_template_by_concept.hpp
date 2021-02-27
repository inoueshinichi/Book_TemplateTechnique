#pragma once

#include <cmath>
#include <map>
#include <type_traits>

////////////////////////////////////////
// コンセプトでテンプレートを特殊化する
////////////////////////////////////////
// 「Geo」ライブラリが点型とみなすあらゆる型を、本章で作ってきた
// 自分たちの計算幾何ライブラリでも点型と認識させ、distance()関数でつかえるようにする

// [Geo]ライブラリ
// 点型 geo::point, std::pair<double, double>
namespace geo
{
    template <class T>
    struct is_point_category {
        static constexpr bool value = false;
    };

    template <class T>
    struct point_traits {
        static double getX(const T& p) { return p.getX(); }
        static double getY(const T& p) { return p.getY(); }
        static T subtract(const T& a, const T& b)
        {
            return T(a.getX() - b.getX(), a.getY() - b.getY());
        }
    };

    class point {
        double x_{0};
        double y_{0};
    public:
        point() = default;
        point(double x, double y)
            : x_(x), y_(y) {}
        
        double getX() const { return x_; }
        double getY() const { return y_; }
    };
    
    // [Geo]ライブラリが点型とみなす条件
    template <>
    struct is_point_category<point> {
        static constexpr bool value = true;
    };

    template <>
    struct point_traits<std::pair<double, double>> {
        using point_type = std::pair<double, double>;

        static double getX(const point_type& p) {
            return p.first;
        }

        static double getY(const point_type& p) {
            return p.second;
        }

        static point_type subtract (const point_type& a,
                                    const point_type& b)
        {
            return std::make_pair(a.first - b.first, a.second - b.second);
        }
    };

    // [Geo]ライブラリが点型とみなす条件
    template <>
    struct is_point_category<std::pair<double, double>> {
        static constexpr bool value = true;
    };
} // namespace geo


/////////////////////////////////////////////////////////////////////////////////
// 自分たちの計算幾何ライブラリ
/////////////////////////////////////////////////////////////////////////////////
class point
{
    double x_ = 0;
    double y_ = 0;
public:
    point() = default;
    point(double x, double y)
        : x_(x), y_(y) {}

    // それぞれの座標を取得する
    double x() const { return x_; }
    double y() const { return y_; }
};

// pointの減算
point operator-(const point& a, const point& b)
{
    return point(a.x() - b.x(), a.y() - b.y());
}

// 中間インターフェース for pointクラス
template <class T, class Enable = void> // Enableはダミーパラメータ
struct point_traits {
    static double x(const T& p) { return p.x(); }
    static double y(const T& p) { return p.y(); }
    static T subtract(const T& a, const T& b)
    {
        return T(a.x() - b.x(), a.y() - b.y());
    }
};

template <class Point>
class line_segment 
{
    Point p1_;
    Point p2_;
public:
    using point_type = Point;

    line_segment() = default;
    line_segment(const Point& p1, const Point& p2)
        : p1_(p1), p2_(p2) {}

    const Point& p1() const { return p1_; }
    const Point& p2() const { return p2_; }
};

template <class T>
struct line_segment_traits
{
    using point_type = typename T::point_type;

    static const point_type& p1(const T& line) { return line.p1(); }
    static const point_type& p2(const T& line) { return line.p2(); }
};

struct point_category {};
struct line_segment_category {};

// 宣言だけのプライマリーテンプレート
template <class T, class Enable = void> // Enableはダミーパラメータ
struct get_geometry_category; 

// get_geometry_categoryを特殊化
template <>
struct get_geometry_category<point> {
    using type = point_category;
};

template <class Point>
struct get_geometry_category<line_segment<Point>> {
    using type = line_segment_category;
};

// 点と点のdistance_impl関数
template <class Point>
double distance_impl(Point a, Point b, point_category, point_category)
{
    using traits = point_traits<Point>;
    const Point d = traits::subtract(a, b);
    return std::sqrt(traits::x(d) * traits::x(d) + traits::y(d) * traits::y(d));
}

// 点と線分のdistance_impl関数
template <class Point, class LineSegment>
double distance_impl(Point a, LineSegment b, point_category, line_segment_category)
{
    using p_traits = point_traits<Point>;
    using ls_traits = line_segment_traits<LineSegment>;
    Point p1_b = ls_traits::p1(b);
    Point p2_b = ls_traits::p2(b);
    Point vec_a_to_p = p_traits::subtract(a, p1_b);
    Point vec_a_to_b = p_traits::subtract(p2_b, p1_b);
    double norm_a_to_p = distance(a, p1_b);
    double norm_a_to_b = distance(p2_b, p1_b);
    double naizeki = p_traits::x(vec_a_to_p) * p_traits::x(vec_a_to_b) + p_traits::y(vec_a_to_p) * p_traits::y(vec_a_to_b);
    double angle = std::acos(naizeki / (norm_a_to_p * norm_a_to_b));
    return norm_a_to_p * std::sin(angle);
}

// 線分と点のdistance_impl関数
template <class LineSegment, class Point>
double distance_impl(LineSegment a, Point b, line_segment_category, point_category)
{
    return distance(b, a);
}


// distance: 特殊化したdistance_implに処理を転送する
template <class Geometry_1, class Geometry_2>
double distance(Geometry_1 a, Geometry_2 b)
{
    return distance_impl(a, b,
                         typename get_geometry_category<Geometry_1>::type(), // type型のインスタンス生成している
                         typename get_geometry_category<Geometry_2>::type());
}


// 目標：「Geoライブラリが点型とみなすあらゆる型を私達のライブラリでも点型とみなす」
// 方法：get::is_point_categoryメタ関数がtrueを返すあらゆる型に対して、get_geometry_categoryメタ関数と
// point_traintsクラスを特殊化する必要がある.

// template <class T>
// struct get_geometry_category<typename std::enable_if<geo::is_point_category<T>::value, T>::type> // 部分特殊化の際にTがstd::enable_ifを介した間接的な使用になるのでエラー
// {
//     using type = point_category; // 自分たちが点型とみなすタグ
// };
// 解決方法：get_geometry_category, point_traitsにダミーテンプレートパラメータを追加する.


// 部分特殊化の際に型Tを直接利用している。std::enable_ifはダミパラメータEnable = voidに充てがう.
template <class T>
struct get_geometry_category<T, typename std::enable_if<geo::is_point_category<T>::value, void>::type>
{
    using type = point_category; // 自分たちが点型とみなすタグ
};


template <class T>
struct point_traits<T, typename std::enable_if<geo::is_point_category<T>::value, void>::type>
{
    static double x(const T& p) {
        return geo::point_traits<T>::getX(p);
    }

    static double y(const T& p) {
        return geo::point_traits<T>::getY(p);
    }

    static T subtract(const T& a, const T& b) {
        return geo::point_traits<T>::subtract(a, b);
    }
};

