#include "type_erasure_functional.hpp"

#include <functional>
#include <iostream>

// 関数ポインタ(アドレス)
int func() {
    return 3;
}

// 関数オブジェクト
struct functor {
    int operator()() const {
        return 4;
    }
};

int main(int, char**)
{
    // std::function<>の使い方
    {
        std::function<int()> f;

        // 関数ポインタ
        f = &func;
        int func_result = f(); // 3
        std::cout << func_result << std::endl;

        // 関数オブジェクト
        f = functor();
        int functor_result = f(); // 4
        std::cout << functor_result << std::endl;
    }

    // 簡易実装したexample::function<>の使い方
    {
        example::function<int()> f;

        // 関数ポインタ
        f.set_function_ptr(&func);
        int func_result = f(); // 3
        std::cout << func_result << std::endl;

        // 関数オブジェクト
        f.set_function_obj(functor());
        int functor_result = f(); // 4
        std::cout << functor_result << std::endl;
    }

    // SFINAE(std::enable_if_t or タグディスパッチ)によるoperator=()の実装
    {
        example::function<int()> f;

        // 関数ポインタ
        f = &func;
        int func_result = f(); // 3
        std::cout << func_result << std::endl;

        // 関数オブジェクト
        f = functor();
        int functor_result = f(); // 4
        std::cout << functor_result << std::endl;
    }

}