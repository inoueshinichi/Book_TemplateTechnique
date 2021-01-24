#pragma once

// プロパティの実装
// テンプレートパラメータにポインタを使用する

template <typename T, typename Object, 
            T (Object::*real_getter)() const, 
            T (Object::*real_setter)(const T&)>
class RWProperty
{
    Object* my_object_;

public:
    // プロパティの所有者を設定
    void operator()(Object* obj) { my_object_ = obj; }

    // 関数呼び出しによるget/set
    T operator()() const
    {
        return (my_object_->*real_getter)();
    }

    T operator()(const T& value)
    {
        return (my_object_->*real_setter)(value);
    }

    // メンバ関数get/set
    T get() const
    {
        return (my_object_->*real_getter)();
    }

    T set(const T& value)
    {
        return (my_object_->*real_setter)(value);
    }

    // (型変換演算子)
    operator T() const 
    {
        return (my_object_->*real_getter)();
    }

    // `=`演算子によるアクセス
    T operator=(const T& value)
    {
        return (my_object_->*real_setter)(value);
    }

    using value_type = T;
};