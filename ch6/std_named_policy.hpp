#pragma once

#include<type_traits>

#include <algorithm>
#include <string>
#include <iostream>
#include <vector>


//////////////////////////////////////////////
// stdに使用されている名前付きテンプレートの例
//////////////////////////////////////////////

//////////////////
// std::allocator
// アロケータに最低限必要なインターフェース
template <class T>
struct MyAllocator {
    using type_value = T; // 要素型

    // 別型から受け取るコピーコンストラクタ
    template <class U>
    MyAllocator(const MyAllocator<U>& other);

    // 特殊関数
    MyAllocator();
    MyAllocator(const MyAllocator&);
    MyAllocator(MyAllocator&&);

    // メモリ確保
    T* allocate(std::size_t n, void* hint = 0);

    // メモリ解放
    void deallocate(T* p, std::size_t n);
};

template <class T, class U>
bool operator==(const MyAllocator<T>&, const MyAllocator<U>&);

template <class T, class U>
bool operator!=(const MyAllocator<T>&, const MyAllocator<U>&);


///////////////////////
// アロケータの使われ方

#include <memory>
#include <stdexcept>

namespace Is {

    // vector
    template <class T, class Allocator = std::allocator<T>>
    class vector {
        T* values_;
        std::size_t size_;
        Allocator alloc_; // 状態を持つポリシークラス
    public:
        template <class Iterator>
        vector(Iterator first, Iterator last) {
            size_ = last - first;
            values_ = alloc_.allocate(size_, 0); // ポリシーに基づく設計
            for (std::size_t i = 0; i < size_; ++i) {
                std::allocator_traits<Allocator>::construct(alloc_, &values_[i], *first++);
            }
        }

        ~vector() {
            for (std::size_t i = 0; i < size_; ++i) {
                std::allocator_traits<Allocator>::destroy(alloc_, &values_[i]);
            }
            alloc_.deallocate(values_, size_); // ポリシーに基づく設計
        }

        const T& at(std::size_t index) const {
            if (index < 0 || index >= size_)
                throw std::runtime_error("Error: out of range");
            
            return values_[index];
        }
    };


    // map // std::less<Key>, std::allocator<std::pair<const Key, T>>がポリシーに基づく設計になっている.
    template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T>>>
    class map {
        // mapの実装は難しいので省略
    };

    
    // mapの代わりにソート済みコンテナを実装(ポリシークラスを利用するクラス)
    template <class T, template <class> class ComparePolicy>
    class sorted_vector {
        std::vector<T> vec_;
    public:
        void push_back(const T& value) {
            vec_.push_back(value);
            std::sort(std::begin(vec_), std::end(vec_), &ComparePolicy<T>::compare); // ポリシー設計
        }

        void print() {
            for (const T& x : vec_) {
                std::cout << x << std::endl;
            }
        }
    };

    // ポリシークラス1
    template <class T>
    struct less_policy {
        static bool compare(const T& lhs, const T& rhs) {
            return lhs < rhs;
        }
    };

    // ポリシークラス2
    template <class T>
    struct greater_policy {
        static bool compare(const T& lhs, const T& rhs) {
            return lhs > rhs;
        }
    };
}

