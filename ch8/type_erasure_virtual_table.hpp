#pragma once

#include <iostream>

///////////////////////////////////////////
// 仮想関数テーブルによるType Erasureの実現
///////////////////////////////////////////

namespace example {

    // 継承
    class drawable {
    public:
        drawable() = default;
        virtual ~drawable() {}
        drawable(const drawable&) = default;
        drawable& operator=(const drawable&) = default;
        drawable(drawable&&) = default;
        drawable& operator=(drawable&&) = default;

        virtual void draw() const = 0;
    };

    class circle : public drawable {
    public:
        virtual void draw() const override {
            std::cout << "円を描画する" << std::endl;
        };
    };

    class square : public drawable {
    public:
        virtual void draw() const override {
            std::cout << "四角形を描画する" << std::endl;
        }
    };

    // ポリモーフィズム
    void draw(const drawable& a) {
        a.draw();
    }

    // 継承されていないクラス
    class triangle {
    public:
        void draw() const {
            std::cout << "三角形を描画する" << std::endl;
        }
    };

    ///////////////////////////////////////////
    // テンプレートによって多態的に振る舞わせる
    ///////////////////////////////////////////
    template <class Drawable>
    void draw(const Drawable& a) {
        a.draw();
    }


    ///////////////////////////////////////////////////
    // 仮想関数テーブルを実装したインターフェースクラス
    ///////////////////////////////////////////////////
    // 継承していないクラスのメンバ関数のポリモーフィズムを実現する
    namespace virtual_table {
        
        class drawable {
            // 仮想関数テーブル
            struct vtable {
                void (*draw)(void*); // void*を引数に取る関数ポインタ
            };

            // 型T毎に別々にインスタンス化される仮想関数テーブルのイニシャライザ
            template <class T>
            struct vtable_initializer {
                static vtable vtbl_; // static変数はテンプレートクラスの実体化時に静的メモリ領域に定義される

                static void draw(void* this_) {
                    static_cast<T*>(this_)->draw();
                }
            };

            void* this_;
            vtable* vptr_;
        public:
            template <class T>
            drawable(T& other)
                : this_(&other)
                , vptr_(&vtable_initializer<T>::vtbl_) {}
            
            // 型情報を消したotherが持つ関数を実行する
            void draw() const {
                vptr_->draw(this_);
            }
        };

        template <class T>
        drawable::vtable drawable::vtable_initializer<T>::vtbl_ = { 
            &drawable::vtable_initializer<T>::draw
        };
    }


} // namespace example