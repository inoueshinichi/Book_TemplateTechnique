#include "expression_template.hpp"

#include <iostream>
#include <chrono>
using namespace std::chrono;


int main(int, char**)
{
    // 一時オブジェクトのコスト
    {
        math::vector x, y, z, t;

        auto start = high_resolution_clock::now();
        // コピーコンストラクタ2回と代入演算子1回が呼ばれる
        t = x + y + z;

        auto end = high_resolution_clock::now();
        auto duration = end - start;
        double duration_ns = duration_cast<nanoseconds>(duration).count();
        std::cout << duration_ns << "[ns]" << std::endl;

        ///////////////////////////////////////////
        // 一時オブジェクトを生成せずに計算する方法
        ///////////////////////////////////////////
        start = high_resolution_clock::now();
        // その１ +=を使う
        t = x;
        t += y;
        t += z;

        end = high_resolution_clock::now();
        duration = end - start;
        duration_ns = duration_cast<nanoseconds>(duration).count();
        std::cout << duration_ns << "[ns]" << std::endl;

        start = high_resolution_clock::now();
        // その2 for文を使う
        for (size_t i = 0; i < math::vector::N; ++i) {
            t[i] += x[i] + y[i] + z[i];
        }

        end = high_resolution_clock::now();
        duration = end - start;
        duration_ns = duration_cast<nanoseconds>(duration).count();
        std::cout << duration_ns << "[ns]" << std::endl;

        // いずれも直感的でない
        // 直感的かつ一時オブジェクトを作らずに計算する方法 -> Expression Template
    }   

    // Expression Template
    // 式の一部(x+y)を評価していくのではなく、
    // 式の全体(t = x + y + z)が現れたときに、つまり、代入が行われたときに
    // 全体を一度に評価することで、不要な計算を行わせないこと.
    // Expression Templateという手法では、(x+y+z)という式をoperatpr+で
    // それぞれ、計算するのではなく(x+y+z)という式の構造を保存しておき、
    // 必要になったとき(ここでは、代入演算子が呼ばれたとき)に計算するという遅延評価を実現する.
    // Expression Templateのために用意するのは(+),(-),(*),(/)のような各演算を行う小さなクラス.
    {
        using namespace expression_template;

        std::vector<int> left = {1,2,3,4,5};
        std::vector<int> right = {1,1,1,1,1};

        plus p(left, right);
        for (int i = 0; i < left.size(); ++i) {
            std::cout << p[i];
        }
        std::cout << std::endl;


        // 一時オブジェクトが生成されない演算
        vector x, y, z, t;

        auto start = high_resolution_clock::now();

        t = x + y + z;

        auto end = high_resolution_clock::now();
        auto duration = end - start;
        double duration_ns = duration_cast<nanoseconds>(duration).count();
        std::cout << duration_ns << "[ns]" << std::endl;

        start = high_resolution_clock::now();
        
        // multiply + plus
        t = x + y * z;

        end = high_resolution_clock::now();
        duration = end - start;
        duration_ns = duration_cast<nanoseconds>(duration).count();
        std::cout << duration_ns << "[ns]" << std::endl;
    }

    // 更に改良したExpression Templateによる演算の効率化
    {
        using namespace expression_template_operator;

        vector x, y, z, t;

        auto start = high_resolution_clock::now();

        t = x + y * z;

        auto end = high_resolution_clock::now();
        auto duration = end - start;
        double duration_ns = duration_cast<nanoseconds>(duration).count();
        std::cout << duration_ns << "[ns]" << std::endl;
    }
}