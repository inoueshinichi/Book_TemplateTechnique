#include "template_stack.hpp"

#include <iostream>

int main(int argc, char** argv)
{
    Stack<int> s(10);
    s.push(1);
    s.push(2);
    while (s.size() != 0)
    {
        std::cout << s.top() << std::endl;
        s.pop();
    }

    return 0;
}