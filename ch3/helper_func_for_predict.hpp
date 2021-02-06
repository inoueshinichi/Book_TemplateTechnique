#pragma once

#include <map>
#include <iostream>

// イテレータの組(pair)を与えて、その範囲を出力する
template <typename Iterator>
void print_all(std::pair<Iterator, Iterator> iter_pair)
{
    while (iter_pair.first != iter_pair.second)
    {
        std::cout << *(iter_pair.first) << ",";
        ++(iter_pair.first);
    }
    std::cout << std::endl;
}

namespace Is
{
    // ヘルパー関数(型推論)
    template <typename FirstT, typename SecondT>
    std::pair<FirstT, SecondT> make_pair(FirstT&& first, SecondT&& second)
    {
        return std::pair<FirstT, SecondT>(std::forward<FirstT>(first), std::forward<SecondT>(second));
    }

}


