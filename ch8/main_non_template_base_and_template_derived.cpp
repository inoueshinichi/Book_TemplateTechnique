#include "non_template_base_and_template_derived.hpp"

int main(int argc, char** argv) {

    // BaseとDerivedによる型情報の消去
    {
        using namespace example;
        int used_param = 100;
        UseTemplateParam utp(used_param);
        utp.print();
    }

    return 0;
}