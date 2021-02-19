#pragma once

#include <iostream>
#include <string>

#include <fstream>

//////////////////////////////////////
// ポリシーとポリシークラス
//////////////////////////////////////
struct debug_log {
    static void print(const std::string& value)
    {
        std::cout << value << std::endl;
    }
};

struct release_log {
    static void print(const std::string&) {}
};

struct file_log {
    static void print(const std::string& value)
    {
        std::ofstream file("./log.txt");
        file << value << std::endl;
    }
};

template <class LogPolicy>
struct hoge {
    void foo() const 
    {
        LogPolicy::print("Fatal Error!!!");
    }
};

/////////////////////////////////
// カスタマイズ性の高いクラス設計
/////////////////////////////////
// スマートポインタの実装形式
// 1. 参照カウント方式
// 2. ディープコピー方式
// 3. 書き込み時コピー方式
// 4. 参照リンク方式
// 5. 破壊型コピー方式
// etc

// 継承による設計は、直交する機能の組み合わせを継承で表現
// しようとした場合、多重継承を用いることになり、オプションを
// 増やすたびに指数関数的に組み合わせの継承関係が増えてしまう。

// ポリシーベースの設計ではM*NがM+Nの組み合わせ関係に落ち着く.

class single_thread_model {};
class multi_thread_model {};

class reference_count {};
class deep_copy {};
class copy_on_write {};

// スマートポインタ<所有権管理方式, スレッドモデル>
template <class Ownership, class ThreadModel>
class smart_ptr {};

// シングルスレッドの参照カウント方式のスマートポインタ
smart_ptr<reference_count, single_thread_model> ptr_1;
// マルチスレッドのディープコピー方式のスマートポインタ
smart_ptr<deep_copy, multi_thread_model> ptr_2;
// マルチスレッドの書き込み時コピー方式のスマートポインタ
smart_ptr<copy_on_write, multi_thread_model> ptr_3;


/////////////////////////////////////
// ポリシーに基づく設計の実装パターン
/////////////////////////////////////
// 1) staticメンバ関数を持つポリシークラス -> ポリシークラスは状態を持たない
// 2) 非静的メンバ関数を持つポリシークラス -> ポリシークラスは状態を持つ
// 3) 継承によるポリシークラス -> ポリシークラスは状態を持つ。また、
// インスタンスメンバを持つポリシークラスをパラメータ化継承することで、
// ポリシークラスを扱う側がテンプレートパラメータの型ごとにメンバ関数の増減や種類を制御できる。
// ポリシーを受け取る側はあらゆる目的に使用できる抽象的なメンバ関数を定義する。

// 1) staticメンバ関数を持つポリシークラス -> ポリシークラスは状態を持たない
struct static_policy {
    static void foo(){
        std::cout << "static_policy" << std::endl;
    }
};

template <class Policy>
struct static_widget {
    void do_something() {
        Policy::foo();
    }
};


// 2) 非静的メンバ関数を持つポリシークラス -> ポリシークラスは状態を持つ
struct non_static_policy {
    void foo() {
        std::cout << "non_static_policy" << std::endl;
    }
};

template <class Policy>
class non_static_widget {
    Policy policy_;
public:
    void do_something()
    {
        policy_.foo();
    }
};

// 3) 継承によるポリシークラス -> ポリシークラスは状態を持つ
// また、テンプレートパラメータごとに自由にメンバ変数・関数の増減を制御できる
struct non_static_policy_with_extension {
protected:
    void foo() {
        std::cout << "non_static_policy_with_extension" << std::endl;
    }
};

template <class Policy>
class non_static_widget_with_extension : public Policy {
public:
    void do_something() {
        Policy::foo();
    }
};

//////////////////////
// デフォルトポリシー
//////////////////////
struct cout_policy {
    static void foo(const std::string& value) {
        std::cout << value << std::endl;
    }
};

struct printf_policy {
    static void foo(const std::string& value) {
        std::printf("%s\n", value.c_str());
    }
};

template <class Policy = cout_policy>
struct default_widget {
    void do_something() {
        Policy::foo("Hello");
    }
};

