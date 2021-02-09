#pragma once

#include <iostream>

///////////////
// 簡単なSFINE
///////////////

struct widget { 
    using value_type = int;
};

template <class T>
void something(typename T::value_type*) {
    std::cout << "value_typeを持っている" << std::endl;
}

template <class T>
void something(...) {
    std::cout << "それ以外" << std::endl;
}


///////////////////////////////
// 型特性(type traits)メタ関数
///////////////////////////////

// void ?
template <class T>
struct is_void {
    static const bool value = false;
};

template <>
struct is_void<void> {
    static const bool value = true;
};

template<class T>
constexpr bool is_void_v = is_void<T>::value;


// pointer ?
template<class T>
struct is_pointer {
    static const bool value = false;
};

template<class T>
struct is_pointer<T*> {
    static const bool value = true;
};

template<class T>
constexpr bool is_pointer_v = is_pointer<T>::value;


//////////////////////////////////
// SFINAEを利用した型特性メタ関数
//////////////////////////////////
// テンプレートの特殊化によって表現できない型特性メタ関数はSFINAEで実現する

// ver1
// template<class T>
// constexpr bool has_iterator_impl(typename T::iterator*) {
//     return true;
// }

// template<class T>
// constexpr bool has_iterator_impl(...) {
//     return false;
// }

// template <class T>
// constexpr bool has_iterator() {
//     return has_iterator_impl<T>(nullptr);
// }

// ver2
// template <typename T>
// class has_iterator {
//     template <typename U>
//     static constexpr bool check(typename U::iterator*)
//     {
//         return true;
//     }

//     template <typename U>
//     static constexpr bool check(...)
//     {
//         return false;
//     }

// public:
//     static const bool value = check<T>(nullptr);
// };

// ver3 (C++11以降)
struct has_iterator_impl
{
    template <typename T>
    static std::true_type check(typename T::iterator*);

    template <typename T>
    static std::false_type check(...);
};

template <typename T>
class has_iterator : public decltype(has_iterator_impl::check<T>(nullptr))
{};

template <typename T>
constexpr bool has_iterator_v = has_iterator<T>::value;