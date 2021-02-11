#include "enable_if.hpp"

#include <vector>
#include <list>
#include <iostream>

int main(int argc, char** argv)
{
    // ver1(仮引数の型)によるSFINAE with std::enable_if_t
    struct X {};
    check(X());
    check(3);

    // ver2(戻り値の型)によるSFINAE with std::enable_if_t
    class Y
    {
        int value;
    public:
        Y(int value) : value(value) {}

        Y add(const Y& y) const
        {
            return Y(value + y.value);
        }

        int getValue() const { return value; }
    };

    Y a(1);
    Y b(2);

    Y r = a + b;
    std::cout << r.getValue() << std::endl;

    // ver3(関数テンプレートのデフォルトテンプレート引数) with std::enable_if_t SFINAE
    check_class(X());
    check_class(5L);

    // ver4(専門特化した実装を持っているかどうかでオーバーロードする)
    std::vector<int> v = {3,1,4};
    std::list<int> ls = {3,1,4};

    sort(v); // sort(v.begin(), v.end())
    sort(ls); // ls.sort()

    for (int x : v) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    for (int x : ls) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    return 0;
}