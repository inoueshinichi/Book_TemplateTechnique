#include "valiadic_template_params.hpp"

int main(int argc, char** argv)
{
    printType('T', 4, "two");

    // tuple
    tuple<char, int, const char*> t;
    get<0>(t) = 'T';
    get<1>(t) = 4;
    get<2>(t) = "two";
    printType(get<0>(t), get<1>(t), get<2>(t));

    // initializer
    std::vector<int> v = initializer<1,2,3>();
    for (int x : v)
    {
        std::cout << x << std::endl;
    }

    return 0;
}