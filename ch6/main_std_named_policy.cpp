#include "std_named_policy.hpp"

#include <iterator>
#include <cstdio>

#include <map>
#include <string>

int main(int argc, char** argv) {

    //////////////////////////////////////////////
    // stdに使用されている名前付きテンプレートの例
    //////////////////////////////////////////////

    // std::allocatorの使われ方 for vector
    int array[] = {1, 2, 3};
    Is::vector<int> v(std::begin(array), std::end(array));
    int size = (int)(sizeof(array) / sizeof(*array));
    std::printf("size: %d\n", size);
    for (int i = 0; i < size; ++i) {
        std::printf("%dth -> %d\n", i, v.at(i));
    }

    // ↑ for map
    std::map<int, std::string, std::greater<int>> dict { 
        {3, "3rd"},
        {1, "1st"},
        {4, "4th"}
    };

    for (int i = 0; const auto& x : dict) {
        std::printf("%d -> (%d, %s)\n", i, x.first, x.second.c_str());
        i += 1;
    }

    // ソート済みコンテナ
    Is::sorted_vector<int, Is::less_policy> sorted_vec;
    sorted_vec.push_back(3);
    sorted_vec.push_back(1);
    sorted_vec.push_back(4);
    sorted_vec.print();
    
    return 0;
}