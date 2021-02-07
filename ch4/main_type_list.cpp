#include "type_list.hpp"

#include <iostream>

int main(int argc, char** argv) {

    // constexpr bool judge = any_of<is_int, char*, long, int>::value;
    constexpr bool judge = any_of_v<is_int, char*, long, int>;
    std::cout << "judge int -> " << std::boolalpha << judge << std::endl;

    constexpr bool judge_kai = any_of_kai<is_int>::value;
    std::cout << "judge_kai int -> " << std::boolalpha << judge_kai << std::endl;

    transform_t<std::remove_reference, char&, long&, int&> t;

    struct X {
        using type = int;
    };

    struct Y {};

    constexpr bool result_X = has_type<X>::value;
    constexpr bool result_Y = has_type<Y>::value;
    std::cout << "result_X -> " << std::boolalpha << result_X << std::endl;
    std::cout << "result_Y -> " << std::boolalpha << result_Y << std::endl;


    return 0;
}