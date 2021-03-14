#include "non_template_base_and_template_derived.hpp"

#include <iostream>
#include <cstdio>
#include <memory>

using namespace example;

struct hoge {
    hoge() { std::cout << "コンストラクタ" << std::endl; }
    ~hoge() { std::cout << "デストラクタ" << std::endl; }
    void something() const { std::cout << "何かする" << std::endl; }
};

void delete_hoge(hoge* p) {
    delete p;
    std::cout << "削除子を使用して解放" << std::endl;
}

void foo() {
    sp::shared_ptr<hoge> p(new hoge(), &delete_hoge);
    p->something();
}

int main(int argc, char** argv) {

    // BaseとDerivedによる型情報の消去
    {
        using namespace example;
        int used_param = 100;
        UseTemplateParam utp(used_param);
        utp.print();
    }

    // shared_ptrの使用
    {
        foo();
    }

    // カスタム削除子は、コンストラクタ/デストラクタなので管理されていないリソースを確実に解放する手段として使える.
    {
        // カスタム削除子(fclose)を指定してファイルを開く
        std::shared_ptr<FILE> p(fopen("test.txt", "wb"), fclose);
        if (p) {
            fwrite("abc", 3, 1, p.get()); // ファイルを使う
        }
    } // ここでfcloseされる

    return 0;
}