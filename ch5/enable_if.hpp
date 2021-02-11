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

    template <bool Cond>
    using enable_if_t = enable_if<Cond>::type;
}

/////////////////////
// ver1(仮引数の型)
/////////////////////
// 引数の数が固定の関数に対して使えない

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

/////////////////////
// ver2(戻り値の型)
/////////////////////
// 引数が固定の関数に対して使える
// ただし、式が煩雑

struct has_add_member_impl {
    template <typename T, typename U>
    static auto check(T*, U*) -> decltype(std::declval<T>().add(std::declval<U>()), std::true_type());

    template <typename T, typename U>
    static std::false_type check(...);
};

template <typename T, typename U>
struct has_add_member : public decltype(has_add_member_impl::check<T, U>(nullptr, nullptr))
{};

template <typename T, typename U>
constexpr const bool has_add_member_v = has_add_member<T, U>::value;

// 関数テンプレートのoperator+
// T型がadd()メンバ関数を持っている場合のみ、呼び出される。
template <typename T, typename U>
auto operator+(const T& a, const U& b) -> std::enable_if_t<has_add_member_v<T, U>, T>
{
    return a.add(b);
}


//////////////////////////////////////////////////////
// ver3(関数テンプレートのデフォルトテンプレート引数)
//////////////////////////////////////////////////////
// 万能な方法。これ使えばstd::enable_if_t<T>はOK

// class ?
struct is_class_impl {
    template <typename T>
    static std::true_type check(void (T::*)());

    template <typename T>
    static std::false_type check(...);
};

template <typename T>
class is_class : public decltype(is_class_impl::check<T>(nullptr))
{};

template <typename T>
constexpr bool is_class_v = is_class<T>::value;


// ------------------------------------------------
// main

template <typename T, typename std::enable_if_t<is_class_v<T>>* = nullptr>
void check_class(T value)
{
    std::cout << "Tはクラス" << std::endl;
}

template <typename T, typename std::enable_if_t<!is_class_v<T>>* = nullptr>
void check_class(T value)
{
    std::cout << "Tはクラスでない" << std::endl;
}


///////////////////////////////////////////////////////////////////
// ver4(専門特化した実装を持っているかどうかでオーバーロードする)
///////////////////////////////////////////////////////////////////
// instance.sort関数を持つstd::listとstd::sort関数が使えるstd::vector系を同じ関数で処理する

// T型がsort()メンバ関数を持っているか判定するメタ関数
struct has_sort_member_impl {
    template <typename T>
    static auto check(T*) -> decltype(std::declval<T>().sort(), std::true_type());

    template <typename T>
    static auto check(...) -> std::false_type;
};

template <typename T>
struct has_sort_member : public decltype(has_sort_member_impl::check<T>(nullptr)) {};

template <typename T>
constexpr bool has_sort_member_v = has_sort_member<T>::value;


template <typename Sortable, std::enable_if_t<has_sort_member_v<Sortable>>* = nullptr>
void sort(Sortable& container)
{
    container.sort();
}

template <typename Range, std::enable_if_t<!has_sort_member_v<Range>>* = nullptr>
void sort(Range& container)
{
    std::sort(std::begin(container), std::end(container));
}