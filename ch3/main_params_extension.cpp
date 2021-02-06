#include "params_extension.hpp"

#include <iostream>


int main(int argc, char** argv)
{
    using namespace Is;

    // Plain + Bold
    Bold<Plain> bold;
    string s1 = bold.convert("Hello world.");
    std::cout << s1 << std::endl;

    // Plain + Italic
    Italic<Plain> italic;
    string s2 = italic.convert("Hello world.");
    std::cout << s2 << std::endl;

    // Plain + Bold + Italic
    Italic<Bold<Plain>> bi;
    string s3 = bi.convert("Hello world.");
    std::cout << s3 << std::endl;

    /////////////////////////////
    // 基本クラスのメンバ関数をvirtualに

    VirtualPlain p;
    VirtualBold<> b;
    VirtualItalic<> i;
    VirtualSize<VirtualBold<VirtualItalic<>>> sbi(5);
    VirtualItalic<VirtualSize<>> si(3);

    VirtualPlain* converters[5] = { &p, &b, &i, &sbi, &si };
    for (auto* c : converters)
    {
        std::cout << c->convert("Hello, C++") << std::endl;
    }

    /////////////////////////////////////////////
    // パラメータ化継承によって関数を追加する例
    Printable<std::vector<int>> pv = {1,2,3};
    Printable<std::list<int>> pl = {4,5,6};

    pv.print_on(std::cout, "/") << std::endl;
    pl.print_on(std::cout, ",") << std::endl;

    return 0;
}