#include "concept_overload.hpp"

#include <iostream>

int main(int argc, char** argv)
{
    /////////////////////////////////
    // コンセプトによるオーバーロード
    /////////////////////////////////

    // 1. 様々なAPIで実装されている点を点というコンセプトでAPIの差を吸収する
    // 2. 中間インターフェースであるコンセプトの種類を組み合わせた関数を作成する(タグディスパッチorSFINAEによるenable_ifでオーバーロード)

    // 点とみなせるあらゆる型に対するアルゴリズムを定義できるようになった
    // 他の図形との組み合わせで、アルゴリズムをオーバーロードできるようになった

    point p1(0.0, 0.0);
    point p2(3.0, 3.0);
    line_segment line(point(2.0, 2.0), point(3.0, 3.0)); // c++17以降はクラステンプレートの型推論ができる.

    // 点と点
    double d1 = distance(p1, p2);
    std::cout << d1 << std::endl;

    // 点と線分
    point p3(2.0, 3.0);
    double d2 = distance(p3, line);
    std::cout << d2 << std::endl;

    return 0;
}