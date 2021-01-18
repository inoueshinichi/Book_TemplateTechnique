#ifndef TEMPLATE_TEQUNIQUE_SMALLTALK_HPP
#define TEMPLATE_TEQUNIQUE_SMALLTALK_HPP

// 基底クラス
class Object
{
public:
    Object() = default;
    virtual ~Object() {}
};


// 可変長型配列
class Vector : public Object
{
    Object** data_;
    int capacity_;
    int size_;

public:
    Vector() : data_(0), capacity_(0), size_(0) {}

    ~Vector()
    {
        for (int i = 0; i < size_; ++i)
        {
            delete data_[i];
        }
        delete[] data_;
    }

    void add(Object* item)
    {
        if (size_ == capacity_)
        {
            capacity_ += 10;
            Object** tmp = new Object*[capacity_];
            for (int i = 0; i < size_; ++i)
            {
                tmp[i] = data_[i];
            }
            delete[] data_;
            data_ = tmp;
        }

        data_[size_++] = item;
    }

    Object* at(int index)
    {
        if (index < 0 || index >= size_)
        {
            return 0;
        }
        return data_[index];
    }

    int size() const { return size_; }
};


// Objectに仕立てる
class Integer : public Object
{
    int value_;
public:
    Integer(int v) : value_(v) {}

    int value() const { return value_; }
};

#include <cstring>

// Stringを追加する
class String : public Object
{
    char* value_;
public:
    String(const char* str)
    {
        std::strcpy(value_ = new char[std::strlen(str) + 1], str);
    }

    ~String() { delete[] value_; }

    const char* value() const { return value_; }
};


#endif // TEMPLATE_TEQUNIQUE_SMALLTALK_HPP