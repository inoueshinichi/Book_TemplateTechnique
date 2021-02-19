#include "policy1.hpp"

int main(int argc, char** argv) {

    // ポリシーとポリシークラス
    hoge<debug_log>().foo();
    hoge<release_log>().foo();
    hoge<file_log>().foo();

    // 1) staticメンバ関数を持つポリシークラス -> ポリシークラスは状態を持たない
    static_widget<static_policy> hoge;
    hoge.do_something();

    // 2) 非静的メンバ関数を持つポリシークラス -> ポリシークラスは状態を持つ
    non_static_widget<non_static_policy> hoge2;
    hoge2.do_something();

    // 3) 継承によるポリシークラス -> ポリシークラスは状態を持つ
    // また、テンプレートパラメータごとに自由にメンバ変数・関数の増減を制御できる
    non_static_widget_with_extension<non_static_policy_with_extension> hoge3;
    hoge3.do_something();


    // デフォルトポリシークラス
    default_widget<>().do_something(); // default: cout_policy
    default_widget<printf_policy>().do_something(); // 明示的にポリシークラスを指定する

    return 0;
}