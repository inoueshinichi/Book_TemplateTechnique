#pragma once

#include <iterator>

/////////////////////////////
// 複数の戻り値を持つメタ関数
/////////////////////////////

namespace Is {

    // プライマリー
    template <typename Iterator>
    struct iterator_traits {
        using difference_type = typename Iterator::difference_type;
        using value_type      = typename Iterator::value_type;
        using pointer         = typename Iterator::pointer;
        using reference       = typename Iterator::reference;
        using iterator_category = typename Iterator::iterator_category;
    };

    // (const)ポインタ型に対する部分特殊化
    template <typename T>
    struct iterator_traits<T*> {
        using defference_type = std::ptrdiff_t;
        using value_type      = std::remove_cv_t<T>; // const, volatileを外す
        using pointer_type    = T*; // Tがconst intなら -> const int*
        using reference_type  = T&; // Tがconst intなら -> const int&
        using iterator_category = std::random_access_iterator_tag; 
    };

    // // constポインタ型に対する部分特殊化(C++14まで)
    // template <typename T>
    // struct iterator_traints<const T*> {
    //     using defference_type = std::ptrdiff_t;
    //     using value_type      = T;
    //     using pointer_type    = const T*;
    //     using reference_type  = const T&;
    //     using iterator_category = std::random_access_iterator_tag; 
    // };
}