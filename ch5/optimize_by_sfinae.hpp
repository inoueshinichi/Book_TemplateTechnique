#pragma once

#include <iterator>
#include <type_traits>

#include <iostream>
#include <cstring> // std::memmove

////////////////////////////
// SFINAEによる実装の最適化
////////////////////////////
// SFINAEは最適化にも利用できる

namespace Is {
    template <typename InputIterator, typename OutputIterator>
    OutputIterator copy(InputIterator first, InputIterator last, OutputIterator out)
    {
        while (first != last) {
            *out = *first;
            ++out;
            ++first;
        }
        return out;
    }
}

namespace optim {

    /////////////////////////////////////////////////////////
    // copy関数の最適化(ポインターの場合std::memmoveを使う)
    template <typename Iterator,
              std::enable_if_t<std::is_pointer<Iterator>::value &&
                               std::is_trivially_copy_assignable_v<typename std::iterator_traits<Iterator>::value_type> &&
                               std::is_trivially_destructible_v<typename std::iterator_traits<Iterator>::value_type>
                               >* = nullptr>
    Iterator copy(Iterator first, Iterator last, Iterator out)
    {
        std::cout << "memmove" << std::endl;
        // std::memcpy()の上位互換
        // std::memcpyはメモリブロックoutとメモリブロックfirstが重なっているとき、未定義動作になるが、
        // std::memmove()は正常にブロックが移動(コピー)される
        std::memmove(out, first, (last - first) * sizeof(decltype(*first))); 
        return out + (last - first);
    }

    template <typename InputIterator, typename OutputIterator>
    OutputIterator copy(InputIterator first, InputIterator last, OutputIterator out) 
    {
        std::cout << "loop copy" << std::endl;
        while (first != last) 
        {
            *out = *first;
            ++out;
            ++first;
        }
        return out;
    }


    ///////////////////////////////////////////////////////////////////////////////////
    // 組み込み型(int, char, etc..)をnewでメモリ確保した場合、デストラクタは不要らしい
    // 不要なデストラクタの場合で専門特化して最適化する
    template <typename T,
              std::enable_if_t<std::is_trivially_destructible_v<T>>* = nullptr>
    void destroy_all(T*, T*)
    {
        std::cout << "Don't destroy" << std::endl;
    }

    template <typename T,
              std::enable_if_t<!std::is_trivially_destructible_v<T>>* = nullptr>
    void destroy_all(T* first, T* last)
    {
        std::cout << "Execute loop destroy" << std::endl;
        while (first != last)
        {
            first->~T();
            ++first;
        }
    }

} // optim