#include "helper_func_for_predict.hpp"

#include <iostream>
#include <vector>
#include <iterator>

int main(int argc, char** argv)
{
    int arr[] = {1,2,4,8,16};
    std::vector<int> v(std::begin(arr), std::end(arr));

    print_all(std::pair<int*, int*>(std::begin(arr), std::end(arr)));
    print_all(std::pair<decltype(v)::iterator, decltype(v)::iterator>(std::begin(v), std::end(v)));

    /* 以下ヘルパー関数を使ってstd::pairの引数を与える */
    print_all(Is::make_pair(std::begin(arr), std::end(arr)));
    print_all(Is::make_pair(std::begin(v), std::end(v)));

    // 標準ライブラリのヘルパ関数例
    int data[] = {1,2,3};
    std::vector<int> vv;
    std::copy(std::begin(data), std::end(data), std::back_insert_iterator<decltype(vv)>(vv));
    print_all(Is::make_pair(std::begin(vv), std::end(vv)));

    std::copy(std::begin(data), std::end(data), std::back_inserter(vv)); // std::back_inserterはヘルパ関数
    print_all(Is::make_pair(std::begin(vv), std::end(vv)));

    return 0;
}