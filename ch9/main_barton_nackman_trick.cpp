#include "barton_nackman_trick.hpp"


int main(int, char**)
{
    // クラススコープ内で演算子を定義
    {
        using namespace normal;

        hoge h1(1);
        hoge h2(1);

        bool is_equal = (h1 == h2); // hogeのoperator==が呼ばれる
    }

    // friend関数とCRTPによるBarton-Nackman Trick
    {
        using namespace barton_nackman_trick;

        hoge h1(1);
        hoge h2(1);

        bool is_equal = (h1 == h2);
        bool is_not_equall = (h1 != h2); 
        bool is_less = (h1 < h2);
        bool is_greater = (h1 > h2);
        bool is_less_or_equal = (h1 <= h2);
        bool is_greater_or_equal = (h1 >= h2);
    }


    // Barton-Nackman Trickのルックアップ問題
    // クラススコープ内でfreind関数を定義したが、こうすると
    // クラススコープ内のfriend関数を直接呼び出すことができない.
    {
        using namespace problem_of_lookup;

        hoge h1, h2;
        bool is_equal = (h1 == h2); // OK
        // is_equal = hoge::operator==(h1, h2); // エラー
        // is_equal = ::operator==(h1, h2); // エラー 
    }


    /**
     * @brief ADL(Argument Dependent Lookup)
     * 引数依存の名前検索
     * 関数呼び出し時の引数の型に合わせて、呼び出す関数を探しに行く仕組み.
     * 
     * std::string hello = "Hello World";
     * std::cout << hello;
     * ADLが動作している.
     * namespace std {
     *  ostream& operator<<(ostream&, const string&);
     * }
     * であるため、本来はstd::operator<<(std::cout, hello);
     * と呼び出さなければならないが、ADLによって std::cout << helloを可能にしている.
     * 
     * Barton-Nackman Trickによって、クラススコープ内で定義したfriend関数は、ADLのみによって
     * アクセスできる.
     */
    
}