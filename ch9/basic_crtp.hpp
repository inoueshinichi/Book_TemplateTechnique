#pragma once

#include <iostream>

// 仮想関数による動的なポリモーフィズム
namespace how_to {

    // 基底
    struct base {
        void base_foo() const {
            foo_impl();
        }

        virtual void foo_impl() const = 0;
    };

    // 派生
    struct derived : public base {
        virtual void foo_impl() const override {
            std::cout << "derived::foo_impl" << std::endl;
        }
    };

}


// CRTPを使用した静的なポリモーフィズム
namespace crtp {

    // 基底
    template <class Derived>
    struct base {
        void base_foo() const {
            static_cast<const Derived&>(*this).foo_impl(); // 自分自身を派生クラスにダウンキャストする
        }
    };

    // 派生
    struct derived : public base<derived> {
        void foo_impl() const {
            std::cout << "derived::foo_impl" << std::endl;
        }
    };
}


// 仮想関数によるTemplate Method パターン
namespace template_method_with_vtable {

    // 基底
    class base {
        virtual void template_method_impl() const = 0; // private
    public:
        void interface_api() const { // インターフェースAPI(外部に公開)
            template_method_impl();
        }
    };

    // 派生
    class derived : public base {
        virtual void template_method_impl() const override { // private
            std::cout << "template_method_impl" << std::endl;
        }
    };
}   


// CRTPによるTemplate Method パターン
namespace template_method_with_crtp {

    // 基底
    template <class Derived>
    class base {
    public:
        void interface_api() const { // インターフェースAPI(外部に公開)
            static_cast<const Derived&>(*this).template_method_impl();
        }
    };

    // 派生
    class derived : public base<derived> {
    public:
        void template_method_impl() const { // 派生クラスの実装が公開になっていしまうのがCRTPによるTemplate Methodパターンの弱点か？
            std::cout << "template_method_impl" << std::endl;
        }
    };
}