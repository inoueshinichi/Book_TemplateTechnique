#include "meta_func.hpp"

#include <iostream>

int main(int argc, char** argv) {

    /* メタ関数 */
    // int n = incremental<3>::value;
    int n = incremental_v<3>; // C++14 変数テンプレート
    std::cout << "incremental<3>::value -> " << n << std::endl;

    //////////////////
    /* 再帰メタ関数 */
    // factorial
    int result = factorial<10>::value;
    std::cout << "factorial<10>::value -> " << result << std::endl;

    // square
    int ans = square<5>::value;
    std::cout << "square<5>:value -> " << ans << std::endl;

    // pow
    int answer = pow<2, 3>::value;
    std::cout << "pow<2,3>::value -> " << answer << std::endl;

    // constexpr pow
    // constexpr型の関数は浮動小数点もコンパイル時に計算できる！
    constexpr int con_ans = pow_con(2, 3);
    std::cout << "pow_con(2,3) -> " << con_ans << std::endl;

    /////////////////////////////////////////////////////
    // 型を操作するメタ関数(エイリアステンプレートを使用)
    /////////////////////////////////////////////////////
    

    return 0;
}