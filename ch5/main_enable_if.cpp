#include "enable_if.hpp"


int main(int argc, char** argv)
{
    struct X {};

    check(X());
    check(3);

    return 0;
}