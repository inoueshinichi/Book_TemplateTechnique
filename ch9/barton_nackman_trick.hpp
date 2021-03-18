#pragma once

/**
 * @brief Barton-Nackman Trick
 * operator==やoperator<から関連する比較演算子を自動生成する仕組み.
 * friend関数とCRTPを組み合わせて使う.
 * 
 * 派生クラスに対する非メンバ関数を基本クラス側で自動的に定義する手法.
 */

// 通常[operator==]は非メンバ関数にするため、privateメンバの比較を行う場合は、
// operator==をfriendにするか、privateメンバへアクセスするための、getterを用意する.
namespace normal {

    // クラススコープ内で演算子を定義
    class hoge {
        int id_;
    public:
        explicit hoge(int id) : id_(id) {}

        // 一応、メンバ関数?
        friend bool operator==(const hoge& lhs, const hoge& rhs) { // 必ずinline定義
            return lhs.id_ == rhs.id_;
        }
    };
    // operator==をfriendとしてクラススコープ内でインライン定義することで、operator==を
    // あたかも非メンバ関数として定義したかのように振る舞わせることができる.
}


// friend関数とCRTPによるBarton-Nackman Trick
namespace barton_nackman_trick {

    template <class T>
    class equal_comparable {
        // Tクラスのoperator==を使ってoperator!=を定義
        friend bool operator!=(const T& lhs, const T& rhs) {
            return !lhs.operator==(rhs);
        }
    };

    template <class T>
    class less_than_camparable {
        friend bool operator>(const T& lhs, const T& rhs) {
            return rhs.operator<(lhs);
        }

        friend bool operator<=(const T& lhs, const T& rhs) {
            return !rhs.operator<(lhs);
        }

        friend bool operator>=(const T& lhs, const T& rhs) {
            return !lhs.operator<(rhs);
        }
    };

    class hoge : private equal_comparable<hoge> , less_than_camparable<hoge> {
        int id_;
    public:
        explicit hoge(int id) : id_(id) {}

        bool operator==(const hoge& rhs) const {
            return id_ == rhs.id_;
        }

        bool operator<(const hoge& rhs) const {
            return id_ < rhs.id_;
        }
    };
}


// Barton-Nackman Trickのルックアップ問題
namespace problem_of_lookup {

    struct hoge {
        friend bool operator==(const hoge& lhs, const hoge& rhs) {
            return true;
        }
    };
}


