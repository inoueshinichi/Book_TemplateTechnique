#include "tag_dispatch.hpp"

#include <vector>
#include <list>
#include <iostream>

int main(int argc, char** argv)
{
    

    // std::advanceの利用(iteratorをN回進める)
    std::vector<int> vec = {1,2,3};
    std::list<int> lst = {1,2,3};

    auto iter_vec = std::begin(vec);
    std::advance(iter_vec, 1); // 1進める
    std::cout << *iter_vec << std::endl;

    auto iter_lst = std::begin(lst);
    std::advance(iter_lst, 1); // 1進める
    std::cout << *iter_lst << std::endl;

    // 自作Is::andvanceの利用
    Is::advance(iter_vec, 1);
    std::cout << *iter_vec << std::endl;
    Is::advance(iter_lst, 1);
    std::cout << *iter_lst << std::endl;
    

    return 0;
}