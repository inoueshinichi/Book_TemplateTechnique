#pragma onece

#include <iostream>

template <typename T>
class Point
{
    T x_;
    T y_;
public:
    Point(T x = T(), T y = T())
        : x_(x), y_(y) {}

    Point(const Point& pt)
        : x_(pt.x_), y_(pt.y_) {}
    
    void print(std::ostream& s) const
    {
        s << "(" << x_ << "," << y_ << ")" << std::endl;
    }

    // コンストラクタテンプレート
    template <typename U>
    Point(const Point<U>& r) 
        : x_(r.x_), y_(r.y_) {}

private:
    template<typename> friend class Point;
};