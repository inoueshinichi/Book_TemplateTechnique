#include "sfinae1.hpp"

#include <vector>

int main(int argc, char** argv) {

    // 簡単なSFINAE
    something<widget>(nullptr);
    something<int>(nullptr);

    // 型特性メタ関数
    std::cout << std::boolalpha;
    std::cout << is_void_v<void> << std::endl;
    std::cout << is_void_v<int> << std::endl;
    std::cout << is_void_v<char*> << std::endl;

    std::cout << is_pointer_v<char> << std::endl;
    std::cout << is_pointer_v<char*> << std::endl;

    // 型Tが特定の型を持っているか否かを判定する関数
    // static_assert(has_iterator<std::vector<int>>(), "std::vector<int>はiterator型を持っている"); // ver1
    static_assert(has_iterator<std::vector<int>>::value, "std::vector<int>はiterator型を持っている"); // ver2
    static_assert(has_iterator_v<std::vector<int>>, "std::vector<int>はiterator型を持っている"); // ver3
    // static_assert(has_iterator<int>(), "intはiterator型を持っていない");

    return 0;
}