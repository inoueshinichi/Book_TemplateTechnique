#pragma once

#include <vector>

// 一時オブジェクトのコスト
namespace math {

    class vector {
    public:
        static constexpr int N = 3; // 次元数

        vector() {
            for (size_t i = 0; i < N; ++i) {
                values_[i] = 0;
            }
        }

        vector(const vector& rhs) {
            for (size_t i = 0; i < N; ++i) {
                values_[i] = rhs[i];
            }
        }

        vector& operator=(const vector& rhs) {
            for (size_t i = 0; i < N; ++i) {
                values_[i] = rhs[i];
            }
            return *this;
        }

        vector& operator+=(const vector& rhs) {
           for (size_t i = 0; i < N; ++i) {
                values_[i] += rhs[i];
            }
            return *this;
        }

        float& operator[](size_t i) { return values_[i]; }
        float operator[](size_t i) const { return values_[i]; }

    private:
        float values_[N];
    };

    // コピーコンストラクタが呼ばれる
    vector operator+(const vector& lhs, const vector& rhs) {
        // パラメータがconstになっているため、左辺の値を変更できず、一時オブジェクトが必要になる.
        vector tmp(lhs);
        tmp += rhs;
        return tmp;
    }
}


namespace expression_template {

    // Expression Template
    // 式の一部(x+y)を評価していくのではなく、
    // 式の全体(t = x + y + z)が現れたときに、つまり、代入が行われたときに
    // 全体を一度に評価することで、不要な計算を行わせないこと.
    // Expression Templateという手法では、(x+y+z)という式をoperatpr+で
    // それぞれ、計算するのではなく(x+y+z)という式の構造を保存しておき、
    // 必要になったとき(ここでは、代入演算子が呼ばれたとき)に計算するという遅延評価を実現する.
    // Expression Templateのために用意するのは(+),(-),(*),(/)のような各演算を行う小さなクラス.

    // (+)クラス
    template <class L, class R>
    class plus {
        const L& l_;
        const R& r_;
    public:
        plus(const L& l, const R& r)
            : l_(l)
            , r_(r) {}
        
        float operator[](size_t i) const {
            return l_[i] + r_[i];
        }
    };

    // (*)クラス
    template <class L, class R>
    class multiply {
        const L& l_;
        const R& r_;
    public:
        multiply(const L& l, const R& r)
            : l_(l)
            , r_(r) {}
        
        float operator[](size_t i) const {
            return l_[i] * r_[i];
        }
    };



    // 改良したvector
    class vector {
    public:
        static constexpr int N = 3; // 次元数

        vector() {
            for (size_t i = 0; i < N; ++i) {
                values_[i] = 0;
            }
        }

        vector(const vector& rhs) {
            for (size_t i = 0; i < N; ++i) {
                values_[i] = rhs[i];
            }
        }

        // vector& operator=(const vector& rhs) {
        //     for (size_t i = 0; i < N; ++i) {
        //         values_[i] = rhs[i];
        //     }
        //     return *this;
        // }

        // plus<L,R>を受け取れる
        template <class E>
        vector& operator=(const E& rhs) {
            for (size_t i = 0; i < N; ++i) {
                values_[i] = rhs[i]; // plus[i]
            }
            return *this;
        }

        vector& operator+=(const vector& rhs) {
           for (size_t i = 0; i < N; ++i) {
                values_[i] += rhs[i];
            }
            return *this;
        }

        float& operator[](size_t i) { return values_[i]; }
        float operator[](size_t i) const { return values_[i]; }

    private:
        float values_[N];
    };

    // // コピーコンストラクタが呼ばれる
    // vector operator+(const vector& lhs, const vector& rhs) {
    //     // パラメータがconstになっているため、左辺の値を変更できず、一時オブジェクトが必要になる.
    //     vector tmp(lhs);
    //     tmp += rhs;
    //     return tmp;
    // }

    // operator+では計算はおこなわれず、plusクラスのオブジェクト、つまり左辺と右辺の変数、＋演算を行う
    // という情報が返される.
    template <class L, class R>
    plus<L, R> operator+(const L& l, const R& r) {
        return plus<L,R>(l, r); // moveしているからコピーは起きてない
    }


    template <class L, class R>
    multiply<L, R> operator*(const L& l, const R& r) {
        return multiply<L, R>(l, r); 
    }

}


// plus, multiplyといった二項演算子クラスはほとんどクラス構成がおなじなので、
// テンプレート化して、操作+,*などだけ別途オペレータクラスにする
namespace expression_template_operator {

    // 二項演算子のテンプレート
    template <class L, class Op, class R>
    class expression {
        const L& l_;
        const R& r_;
    public:
        expression(const L& l, const R& r)
            : l_(l)
            , r_(r) {}
        
        float operator[](size_t i) const {
            return Op::apply(l_[i], r_[i]);
        }
    };

    // 重複コードをなくした
    struct plus {
        static float apply(float l, float r) {
            return l + r;
        }
    };

    struct multiply {
        static float apply(float l, float r) {
            return l * r;
        }
    };


    // 更に改良したvector
    class vector {
    public:
        static constexpr int N = 3; // 次元数

        vector() {
            for (size_t i = 0; i < N; ++i) {
                values_[i] = 0;
            }
        }

        vector(const vector& rhs) {
            for (size_t i = 0; i < N; ++i) {
                values_[i] = rhs[i];
            }
        }

        // vector& operator=(const vector& rhs) {
        //     for (size_t i = 0; i < N; ++i) {
        //         values_[i] = rhs[i];
        //     }
        //     return *this;
        // }

        // plus<L,R>を受け取れる
        template <class E>
        vector& operator=(const E& rhs) {
            for (size_t i = 0; i < N; ++i) {
                values_[i] = rhs[i]; // plus[i]
            }
            return *this;
        }

        vector& operator+=(const vector& rhs) {
           for (size_t i = 0; i < N; ++i) {
                values_[i] += rhs[i];
            }
            return *this;
        }

        float& operator[](size_t i) { return values_[i]; }
        float operator[](size_t i) const { return values_[i]; }

    private:
        float values_[N];
    };

    // // コピーコンストラクタが呼ばれる
    // vector operator+(const vector& lhs, const vector& rhs) {
    //     // パラメータがconstになっているため、左辺の値を変更できず、一時オブジェクトが必要になる.
    //     vector tmp(lhs);
    //     tmp += rhs;
    //     return tmp;
    // }

    // // operator+では計算はおこなわれず、plusクラスのオブジェクト、つまり左辺と右辺の変数、＋演算を行う
    // // という情報が返される.
    // template <class L, class R>
    // plus<L, R> operator+(const L& l, const R& r) {
    //     return plus<L,R>(l, r); // moveしているからコピーは起きてない
    // }

    template <class L, class R>
    expression<L, plus, R> operator+(const L& lhs, const R& rhs) {
        return expression<L, plus, R>(lhs, rhs);
    }

    // template <class L, class R>
    // multiply<L, R> operator*(const L& l, const R& r) {
    //     return multiply<L, R>(l, r); 
    // }

    template <class L, class R>
    expression<L, multiply, R> operator*(const L& lhs, const R& rhs) {
        return expression<L, multiply, R>(lhs, rhs);
    }
}

