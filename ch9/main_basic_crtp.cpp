#include "basic_crtp.hpp"


int main(int, char**)
{
    // 仮想関数による動的なポリモーフィズム
    {
        using namespace how_to;

        base* b = new derived();
        b->base_foo(); // derived::foo()

        delete b;   
    }

    // CRTPを使用した静的なポリモーフィズム
    {
        using namespace crtp;

        derived d;
        base<derived>& bd = d;
        bd.base_foo();

        d.base_foo(); // template_method
    }

    // 仮想関数によるTemplate Method パターン
    {
        using namespace template_method_with_vtable;

        derived d;
        d.interface_api(); // 基底クラスのインターフェースで、派生クラスの実装template_method_implが呼ばれる
    }

    // CRTPによるTemplate Method パターン
    {
        using namespace template_method_with_crtp;

        derived d;
        d.interface_api();
    }
}