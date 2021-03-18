#pragma once

#include <memory>
#include <iostream>

// std::enable_shared_from_thisの使用例
namespace how_to {
    
    // 関数テンプレート
    template <class T>
    void print_share(std::shared_ptr<T> p) {
        p->print();
    }


    class X : public std::enable_shared_from_this<X> {
    public:
        void f() {
            print_share(shared_from_this());
        }

        void print() {
            std::cout << "X" << std::endl;
        }
    };
}


// enable_shared_from_thisクラスの簡易実装
namespace easy_implement {

    // enable_shared_from_this
    template <class T>
    class my_enable_shared_from_this {
        std::weak_ptr<T> weak_this_;
    public:
        std::shared_ptr<T> shared_from_this() {
            std::shared_ptr<T> p(weak_this_);
            return p;
        }

        void setup_shared_from_this(const std::shared_ptr<T>& p) {
            if (weak_this_.expired()) {
                weak_this_ = p;
            }
        }
    };

    // 関数テンプレート
    template <class T>
    void print_share(std::shared_ptr<T> p) {
        p->print();
    }

    // X
    class X : public my_enable_shared_from_this<X> {
    public:
        void f() {
            print_share(shared_from_this());
        }

        void print() {
            std::cout << "X" << std::endl;
        }
    };
}