#include "type_conversion_operator.hpp"

#include <iostream>

#include <list>
#include <vector>
#include <deque>

int main(int, char**)
{
    // how to Integer
    {
        using namespace how_to;

        Integer value = 3;
        int n = value; // value.operator int()が呼ばれる.

        n = value;
        n = value.operator int();
        n = (int)value;
    }

    // operator bool
    {
        pointer<int> p;
        if (!p) {
            // ヌルポインタ
        }

        using namespace how_to;

        if (Integer n1 = 1) {}
        else if (Integer n2 = 2) {}
        else if (Integer n3 = 3) {}
        else {
            n1;
            n2;
            n3;
        }
    }

    // foreach文を作成する
    // 常にfalseを返すoperator boolの応用例
    {
        std::vector<int> v = {1, 2, 3};

        FOR_EACH(int item, v) {
            std::cout << item << std::endl;
        }
    }


    // 戻り値の型によるオーバーロード
    // 言語仕様で正式にはサポートされていない戻り値の型によるオーバーロードが
    // 型変換演算子を駆使することで実現可能.
    {
        using namespace example;

        A a = foo(); // OK : call A
        B b = foo(); // OK : call B

        X x;

        static_cast<A>(x); // call A
        static_cast<B>(x); // call B
    }

    // 戻り値による型推論
    {
        using namespace inference_type_by_return;

        Integer value = 3;

        // 代入/初期化構文の左辺から戻り値の型を推論している
        int n = value; // value.operator int()
        double d = value; // value.operator double()
        char c = value; // value.operator char()

        // 戻り値の型Tのコンストラクタで生成したインスタンスを戻り値としている
        container_holder<int> con;

        con.push_back(1);
        con.push_back(2);
        con.push_back(3);

        // container_holderから標準コンテナへ変換
        std::vector<int> v = con;
        std::list<int> l = con;
        std::deque<int> de = con;
    }

    // lexical_cast
    {
        using namespace lexical;

        int n = lexical_cast<int>("3"); 

        std::string s = lexical_cast<std::string>(314);
    }

    // 改良版lexical_cast
    {
        using namespace lexical;

        // 型が曖昧だといわれてエラーになる...
        // int n = lexical("3");
        // std::string s = lexical(314);
    }
}