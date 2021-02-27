#include "concept.hpp"

#include <iostream>

int main (int argc, char** argv)
{
    /////////////
    // コンセプト
    /////////////
    int n = Is::min(1, 2);
    std::cout << n << std::endl;

    struct X {};
    // X x = Is::min(X(), X());

    /////////////////////////
    // コンセプトに基づく設計
    /////////////////////////
    // 点とみなせるあらゆる型に対するアルゴリズムを定義できるようになった

    point a(0.0, 0.0);
    point b(3.0, 3.0);
    double d = distance(a, b);
    std::cout << d << std::endl;

    MyPoint a_my(0.0, 0.0);
    MyPoint b_my(3.0, 3.0);
    double d_my = distance(a_my, b_my);
    std::cout << d_my << std::endl;

    return 0;
}