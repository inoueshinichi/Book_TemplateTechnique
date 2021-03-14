#include "type_erasure_any.hpp"

#include <iostream>
#include <vector>
#include <string>

int main(int, char**)
{

    // anyクラス
    // メンバ関数テンプレートで受け取ったパラメータを
    // Type Erasureのテンプレート派生クラスであるholderのコンストラクタに渡して
    // newする. それをanyクラスのメンバであるhold_base* content_;に保持することで
    // holderの型とメンバ変数を隠す.
    {
        struct hoge {};

        any val = 3;  // intの値をコンストラクタに渡してany型として保持
        val = hoge(); // hoge型のインスタンスをoperatpr=に渡してany型として保持 
    }
    
    // 動的な型の切り替えと判別を行う
    {
        struct hoge {};
        any val = 3;
        val = hoge();

        if (val.type() == typeid(int)) {
            std::cout << "int型を持っています" << std::endl;
        } else if (val.type() == typeid(hoge)) {
            std::cout << "hoge型を持っています" << std::endl;
        } else {
            std::cout << "その他の型を持っています" << std::endl;
        }
    }

    // 保持している値を取り出す
    {
        struct hoge {};
        any val = 3;
        val = hoge();

        if (val.type() == typeid(int)) {
            std::cout << "int型を持っています" << std::endl;
            int value = val.cast<int>();
        } else if (val.type() == typeid(hoge)) {
            std::cout << "hoge型を持っています" << std::endl;
            hoge h = val.cast<hoge>();
        } else {
            std::cout << "その他の型を持っています" << std::endl;
        }
    }

    // なんでも入れちゃうany配列
    {
        struct hoge {};
        std::vector<any> v;

        v.push_back(3);
        v.push_back(hoge());
        v.push_back(std::string("abc"));

        // 動的に型を判別して処理を分ける
        for (const any& x : v) {
            if (x.type() == typeid(int)) {
                std::cout << "int" << std::endl;
            } else if (x.type() == typeid(hoge)) {
                std::cout << "hoge" << std::endl;
            } else if (x.type() == typeid(std::string)) {
                std::cout << "std::string" << std::endl;
            }
        }
    }
}