#pragma once

struct X
{
    using result = int;
    result f() { return 1; }
};

template <typename T>
void g(T arg)
{
    typename T::result* p;
}

struct Y
{
    static const int result = 5;
};


template <typename T>
typename T::result f(T t)
{
    return t.f();
}


class Utility
{
public:
    template <int N>
    int get(int arg)
    {
        return N + arg;
    }
};


template <typename T>
int foo(T x, int n)
{
    return x.template get<3>(n);
}