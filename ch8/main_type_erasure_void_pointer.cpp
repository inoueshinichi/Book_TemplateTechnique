#include "type_erasure_void_pointer.hpp"

#include <string>
#include <iostream>

struct widget {

    widget() {
        std::cout << "widget : コンストラクタ" << std::endl;
    }

    widget(const widget&) {
        std::cout << "widget : コピーコンストラクタ" << std::endl;
    }

    ~widget() {
        std::cout << "widget : デストラクタ" << std::endl;
    }

    void something() const {
        std::cout << "widget : 何かの処理" << std::endl;
    }
};


int main(int argc, char** argv) {

    // void*にキャスト
    {
        void* p = new widget();
        static_cast<widget*>(p)->something(); // 型安全ではない. 意図しない型にキャストすると未定義動作
        delete p;
    }

    // any
    {
        using namespace example;
        any data = 3; // anyのコピーコンストラクタ : int
        int n = any_cast<int>(data);

        data = static_cast<const char*>("abc"); // const char*として使う
        std::string str = any_cast<const char*>(data);
    }

    // any内部でvoid*をデリートすると未定義動作となり、型Tのデストラクタが呼ばれない
    {
        using namespace example;
        any data;
        {
            widget w;
            data = w; 
        }// wのスコープを抜けたときはwのデストラクタが呼ばれる
        // dataにコピーしたwのデストラクタは呼ばれない -> メモリリーク
        any_cast<widget>(data).something();
        std::cout << "anyのdataにコピーしたwのデストラクタは呼ばれない -> メモリリーク" << std::endl;
    }
    //////////////////////////////////////////////////////////////////////////////
    //  void*によるType Erasureは型安全な動的型の実装には向いていない
    //////////////////////////////////////////////////////////////////////////////

    return 0;
}