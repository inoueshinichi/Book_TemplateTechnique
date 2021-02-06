#include "generic_program.hpp"

#include <iostream>
#include <functional>
#include <iterator>

int main(int argc, char** argv)
{
    int data[] = {9,7,5,3,1,8,6,4,2,0};

    selection_sort(std::begin(data), std::end(data), std::greater<int>());

    for (int x : data)
    {
        std::cout << x << ",";
    }
    std::cout << std::endl;
    return 0;
}