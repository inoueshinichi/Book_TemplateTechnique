#pragma once

#include <iostream>

/////////////////////////////////////////////////////////////////////
// 非テンプレート基本クラスとテンプレート派生クラスによるType Erasure
/////////////////////////////////////////////////////////////////////
// 簡単で強力な実装なので、頻繁に利用される
// テンプレートのクラス、関数に代入した型情報を保持したい場合に有用

namespace example {

    // 非テンプレート基本クラス
    class Base {
    public:
        virtual ~Base() {}

        virtual void print() const {
            std::cout << "No implement." << std::endl;
        }
    };

    // テンプレート派生クラス
    template <class T>
    class Derived : public Base {
        T value_;
    public:
        Derived(const T& value)
            : value_(value) {}
        
        virtual ~Derived() {}

        void print() const override {
            std::cout << "T value stored Derived<T> class: " << value_ << std::endl;
        }
    };

    // 保持した型情報を使用するクラス
    class UseTemplateParam {
        Base* base_;
    public:
        template <class T>
        UseTemplateParam(const T& value) {
            base_ = new Derived<T>(value); // Derived<T>がType Erase
        }

        ~UseTemplateParam() {
            delete base_; // 継承のポリモーフィズムによってT情報を保持するDerived<T>クラスのデストラクタが呼ばれる.
        }

        // 型情報Tを使用する関数
        void print() const {
            base_->print(); // Base経由でDerivedで継承したprint()関数を実行する.
        }
    };


    // shared_ptrの実装例
    namespace sp {
        /////////////////////////////
        // shared_ptrのカスタム削除子
        /////////////////////////////
        class shared_deleter_base {
            shared_deleter_base() {}
            virtual ~shared_deleter_base() {}
            virtual void destroy() = 0;
        };

        template <class T, class D>
        class shared_deleter : public shared_deleter_base {
            T* object_;
            D deleter_;
        public:
            sahred_deleter(T* object, D deleter)
                : object_(object)
                , deleter_(deleter) {}

            ~shared_deleter() {}
            
            virtual void destroy() override {
                deleter_(object_); // デリータは func(T* object)
            }
        };

        // 簡易shared_ptrクラス
        template <class T>
        class shared_ptr {
            T* object_; // ポインタ
            shared_deleter_base* deleter_; // カスタム削除子
        public:
            // カスタム削除子を使用しないコンストラクタ
            explicit shared_ptr(T* object)
                : object_(object)
                , deleter_(nullptr) {}
            
            // カスタム削除子を使用するコンストラクタ
            template <class D>
            shared_ptr(T* object, D deleter)
                : object_(object) {
                deleter_ = new shared_deleter<T, D>(object_, deleter);
            }

            ~shared_ptr() {
                // カスタム削除子が指定されていたらそれを削除
                if (deleter_) {
                    deleter_->destroy();
                    delete deleter_;
                    deleter_ = nullptr;
                } else {
                    // カスタム削除子が指定されなかったパターン
                    delete object_;
                    object_ = nullptr;
                }
            }
        };
    }
}