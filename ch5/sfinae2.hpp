#pragma once

#include <type_traits>
#include <utility>

/////////////////////////////////////////
// T型がクラスかどうかを判定するメタ関数
/////////////////////////////////////////
// void T::* or void (T::*)()を使う

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


///////////////////////////////////
// 特定の式が有効かどうかを判定する
///////////////////////////////////
// C++11以降ではdecltypeに記述した式にもSFINAEが働く
// [式が有効である]とは以下のことを云う
// 1) 要素が見えている(存在する)
// 2) 要素がクラスメンバの場合、アクセス可能である
// 3) 要素が関数の場合、（オーバーロードの解決の結果）呼び出し可能である

///////////////////////////////
// 代入可能かどうかを判定する
///////////////////////////////

struct is_assignable_impl {
    template <typename T>
    static auto check(T*) -> decltype(std::declval<T&>() = std::declval<const T&>(), std::true_type());

    template <typename T>
    static auto check(...) -> std::false_type;
};

template <typename T>
struct is_assignable : public decltype(is_assignable_impl::check<T>(nullptr))
{};

template <typename T>
constexpr bool is_assignable_v = is_assignable<T>::value;


//////////////////////////////
// 加算可能かどうかを判定する
//////////////////////////////

struct is_addable_impl {
    template <typename T, typename U>
    static auto check(T*, U*) -> decltype(std::declval<T>() + std::declval<U>(), std::true_type());

    template <typename T, typename U>
    static auto check(...) -> std::false_type;
};

template <typename T, typename U>
struct is_addable : decltype(is_addable_impl::check<T, U>(nullptr, nullptr))
{};

template <typename T, typename U>
constexpr bool is_addable_v = is_addable<T, U>::value;