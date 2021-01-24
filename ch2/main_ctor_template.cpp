#include "ctor_template.hpp"

int main(int argc, char** argv)
{
    Point<int> ip(12, 34);
    ip.print(std::cout);

    Point<long> lp(ip);
    lp.print(std::cout);

    
    return 0;
}