#include "type_erasure_virtual_table.hpp"

#include <iostream>

namespace example {
    namespace virtual_table {
        struct circle {
            void draw() const {
                std::cout << "継承していないcircleクラスのdraw()をdrawableインターフェースクラス経由で実行した." << std::endl;
            }
        };


        // 仮想関数テーブルを実装するインターフェースクラスを関数の仮引数に指定できる
        void draw(drawable a) {
            a.draw();
        }
    }
}


int main(int argc, char** argv) 
{
    // 継承によるポリモーフィズム
    {
        using namespace example;

        circle c;
        draw(c); // OK

        square s;
        draw(s); // OK

        triangle t;
        // draw(t); // コンパイルエラー
        draw(t); // テンプレート関数
    }

    // 仮想関数テーブルによるType Erasure
    // 継承よりも柔軟なインターフェースを実装できる
    {
        using namespace example;
        virtual_table::circle c;
        virtual_table::drawable a = c; // テンプレートコンストラクタが実行される
        a.draw(); // ポリモーフィズム実行

        virtual_table::draw(a);
    }
    return 0;
}