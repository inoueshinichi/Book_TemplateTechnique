#include "optimize_by_sfinae.hpp"

#include <list>
#include <vector>
#include <iostream>
#include <algorithm>

#include <memory>
#include <string>

// std::allocator用のヒープメモリ確保用関数
template <typename T>
void construct_all(T* first, T* last)
{
    while (first != last)
    {
        new (first) T();
        ++first;
    }
}

// std::allocatorによるメモリ生成と破棄を行う関数
template <typename T>
void genrm_heap_mem_block()
{
    std::allocator<T> alloc;

    std::size_t size = 3;
    T* array = alloc.allocate(size, nullptr);
    construct_all(array, array + size);

    // すべての要素に対してデストラクタを呼び出す
    // optim::destroy_all(static_cast<T*>(array), static_cast<T*>(array + size));
    optim::destroy_all(array, array + size);

    alloc.deallocate(array, size);
}


int main(int argc, char** argv)
{
    std::vector<int> v1 = {1,2,3};
    std::vector<int> v2(v1.size());

    // v1の要素をv2にコピー
    Is::copy(v1.begin(), v1.end(), v2.begin());
    for (int x : v2) {
        std::cout << x << std::endl;
    }

    // SFINAEは最適化にも利用できる
    int ar1[3] = {3,1,4};
    int ar2[3] = {};

    optim::copy(std::begin(ar1), std::end(ar1), std::begin(ar2));
    for (int x : ar2) { std::cout << x << std::endl; }

    std::list<int> ls1 = {300, 200, 100};
    std::list<int> ls2(ls1.size());

    optim::copy(std::begin(ls1), std::end(ls1), std::begin(ls2));
    for (int x : ls2) { std::cout << x << std::endl; }

    // デストラクタが不要な場合の最適化
    genrm_heap_mem_block<std::string>();
    genrm_heap_mem_block<int>();


    return 0;
}