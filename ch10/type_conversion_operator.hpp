#pragma once

#include <vector>
#include <iostream>
#include <sstream>
#include <string>

namespace how_to {
    
    class Integer {
        int data_;

    public:
        Integer(int data = 0) : data_(data) {}

        // 型変換演算子
        operator int() const {
            return data_;
        }

        // 常にfalseを返す
        operator bool() const {
            return false;
        }
    };
}



// operator bool
template <class T>
class pointer {
    T* p_;
public:
    pointer(T* p = nullptr)
        : p_(p) {}
    
    operator bool() const {
        return p_ != nullptr;
    }
};



// foreach
class iterator_holder {
    using value_type = std::vector<int>::iterator;
    value_type iter_;
public:
    iterator_holder(value_type iter) : iter_(iter) {}

    value_type& get() { return iter_; }

    operator bool() const {
        return false;
    }
};

#define FOR_EACH(Value, Container)                                               \
    if (iterator_holder begin_ = std::begin(Container)) {}                       \
    else if (iterator_holder end_ = std::end(Container)) {}                      \
    else for (bool continue_ = true; begin_.get() != end_.get(); ++begin_.get()) \
        if ((continue_ = false) == true) {}                                      \
        else for (Value = *begin_.get(); continue_ == false; continue_ = true)


/////////////////////////////////
// 戻り値の型によるオーバーロード
/////////////////////////////////
namespace example {

    struct A {};
    struct B {};

    A foo_a() { std::cout << "call A" << std::endl; return A(); }
    B foo_b() { std::cout << "call B" << std::endl; return B(); }

    struct X {
        operator A() const { return foo_a(); }
        operator B() const { return foo_b(); }
    };

    X foo() {
        return X();
    }
}


/////////////////////
// 戻り値による型推論
/////////////////////
namespace inference_type_by_return {
    class Integer {
        int data_;
    public:
        Integer(int data = 0) : data_(data) {}

        // 戻り値による型推論
        template <class T>
        operator T() const {
            return data_;
        }
    };


    // テンプレート型変換演算子を使用した応用例
    template <class ValueType>
    class container_holder {
        std::vector<ValueType> vec_;
    public:
        void push_back(const ValueType& value) {
            vec_.push_back(value);
        }

        // 戻り値の型Tのコンストラクタで生成したインスタンスを戻り値としている
        template <class T>
        operator T() const {
            return T(std::begin(vec_), std::end(vec_));
        }
    };

}


namespace lexical
{
    // lexical_cast: 数値と文字列の相互変換関数

    template <class To, class From>
    To lexical_cast(From from) {
        To result;
        std::stringstream ss;

        ss << from;
        ss >> result;

        return result;
    }


    template <class From>
    class lexical_cast_t {
        From from_;
    public:
        lexical_cast_t(From from)
            : from_(from) {}
        
        template <class To>
        operator To() const {
            return lexical_cast<To>(from_);
        }
    };

    template <class From>
    lexical_cast_t<From> lexical(From from) {
        return lexical_cast_t<From>(from);
    }
}

