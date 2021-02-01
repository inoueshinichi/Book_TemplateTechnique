#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>


// // 電話帳
// class Phonebook
// {
//     struct Record
//     {
//         std::string name;
//         std::string phone;
//         Record(const std::string& n, const std::string& p)
//             : name(n), phone(p) {}

//         friend std::ostream& operator<<(std::ostream& stream, const Record& r)
//         {
//             return stream << r.name << ":" << r.phone;
//         }
//     };

//     std::vector<Record> book_;

// public:
//     void add(const std::string& name, const std::string& phone)
//     {
//         book_.emplace_back(name, phone);
//     }

//     void print(std::ostream& stream) const
//     {
//         std::copy(std::begin(book_), std::end(book_), std::ostream_iterator<Record>(stream, "\n"));
//     }
// };



// 電話帳 (テンプレートテンプレートパラメータ)
template <template<typename T, typename A = std::allocator<T>> typename Container> 
class Phonebook
{
    struct Record
    {
        std::string name;
        std::string phone;
        Record(const std::string& n, const std::string& p)
            : name(n), phone(p) {}

        friend std::ostream& operator<<(std::ostream& stream, const Record& r)
        {
            return stream << r.name << ":" << r.phone;
        }
    };

    Container<Record> book_;

public:
    void add(const std::string& name, const std::string& phone)
    {
        book_.emplace_back(name, phone);
    }

    void print(std::ostream& stream) const
    {
        std::copy(std::begin(book_), std::end(book_), std::ostream_iterator<Record>(stream, "\n"));
    }
};