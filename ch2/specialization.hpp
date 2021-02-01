#pragma once

#include <cstring>
#include <iostream>
#include <string>

///////////////////////////////////////////
// 明示的特殊化
///////////////////////////////////////////

// プライマリーテンプレート
template <typename T>
bool equal(T x, T y)
{
    return x == y;
}

// const char* 明示的特殊化
template <>
bool equal(const char* x, const char* y)
{
    return std::strcmp(x, y) == 0;
}

// プライマリーテンプレート
template <typename T>
class printer
{
public:
    void out(const T& value) const
    {
        std::cout << value << std::endl;
    }
};

// std::string 明示的特殊化
template <>
class printer<std::string>
{
public:
    void out(const std::string& value) const
    {
        // 文字列は""で囲む
        std:: cout << '"' << value << '"' << std::endl;
    }
};

///////////////////////////////////////////
// 部分特殊化
///////////////////////////////////////////
template <typename T>
class printer<T*>
{
public:
    void out(T* value) const
    {
        std::cout << *value << std::endl;
    }
};

// 関数テンプレートの部分特殊化はオーバーロードで実現する
template <typename T>
void print(T value) { std::cout << value << std::endl; }

template <typename T>
void print(T* value) { std::cout << *value << std::endl; }