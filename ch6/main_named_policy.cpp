#include "named_policy.hpp"

int main(int argc, char** argv) {
    // 名前付きテンプレート
    smart_ptr<multi_thread<true>, ownership<reference_count>> p;
    smart_ptr<ownership<deep_copy>> dp;
    p.show_info();
    dp.show_info();
}