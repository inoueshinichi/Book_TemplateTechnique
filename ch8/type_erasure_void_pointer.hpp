#pragma once

/**
 * @brief Type Erasure
 * C++は静的型付けが得意で、あるオブジェクトを代入したときに
 * 型安全にオブジェクトの内容を保持するクラスを設計することを考えると
 * テンプレートクラス、関数テンプレートでは動的な実装が難しい
 */

/**
 * @brief void*にキャストする.
 * 型Tをvoid*にキャストして保持し、必要になった時点で型Tにキャストする戦略.
 */

namespace example {

    class any {
        void* data_;
    public:
        any() : data_(nullptr) {}

        template <class T>
        any(const T& data) : data_(new T(data)) {} // 仮引数は必ず左辺値なので、実引数が右辺値でも左辺値のアドレスを取れる.

        ~any() {
            delete data_; // 問題：voidポインタのdeleteは未定義動作!!!
        }

        template <class T>
        any& operator=(const T& data) {
            delete data_;
            data_ = new T(data);
            return *this;
        }

        template <class T> friend 
        T& any_cast(any&); // この関数ではanyクラスのprivateメンバにアクセスできる.
    };

    template <class T>
    T& any_cast(any& data) {
        return *static_cast<T*>(data.data_);
    }


}
