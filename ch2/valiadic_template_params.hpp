#pragma once

#include <typeinfo>
#include <iostream>
#include <vector>

////////////////////////////////
// テンプレートパラメータパック
////////////////////////////////

void printType()
{
    std::cout << std::endl;
}

// 可変引数関数テンプレート
template <typename Head, typename... Body>
void printType(Head head, Body... body)
{
    std::cout << "(" << typeid(Head).name() << ")" << head;
    if (sizeof...(body) > 0)
    {
        std::cout << ",";
    }

    printType(body...);
}


/////////////////////////////////////////
// tuple
/////////////////////////////////////////

// プライマリーテンプレート
template <int N, typename... Args>
struct tuple_data;

// 部分的特殊化
template <int N>
struct tuple_data<N>
{};

// 部分的特殊化
template <int N, typename Head, typename... Body>
struct tuple_data<N, Head, Body...> : public tuple_data<N + 1, Body...>
{
    Head value;
};

template <typename... Args>
struct tuple : public tuple_data<0, Args...>
{};


// tuple<...>のN番目の要素を参照 : get<N>()
template <int N, typename Head, typename... Body>
Head& get_tuple_data(tuple_data<N, Head, Body...>& t)
{
    return t.value;
}

// 派生クラスtuple<Args...>の基底クラスがtuple_datea<N, Head, Body...>なので
// 派生クラスtupel<Args...>のインスタンスを仮引数tuple_data<N, Head, Body...>& tに代入できる(ポリモーフィズム).
template <int N, typename... Args>
auto get(tuple<Args...>& t) -> decltype(get_tuple_data<N>(t))
{
    return get_tuple_data<N>(t);
}


/////////////////////////////////////////
// 非型の可変テンプレート
/////////////////////////////////////////

template <int... List>
std::vector<int> initializer()
{
    std::vector<int> v = {List...};
    return v;
}