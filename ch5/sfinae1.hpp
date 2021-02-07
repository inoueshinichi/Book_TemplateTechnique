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
template<class T>
constexpr bool has_iterator_impl(typename T::iterator*) {
    return true;
}

template<class T>
constexpr bool has_iterator_impl(...) {
    return false;
}

template <class T>
constexpr bool has_iterator() {
    return has_iterator_impl<T>(nullptr);
}
