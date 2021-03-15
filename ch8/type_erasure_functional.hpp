#pragma once

#include <type_traits>

////////////////////////
// std::function<>の実装
////////////////////////
// functionでは、仮想関数テーブル版に似たType Erasureを使用しており、
// void*に実体を保持し、消去された型情報を別のクラステンプレートで管理する、
// という方法で型安全なType Erasureを実現している
namespace example {

    /////////////////////////////////////////////////////////////////////////
    // どのように関数ポインタと関数オブジェクトを同一で扱えるようにしているか
    /////////////////////////////////////////////////////////////////////////
    // functionは、同じ形(戻り値と引数の型が同じ)の関数ポインタと関数オブジェクト
    // を同じように扱うことができるため、非常に強力

    /* 実装したいテンプレートクラス

    // 関数ポインタ/関数オブジェクトの型ではなく、関数の形をテンプレートパラメータで受け取るようになっている
    template <class Signature>
    class function;

    // 戻り値のみのfunction
    template <class R>
    class function<R()> {};

    // 戻り値と引数1つのfunction
    template <class R, class Arg>
    class function<R(Arg)> {};

    // ... その他、複数引数の場合の特殊化

    // functionは、戻り値の型と引数の型だけをテンプレートパラメータで持っている.

    */

    //////////////
    // any_pointer
    //////////////
    // unionを使用して関数ポインタと関数オブジェクトを1つのメモリ領域に保持する.
    // 関数ポインタとvoid*はキャストできないため、関数ポインタと関数オブジェクトのフィールドを分けてある.
    union any_pointer {
        void (*func_ptr)(); // 関数ポインタ
        void* obj_ptr;      // 関数オブジェクト
    };


    // functionでのType Erasure
    // 関数ポインタと関数オブジェクトそれぞれの実行、解放、複製を管理するクラス
    
    // 関数ポインタの管理クラス
    // 関数ポインタ本来の型情報を保持している.
    template <class Func, class R>
    struct function_ptr_manager {
        
        static R invoke(any_pointer function_ptr) {
            Func func = reinterpret_cast<Func>(function_ptr.func_ptr);
            return func();
        }

        static void destroy(any_pointer) {} // 関数ポインタは解放の必要がないのでdestory()は何もしない.
    };

    // 関数オブジェクトの管理クラス
    // 関数オブジェクト本来の型情報を保持している.
    template <class Func, class R>
    struct function_obj_manager {

        static R invoke(any_pointer func_obj_ptr) {
            Func* func = reinterpret_cast<Func*>(func_obj_ptr.obj_ptr);
            return (*func)();
        }

        static void destroy(any_pointer func_obj_ptr) {
            // void*になったままの関数オブジェクトでは、デストラクタが正しくよばれないので、
            // 本来の型にキャストしてからdeleteする.
            Func* func = reinterpret_cast<Func*>(func_obj_ptr.obj_ptr);
            delete func;
        }
    };


    ////////////////////////////////////////
    // Type Erasureを使用したfunctionの実装
    ////////////////////////////////////////
    // any_pointer, function_ptr_manager, function_obj_managerを使用して実装する.

    template <class Signature>
    class function;

    // 戻り値一つのfunction特殊化
    template <class R>
    class function<R()> {
        R (*invoke_)(any_pointer);
        void (*destroy_)(any_pointer);
        any_pointer functor_;

        void clear() {
            if (destroy_) {
                destroy_(functor_);
            }
            destroy_ = nullptr;
        }

    public:
        function()
            : invoke_(nullptr)
            , destroy_(nullptr) {}
        
        ~function() {
            clear();
        }

        template <class Func>
        void set_function_ptr(Func func_ptr) {
            clear();
            invoke_ = &function_ptr_manager<Func, R>::invoke;
            destroy_ = &function_ptr_manager<Func, R>::destroy;
            functor_.func_ptr = reinterpret_cast<void(*)()>(func_ptr);
        }

        template <class Func>
        void set_function_obj(Func func_obj) {
            clear();
            invoke_ = &function_obj_manager<Func, R>::invoke;
            destroy_ = &function_obj_manager<Func, R>::destroy;
            functor_.obj_ptr = reinterpret_cast<void*>(new Func(func_obj)); // コピーコンストラクタのnew
        }

        R operator()() {
            return invoke_(functor_);
        }

        ///////////////////////////////
        // std::enable_if_tによるSFINAE
        ///////////////////////////////
        // operator=をテンプレートパラメータの種類によってオーバーロードする

        // func_ptr
        template <class Func, std::enable_if_t<std::is_pointer_v<Func>, std::nullptr_t> = nullptr>
        function& operator=(Func func) {
            set_function_ptr(func);
            return *this;
        }

        // functor
        template <class Func, std::enable_if_t<!std::is_pointer_v<Func>, std::nullptr_t> = nullptr>
        function& operator=(Func func) {
            set_function_obj(func);
            return *this;
        }

        /**
         * @brief タグディスパッチによるSFINAEもできる
         * // タグ
         * struct function_ptr_tag {}; // 関数ポインタ
         * struct function_obj_tag {}; // 関数オブジェクト
         * 
         * // タグを返すメタ関数
         * template <class Func>
         * struct get_function_tag {
         *  using type = typename std::conditional<std::is_pointer<Func>::value, function_ptr_tag, function_obj_tag>::type;
         * };
         * 
         * template <class FuncPtr>
         * void assign_to(FuncPtr func_ptr, function_ptr_tag) {
         *  set_function_ptr(func_ptr);
         * }
         * 
         * template <class FuncObj>
         * void assign_(FuncObj func_obj, function_obj_tag) {
         *  set_function_obj(func_obj);
         * }
         * 
         * template <class Func>
         * function& operator=(Func func) {
         *  using func_tag = typename get_function_tag<Func>::type;
         *  assign_to(func, func_tag());
         *  return *this;
         * }
         * 
         */
    };
}