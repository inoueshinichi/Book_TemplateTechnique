#pragma once

// メタ関数は以下の特徴を持つ
// 1) コンパイル時に計算が実行される(評価される)
// 2) 引数として定数とテンプレートパラメータが利用できる
// 3) メタ関数は状態を持たない(同じ入力に対して同じ出力が得られる)

template <int N>
struct incremental {
    static const int value = N + 1;
    // static constexpr int value = N;
};

// C++11からC++14時代への変更点
// 変数テンプレートを使って、クラス<params>::valueという記述を回避する
template <int N>
constexpr int incremental_v = incremental<N>::value; // valueは定数であって型名でないので意味がない


///////////////////////////////
// 再帰メタ関数
///////////////////////////////
template <int N>
struct factorial {
    static const int value = N * factorial<N-1>::value;
};

template <> // 終了条件
struct factorial<0> {
    static const int value = 1;
};

///////////////////////////////
// square
template <int N>
struct square {
    static const int value = N * N;
};

///////////////////////////////
// pow
template <int X, int N>
struct pow {
    static const int value = X * pow<X, N-1>::value;
};

template <int X> // 終了条件
struct pow<X, 0> {
    static const int value = 1;
};


// C++11以降では通常の関数をconstexprキーワードを使って
// コンパイル時計算できるようになった
constexpr int pow_con(int x, int n) { 
    return n == 0 ? 1 : x * pow_con(x, n-1);
}


/////////////////////////////////
// 型を操作するメタ関数
/////////////////////////////////
template <typename T>
struct identity {
    using type = T; // T型を返す
};

// エイリアステンプレート
template <typename T>
using identity_t = _identity<T>::type;