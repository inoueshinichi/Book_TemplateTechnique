#include "compile_if.hpp"

#include <iostream>
#include <vector>

int main(int argc, char** argv) {

    // コンパイル時if文
    if_t<(sizeof(int) > sizeof(long)), int, long> value;

    ///////////
    // 高階関数
    std::vector<int> vec = {1,3};
    // 偶数を探す
    bool found_even = Is::find_if(std::begin(vec), std::end(vec), Is::is_even()) != std::end(vec);
    std::cout << "found_even -> " << std::boolalpha << found_even << std::endl;
    // 奇数を探す
    bool found_odd = Is::find_if(vec.begin(), vec.end(), Is::is_odd) != std::end(vec);
    std::cout << "found_odd -> " << std::boolalpha << found_odd << std::endl;

    return 0;
}