#include "specialization.hpp"

#include <iostream>
#include <vector>
#include <type_traits>

int main(int argc, char** argv)
{
    // 明示的特殊化
    int n = 3;
    const char* s = "C++";
    std::cout << std::boolalpha;
    std::cout << equal(n, 2) << std::endl;
    std::cout << equal(n, 3) << std::endl;
    std::cout << equal(s, "Java") << std::endl;
    std::cout << equal(s, "C++") << std::endl;

    printer<int> p_int{};
    p_int.out('128');

    printer<std::string> p_str{};
    p_str.out("128");

    // 部分特殊化
    printer<int*> p_pint{};
    int value = 128;
    p_pint.out(&value);

    // 関数テンプレートの部分特殊化
    print(value);
    print(&value);

    return 0;
}