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

// -----------------------------

template <typename T, int N>
struct add_pointers {
    using type = add_pointers<T, N-1>::type*;
};

template <typename T>
struct add_pointers<T, 0> {
    using type = T;
};

template <typename T, int N>
using add_pointers_t = add_pointers<T, N>::type;

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

/////////////////////////////////
/* 受け取ったT型をそのまま返す */
template <typename T>
struct identity {
    using type = T; // T型を返す
};

// エイリアステンプレート
template <typename T>
using identity_t = identity<T>::type;


////////////////////////////////////////
/* 受け取ったT型のポインタ型T*を返す */
template <typename T>
struct add_pointer {
    using type = T*; // ポインタ型を返す
};

// エイリアステンプレート
template <typename T>
using add_pointer_t = add_pointer<T>::type; 


//////////////////////////////////////////////
/* 受け取ったT型のconst参照型const T&を返す */
template <typename T>
struct add_clr {
    using type = const T&;
};

// エイリアステンプレート
template <typename T>
using add_clr_t = add_clr<T>::type;


/////////////////////////////////////////////////
// 型を操作するメタ関数は小さい粒度で作成すること
/////////////////////////////////////////////////

template <typename T>
struct add_const {
    using type = const T;
};
template <typename T>
using add_const_t = add_const<T>::type;

// ----------------------------------------------------------
template <typename T>
struct add_lvalue_reference {
    using type = T&;
};

// Tに左辺値参照型が入力されたときに対処するために部分特殊化
template <typename T>
struct add_lvalue_reference<T&> {
    using type = T&;
};

// エイリアステンプレート
template <typename T>
using add_lvalue_reference_t = add_lvalue_reference<T>::type;

// ----------------------------------------------------------

// 小さい粒度のメタ関数を組み合わせる(C++11とは違う)
template <typename T>
using add_clr_mix_t = add_const_t<add_lvalue_reference_t<T>>;


////////////////////////
// 型修飾を外すメタ関数
////////////////////////

/* remove const */
template <typename T> // プライマリーテンプレート
struct remove_const {
    using type = T;
};

template <typename T> // 部分特殊化でParamTypeがconst Tのとき、戻り値をTにする
struct remove_const<const T> {
    using type = T;
};

template <typename T>
using remove_const_t = remove_const<T>::type;

// 部分特殊化したテンプレートクラスに対するエイリアステンプレートは必要無いみたい
// template <typename T>
// using remove_const_t = remove_const<const T>::type;



/* remove volatile */
template <typename T>
struct remove_volatile {
    using type = T;
};

template <typename T>
struct remove_volatile<volatile T> {
    using type = T;
};

template <typename T>
using remove_volatile_t = remove_volatile<T>::type;



/* remove const volatile */
template <typename T>
using remove_cv_t = remove_const_t<remove_volatile_t<T>>;

