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

    add_pointers_t<int, 5> np; 

    // その他

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

    // ポインタ
    int v = 3;
    add_pointer_t<int> pv = &v;
    std::cout << "*pv -> " << *pv << std::endl;

    // 左辺値const参照
    add_clr_t<int> clr = v;
    std::cout << "clr -> " << clr << std::endl;

    // 左辺値参照 -> const
    int value = 3;
    add_const_t<int> c = value;            // c : const int
    add_lvalue_reference_t<int> r = value; // int&
    std::cout << "c -> " << value << "r -> " << r << std::endl;

    int& vr = value; // 左辺値参照
    add_lvalue_reference_t<decltype(vr)> value_r = vr; // 部分特殊化で&&を回避
    add_const_t<add_lvalue_reference_t<decltype(vr)>> value_cr = vr;
    std::cout << "value_r -> " << value_r << std::endl;
    std::cout << "value_cr ->" << value_cr << std::endl;

    add_clr_mix_t<decltype(vr)> value_clr = value; // const int&
    std::cout << "value_clr -> " << value_clr << std::endl;

    ///////////////////////
    // 型修飾を外す
    ///////////////////////
    /* remove const */
    remove_const_t<decltype(c)> v_from_cv = value; // decltype(c) -> const int
    std::cout << "v_from_cv -> " << v_from_cv << std::endl;

    /* remove volatile */
    remove_volatile_t<volatile int> v_from_vv = value;
    std::cout << "v_from_vv -> " << v_from_vv << std::endl;

    /* remove const volatile */
    remove_cv_t<const volatile int> v_from_cvv = value;
    std::cout << "v_from_cvv -> " << v_from_cvv << std::endl;


    return 0;
}