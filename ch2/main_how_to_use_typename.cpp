#include "how_to_use_typename.hpp"

int main()
{
    X x{};
    Y y{};

    g(x); // OK
    // g(y); // error

    // --------------------------

    X::result value = f(x);

    // --------------------------

    Utility u;

    int ret = foo(u, 3);

    return 0;
}