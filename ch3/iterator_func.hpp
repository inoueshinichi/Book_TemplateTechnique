#pragma once

#include <iterator>

/* イテレータの種類
Input Iterator: 最も機能の少ないイテレータ. 
                operator++による前方への横断, opeartor*による間接参照が可能. 
                標準のすべてのコンテナのイテレータがこれに合致する.

Forward Iterator: 入力イテレータに加え、operator*を介しての要素の書き換えが可能なイテレータ.
                  std::forward_listのイテレータがこれに合致する.

Bidirectional Iterator: 前方イテレータに加え、operator--による後方への横断が可能なイテレータ.
                        std::list, std::set, std::mapのイテレータがこれに合致する.

Random Access Iterator: 双方向イテレータに加え、operator[]やoperator+=, operator-=によって、
                        任意の位置にアクセスできるイテレータ.
                        std::vector, std::dequeのイテレータ、組み込み配列のポインタがこれに合致する.

Output Iterator: 他のコンテナやストリームに出力するアルゴリズムを設計する場合、出力イテレータを使用する.
                 コンテナを対象としない特殊なイテレータで、
                 operator*で間接参照されたオブジェクトに値を代入することで、要素を書き込む. 
                 operator++で次の要素に移動する.
*/

namespace Is
{
    // イテレータによるfind()アルゴリズムの実装
    template <typename Iterator, typename T>
    Iterator find(Iterator first, Iterator last, const T& value)
    {
        while (first != last)
        {
            if (*first == value)
            {
                break;
            }
            ++first;
        }
        return first;
    }

    // copy()アルゴリズムの実装
    template <typename InputIterator, typename OutputIterator>
    OutputIterator copy(InputIterator first, InputIterator last, OutputIterator out)
    {
        while (first != last)
        {
            *out = *first;
            ++first;
            ++out;
        }
        return out;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////
    // std::back_inserter : std::back_insert_iteratorを作るヘルパ関数(関数テンプレートの型推論を利用)
    // std::back_insert_iteratorは<iterator>ヘッダーで以下のように実装されている.
    template <typename Container>
    class back_insert_iterator : std::iterator<std::output_iterator_tag, void, void, void, void>
    {
    public:
        explicit back_insert_iterator(Container& c) : container(&c) {}

        back_insert_iterator& operator=(typename Container::value_type& value)
        {
            container->push_back(value);
            return *this;
        }

        back_insert_iterator& operator=(typename Container::value_type&& value)
        {
            container->push_back(std::move(value));
            return *this;
        }

        back_insert_iterator& operator*() { return *this; }
        back_insert_iterator& operator++() { return *this; }
        back_insert_iterator& operator++(int) { return *this; }
    
    protected:
        Container* container;
    };

    ////////////////////////////
    // std::back_inserterの実装
    template <typename C>
    back_insert_iterator<C> back_inserter(C& c)
    {
        return back_insert_iterator<C>(c);
    }
    
}




