#include "template_stack.hpp"

template <typename T> 
Stack<T>::Stack(int n) 
    : capacity_(n), index_(0) 
{
    data_ = new T[capacity_];
}

template <typename T>
Stack<T>::~Stack()
{
    delete[] data_;
}

template <typename T>
void Stack<T>::push(T x)
{
    if (index_ < capacity_)
        data_[index_++] = x;
}

template <typename T> 
T Stack<T>::top() const
{
    return data_[index_ - 1];
}

template <typename T>
void Stack<T>::pop()
{
    if (index_ > 0)
        --index_;
}

template <typename T>
int Stack<T>::size() const
{
    return index_;
}

// *.cppにテンプレートを記述する場合、明示的インスタンス化が必要
// ただし、メンバ関数もすべてインスタンス化されてしまうので、
// テンプレートパラメータの型が実装していないメンバ関数を呼ぶと
// 未定義動作になる. その場合、回避策として個々のメンバ関数でインスタンス化する.
template class Stack<int>;

/*
e.g
template Util<int>::Util(const int&);
template void Util<int>::add(const int&);
template int Util<int>::get() const;
*/