#pragma once

#include <tuple>
#include <type_traits>

/////////////////////////////////////////
// 型リスト(可変長テンプレートパラメータ)
/////////////////////////////////////////
// 基本は先頭とその他への分解
template <typename Head, typename... Tail>
struct g {
    using head = Head;
    using tail = std::tuple<Tail...>;
};


template <typename... List>
struct f {
    using head = g<List...>::head;
    using tail = g<List...>::tail;
};


//////////////////
// any_ofメタ関数
//////////////////
template <template <typename> typename Pred, 
          typename Head, typename... Tail>
struct any_of {
    static const bool value = Pred<Head>::value ? true : any_of<Pred, Tail...>::value;
};

template <template <typename> typename Pred,
          typename Head>
struct any_of<Pred, Head> {
    static const bool value = Pred<Head>::value;
};

// 変数テンプレート
template <template <typename> typename Pred, 
          typename Head, typename... Tail>
constexpr bool any_of_v = any_of<Pred, Head, Tail...>::value;

template <typename Type>
struct is_int {
    static const bool value = false;
};

template <>
struct is_int<int> {
    static const bool value = true;
};


//////////////////////////////////////////////////////////////////
// any_ofメタ関数(改) パラメータパックに空が入っても対応できるver
//////////////////////////////////////////////////////////////////
// インスタンス化できないプライマリー
template <template <typename> typename Pred, typename List>
struct any_of_kai_impl;

template <template <typename> typename Pred, typename Head, typename... Tail>
struct any_of_kai_impl<Pred, std::tuple<Head, Tail...>> {
    static const bool value = Pred<Head>::value ? true : any_of_kai_impl<Pred, Tail...>::value;
};


template <template <typename> typename Pred>
struct any_of_kai_impl<Pred, std::tuple<>> {
    static const bool value = false;
};

// 皮テンプレート
template <template <typename> typename Pred, typename... List>
struct any_of_kai {
    static const bool value = any_of_kai_impl<Pred, std::tuple<List...>>::value;
};

////////////////////////////////////////////////////////////////
// transformメタ関数 型リストの個々の型に対して同じ型操作を行う
///////////////////////////////////////////////////////////////
struct has_type_impl {
    template <class U>
    static std::true_type check(typename U::type*); // SFINE

    template <class U>
    static std::false_type check(...);
};

template <class TF>
struct has_type : public decltype(has_type_impl::check<TF>(nullptr))
{};

// Fはtypeを持っているstd::remove_reference系とtypeをもたないstd::remove_reference_t系があるから
// 以下をSFINEで内容を切り替えたい.
template <template <class> class F, class... List>
struct transform {
    using type = std::tuple<typename F<List>::type...>;
};


// template <template <class> class F, class... List>
// struct transform {
//     using type = std::tuple<typename F<List>...>;
// };


template <template <class> class F, class... List>
using transform_t = transform<F, List...>::type;
