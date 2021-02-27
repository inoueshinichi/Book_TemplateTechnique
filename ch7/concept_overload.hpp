#pragma once

#include <cmath>

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
template <class T>
struct point_traits {
    static double x(const T& p) { return p.x(); }
    static double y(const T& p) { return p.y(); }
    static T subtract(const T& a, const T& b)
    {
        return T(a.x() - b.x(), a.y() - b.y());
    }
};

/////////////////////////////////
// コンセプトによるオーバーロード
/////////////////////////////////
// distance(a, b)という関数があるとき、
// a, bが異なる型カテゴリでも扱えるようにする

/**
 * @brief こんな感じ
 * 
 * // 点と点
 * templaet <class Point>
 * double distance(Point a, Point b);
 * 
 * // 点と線分
 * template <class Point, class LineSegment>
 * double distance(Point a, LineSegment b);
 * 
 * // 線分と点
 * double distance(LineSegment a, Point b);
 * 
 * // 線分と線分
 * double distance(LineSegment a, LineSegment b);
 */

// 実現方法 -> タグディスパッチもしくはSFINEによるenable_ifを使用する

////////////
// 事前準備
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

////////////////////////////////////////////////////
// 型がどの分類に属するか判定/取得するためのメタ関数
struct point_category {};
struct line_segment_category {};

// 宣言だけのプライマリーテンプレート
template <class T>
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

//------------------------------------------------------
// distance関数の実装

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


