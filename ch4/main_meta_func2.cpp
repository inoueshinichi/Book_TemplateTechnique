#include "meta_func2.hpp"

int main(int argc, char** argv) {

    // 複数の戻り値を持つメタ関数
    const int data[] = {1, 2, 3};
    const int* data_tmp = data;

    Is::iterator_traits<decltype(data_tmp)>::defference_type diff{0};
    Is::iterator_traits<decltype(data_tmp)>::value_type value{0};
    Is::iterator_traits<decltype(data_tmp)>::pointer_type const_ptr{0};
    Is::iterator_traits<decltype(data_tmp)>::reference_type ref{0}; // const 左辺値参照は右辺値を束縛できる
    Is::iterator_traits<decltype(data_tmp)>::iterator_category iter_tag;

    return 0;
}