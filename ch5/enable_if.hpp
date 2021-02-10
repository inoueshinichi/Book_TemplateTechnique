#pragma once

#include <type_traits>

#include <iostream>

///////////////////////////////////////
// 型特性によるオーバーロード
// std::enable_if, boost::enalbe_if_c
///////////////////////////////////////
// enable_ifは, SFINAEを利用して任意のオーバーロードを呼び出すためのメタ関数

namespace Is
{
    template <bool Cond, typename T = void>
    struct enable_if {
        using type = T;
    };

    template <typename T>
    struct enable_if<false, T> {
        // nothing
    };

    template <typename T>
    using enable_if_t = enable_if<T>::type;
}

// ver1(仮引数の型)
template <typename T>
void check(T value, typename std::enable_if_t<std::is_class<T>::value>* = nullptr)
{
    std::cout << "Tはクラス" << std::endl;
}

template <typename T>
void check(T value, typename std::enable_if_t<!std::is_class<T>::value>* = nullptr)
{
    std::cout << "Tはクラスではない" << std::endl;
}

// ver2(戻り値の型)

