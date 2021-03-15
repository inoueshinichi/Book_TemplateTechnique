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

// std::function<>の応用
// draw()というメンバ関数を持っていれば、あらゆる型で振る舞えるdrawableクラス
class drawable {
    std::function<void()> draw_func_;
public:
    drawable() {}

    template <class T>
    drawable(T& obj)
        : draw_func_([&obj]() { obj.draw(); }) {}
    
    template <class T>
    drawable& operator=(T& obj) {
        draw_func_ = [&obj]() { obj.draw(); };
        return *this;
    }

    void draw() const {
        draw_func_();
    }
};

struct circle {
    void draw() const {
        std::cout << "円を描画する" << std::endl;
    }
};

struct square {
    void draw() const {
        std::cout << "矩形を描画する" << std::endl;
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


    // std::function<>の応用
    // draw()というメンバ関数を持っていれば、あらゆる型で振る舞えるdrawableクラス
    {
        drawable a;

        circle c;
        a = c; // operator=
        a.draw();

        square s;
        a = s; // operator=
        a.draw();
    }
}