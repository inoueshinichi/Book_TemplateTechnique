#include "enable_shared_from_this.hpp"


int main(int, char**)
{
    // std::enable_shared_from_thisの使用例
    {
        using namespace how_to;
        std::shared_ptr<X> p(new X()); // 本来は、ファクトリ関数を作って, shared_ptrを外部に公開し、生ポインタは公開させない.
        p->f();
    }

    // 簡易クラスmy_enable_shared_fromの使用例
    {
        using namespace easy_implement;

        std::shared_ptr<X> p(new X());
        p->setup_shared_from_this(p);

        p->f();
    }
}