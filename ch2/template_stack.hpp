#ifndef TEMPLATE_TECHNIQUE_TEMPLATE_STACK_HPP
#define TEMPLATE_TECHNIQUE_TEMPLATE_STACK_HPP

template <typename T>
class Stack 
{
    T* data_;
    int index_;
    int capacity_;
public:
    explicit Stack(int n);
    ~Stack();
    void push(T x);
    T top() const;
    void pop();
    int size() const;
};
#endif // TEMPLATE_TECHNIQUE_TEMPLATE_STACK_HPP