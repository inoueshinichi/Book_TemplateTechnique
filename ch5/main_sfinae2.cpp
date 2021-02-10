#include "sfinae2.hpp"

#include <iostream>

int main(int argc, char** argv)
{
    // クラスかどうか
    struct X {};
    static_assert(is_class_v<X>, "Xはクラス");
    // static_assert(is_class_v<int>, "intはクラスでない");

    // 代入可能かどうか
    struct A {
        A& operator=(const A&) = delete;
    };
    struct B {};
    static_assert(!is_assignable_v<A>, "Aは代入不可能");
    // static_assert(is_assignable_v<B>, "Bは代入可能");

    // 加算可能かどうか
    struct Y {};
    struct Z {
         Z operator+(const Z&) { return Z(); }
    };
   

    std::cout << std::boolalpha;
    std::cout << is_addable_v<Y, Y> << std::endl;
    std::cout << is_addable_v<Z, Z> << std::endl;
    std::cout << is_addable_v<double, int> << std::endl;

    std::cout << "finish" << std::endl;
    return 0;
}