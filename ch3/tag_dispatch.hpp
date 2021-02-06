#pragma once

#include <iterator>

namespace Is
{
    // // advance (1)
    // template <typename Iterator, typename Distance>
    // void advance(Iterator& iter, Distance offset)
    // {
    //     iter += offset; // Random_Access_Iteratorしかコンパイルできない
    // }

    // // advance (2)
    // template <typename Iterator, typename Distance>
    // void advance(Iterator& iter, Distance offset)
    // {
    //     // Random_Access_Iteratorに対して効率が悪い
    //     if (offset > 0)
    //     {
    //         for (; 0 < offset; --offset)
    //             ++iter;
    //     }
    //     else
    //     {
    //         for(; offset > 0; ++offset)
    //             --iter;
    //     }
    // }

    //////////////////////////
    // タグディスパッチの利用 -> コンパイル時ポリモーフィズム
    //////////////////////////

    // InputIterator版: "1つ進むを繰り返す(後戻り不可)"
    template <typename InputIterator, typename Distance>
    void _advance(InputIterator& iter, Distance offset, std::input_iterator_tag)
    {
        for (; 0 < offset; --offset)
                ++iter;
    }

    // ForwardIterator版: "1つ進むを繰り返す(後戻り不可)"
    template <typename ForwardIterator, typename Distance>
    void _advance(ForwardIterator& iter, Distance offset, std::forward_iterator_tag)
    {
        for (; 0 < offset; --offset)
                ++iter;
    }

    // BidirectionalIterator版: "1つ進む/戻るを繰り返す"
    template <typename BidirectionalIterator, typename Distance>
    void _advance(BidirectionalIterator& iter, Distance offset, std::bidirectional_iterator_tag)
    {
        if (offset > 0)
        {
            for (; 0 < offset; --offset)
                ++iter;
        }
        else
        {
            for(; offset > 0; ++offset)
                --iter;
        }
    }

    // RandomAccessIterator版: operator+=で一気にジャンプ
    template <typename RandomAccessIterator, typename Distance>
    void _advance(RandomAccessIterator& iter, Distance offset, std::random_access_iterator_tag)
    {
        iter += offset;
    }

    // タグによる呼び分けを施した関数advance()
    template <typename Iterator, typename Distance>
    void advance(Iterator& iter, Distance offset)
    {
        // イテレータの性質に応じたタグのtypedefにより関数の振り分けを行う.
        _advance(iter, offset, typename std::iterator_traits<Iterator>::iterator_category());
    }
}
