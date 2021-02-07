#pragma once


///////////////////
// コンパイル時if文
///////////////////

// プライマリー
template <bool Cond, typename Then, typename Else> // Condはbool型
struct if_;

// Cond = true
template <typename Then, typename Else>
struct if_<true, Then, Else> {
    using type = Then;
};

// Cond = false
template <typename Then, typename Else>
struct if_<false, Then, Else> {
    using type = Else;
};

// エイリアステンプレート
template <bool Cond, typename Then, typename Else>
using if_t = if_<Cond, Then, Else>::type;


/////////////////////////////////
// 高階メタ関数とコンパイル時if文
/////////////////////////////////

namespace Is {
    // find_ifは高階関数
    template <typename Iterator, typename Predicate>
    Iterator find_if(Iterator first, Iterator last, Predicate pred) {
        for (; first != last; ++first) {
            if (pred(*first)) {
                break;
            }
        }
        return first;
    }

    // 偶数?
    struct is_even {
        using result_tpe = bool;
        bool operator()(int x) const {
            return x % 2 == 0;
        }
    };

    // 奇数?
    auto is_odd = [](int x) -> bool {
        return !is_even()(x);
    };

}