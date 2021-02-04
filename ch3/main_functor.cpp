#include "functor.hpp"

#include <vector>
#include <iostream>
#include <iterator>

int main(int argc, char** argv)
{
    using namespace std;

    // 値が偶数か判定する関数オブジェクト
    auto is_even = [](int x) -> bool {
        return x % 2 == 0;
    };

    vector<int> v = {1,2,3};

    auto iter = Is::find_if(std::begin(v), std::end(v), is_even);
    if (iter != std::end(v))
    {
        cout << "find_if -> " << *iter << endl;
    }

    return 0;
}