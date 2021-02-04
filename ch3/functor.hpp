#pragma once

namespace Is
{
    ////////////////////////////////////////////////
    // find_if アルゴリズムの実装

    template <typename Iterator, typename Predicate>
    Iterator find_if(Iterator first, Iterator last, Predicate pred)
    {
        while (first != last)
        {
            if (pred(*first))
            {
                break;
            }
            ++first;
        }
        return first;
    }
}
