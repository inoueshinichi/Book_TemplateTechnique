#pragma once

#include <utility>
#include <cmath>

//////////////////////////////////////////////////////
// コンセプト・・・テンプレートパラメータに対する要件
//////////////////////////////////////////////////////

namespace Is
{
    struct is_less_than_comparable_impl 
    {
        template <class T, class U>
        static auto check(T*, U*) -> decltype(
            std::declval<T>() < std::declval<U>(), std::true_type());

        template <class T, class U>
        static auto check(...) -> std::false_type;
    };

    // 型Tと型Uがoperator<で比較可能か判定するメタ関数
    template <class T, class U>
    struct is_less_than_comparable : decltype(
        is_less_than_comparable_impl::check<T, U>(nullptr, nullptr))
    {};


    // コンセプトを適用するmix<T>
    template <class T>
    const T& min(const T& a, const T& b)
    {
        // 型Tに対する要件
        static_assert(is_less_than_comparable<T, T>::value, "T must be less than comparable");

        return a < b ? a : b;
    }
}


/////////////////////////
// コンセプトに基づく設計
/////////////////////////
// コンセプトの要件を満たさない型を要件を満たすように適用することができる

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

// // distance関数 ver1
// template <class Point>
// double distance(Point a, Point b)
// {
//     const Point d = a - b;
//     return std::sqrt(d.x() * d.x() + d.y() * d.y());
// }

/////////////////////////////////
// インターフェースを吸収する設計
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


// 中間インターフェースを介したdistance関数
template <class Point>
double distance(Point a, Point b)
{
    using traits = point_traits<Point>;
    const Point d = traits::subtract(a, b);
    return std::sqrt(traits::x(d) * traits::y(d) + traits::y(d) * traits::y(d));
}

///////////////////////////////////////////////////////////////////////////////////////
// インターフェースの異なる新たな点型を追加したい場合は、point_traitsクラスを特殊化する

// MyPointでpoint_traitsクラスを特殊化する
class MyPoint
{
    double x_ = 0;
    double y_ = 0;
public:
    MyPoint() = default;
    MyPoint(double x, double y)
        : x_(x), y_(y) {}
    
    double getX() const { return x_; }
    double getY() const { return y_; }
};

// point_traitsの特殊化
template <>
struct point_traits<MyPoint>
{
    static double x(const MyPoint& p) { return p.getX(); }
    static double y(const MyPoint& p) { return p.getY(); }

    static MyPoint subtract(const MyPoint& a, const MyPoint& b)
    {
        return MyPoint(a.getX() - b.getX(), a.getY() - b.getY());
    }
};

