#include "iterator_func.hpp"

#include <vector>
#include <list>
#include <iostream>
#include <iterator> // back_inserter

int main(int argc, char** argv)
{
    /////////////////////////////////////////////////////////////////////////////
    // find with some iterator
    char arr[] = "hello";
    std::vector<int> v = {1, 2, 3};
    std::list<long> ls = {1L, 2L, 3L};
    char* p = Is::find(std::begin(arr), std::end(arr), 'e');
    if (p != std::end(arr))
    {
        std::cout << "*p = " << *p << std::endl;
    }

    decltype(v)::iterator iter_v = Is::find(std::begin(v), std::end(v), 3);
    if (iter_v != std::end(v))
    {
        std::cout << "*iter_v = " << *iter_v << std::endl;
    }

    decltype(ls)::iterator iter_ls = Is::find(std::begin(ls), std::end(ls), 2L);
    if (iter_ls != std::end(ls))
    {
        std::cout << "*iter_ls = " << *iter_ls << std::endl;
    }

    /////////////////////////////////////////////////////////////////////////////
    // copy with output iterator

    std::vector<int> vv = {1, 2, 3};
    std::vector<int> result;
    Is::copy(std::begin(vv), std::end(vv), std::back_inserter(result));
    for (int x : result)
    {
        std::cout << "result -> " << x << std::endl;
    }

    // back_inserterを使用せずにcopy
    std::vector<int> vvv = {1,2,3};
    std::vector<int> res(vvv.size());
    Is::copy(std::begin(vvv), std::end(vvv), std::begin(res));
    for (int x : result)
    {
        std::cout << "res -> " << x << std::endl;
    }

    return 0;
}