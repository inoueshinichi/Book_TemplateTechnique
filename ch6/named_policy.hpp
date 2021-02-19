#pragma once

#include <type_traits>
#include <cassert>
#include <typeinfo>
#include <iostream>

///////////////////
// 名前付きポリシー
///////////////////

// 名前付きテンプレートの引数
// 所有権の戦略
// Strategy型をカプセル化する
template <class Strategy>
struct ownership {
    using type = Strategy;
};

struct reference_count {};
struct deep_copy {};

// 名前付きテンプレートの引数
// マルチスレッドセーフか否か
// IsMultiThread型(bool)をカプセル化する
template <bool IsMultiThread>
struct multi_thread {
    static const bool value = IsMultiThread;
};

// 各ポリシーの判定を行うメタ関数 for ownership
template <class Strategy_Capsel> // Strategy_Capsel引数は無くてもOK
struct is_ownership_policy {
    static const bool value = false;
};
template <class Strategy>
struct is_ownership_policy<ownership<Strategy>> {
    static const bool value = true;
};

// ポリシーの判定を行うメタ関数 for multi thread
template <class MultiThread_Capsel> // MultiThread_Capsel引数は無くてもOK
struct is_multi_thread_policy {
    static const bool value = false;
};
template <bool IsMultiThread>
struct is_multi_thread_policy<multi_thread<IsMultiThread>> {
    static const bool value = true;
};


// 名前付きテンプレート引数を実装するには、可変引数テンプレートで受け取ったポリシーのリストから
// 必要なポリシーを取得してくるメタ関数が必要。
// get_required_policy
// get_optional_policy

// ポリシークラスのリストから対象ポリシークラスを探すメタ関数find_if
struct not_found {};

template <template <class> class Pred, class Head, class... Tail>
struct find_if_impl {
    using type = typename std::conditional<Pred<Head>::value, Head, typename find_if_impl<Pred, Tail...>::type>::type;
};

// template <template <class> class Pred, class Head, class... Tail>
// using conditional_t = std::conditional<Pred<Head>, find_if_impl<Pred, Tail...>::type;

// 特殊化
template <template <class> class Pred, class Head>
struct find_if_impl<Pred, Head> {
    using type = typename std::conditional<Pred<Head>::value, Head, not_found>::type;
};

// // 特殊化 空リストに対応
// template <template <class> class Pred>
// struct find_if_impl<Pred> {
//     using type = not_found;
// };

// インターフェース
template <template <class> class Pred, class... List>
struct find_if {
    using type = typename find_if_impl<Pred, List...>::type;
};

// get_required_policy
template <template <class> class Pred, class... List>
struct get_required_arg {
    using type = typename find_if<Pred, List...>::type;
    static_assert(!std::is_same<type, not_found>::value, "required policy not found");
};

// get_optional_policy
template <class Opt, template <class> class Pred, class... List>
struct get_optional_arg {
    using result = typename find_if<Pred, List...>::type;
    using type = typename std::conditional<!std::is_same<result, not_found>::value, result, Opt>;
};

// スマートポインタクラスの定義
template <class... Args>
struct smart_ptr {
    // 所有権管理の戦略を取得
    // (必ず指定する)
    using ownership_policy = typename get_required_arg<is_ownership_policy, Args...>::type;
    
    // マルチスレッドセーフか否かを取得
    // (指定されなかったら非マルチスレッドセーフ)
    using multi_thread_policy = typename get_optional_arg<multi_thread<false>, is_multi_thread_policy, Args...>::type;

public:
    void show_info() {
        std::cout << typeid(ownership_policy).name() << ", " << typeid(multi_thread_policy).name() << std::endl;
    };
};


////////////////////////////////////////////////////////////
// 名前付きテンプレートは実装が長いのでマクロを有効活用する
////////////////////////////////////////////////////////////

// 名前付きテンプレートの引数と判定用メタ関数
#define DEFINE_TYPE_NAMED_PARAM(param)                     \
    template <class T>                                     \
    struct param {                                         \
        using type = T;                                    \
    };                                                     \
                                                           \
    template <class>                                       \
    struct is_##param##_policy {                           \
        static const bool value = false;                   \
    };                                                     \
                                                           \
    tremplate <class T>                                    \
    struct is_##param##_policy<param<T>> {                 \
        static const bool value = true;                    \
    };

#define DEFINE_BOOL_NAMED_PARAM(param)                     \
    template <bool V>                                      \
    struct param {                                         \
        static const bool value = V;                       \
    };                                                     \
                                                           \
    template <class>                                       \
    struct is_##param##_policy {                           \
        static const bool value = false;                   \
    };                                                     \
                                                           \
    template <bool V>                                      \
    struct is_##param##_policy<param<V>> {                 \
        static const bool value = true;                    \
    };


