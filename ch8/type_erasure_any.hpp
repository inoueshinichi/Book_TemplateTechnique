#pragma once

#include <typeinfo>

////////////////////////////////////////////////////////////////////////
// 非テンプレート基本クラスとテンプレート派生クラスでanyクラスを実装する
////////////////////////////////////////////////////////////////////////
// anyクラス内部に非テンプレート基本クラスとテンプレート派生クラスを持つ
// 動的な型の切り替えは、テンプレートコンストラクタとoperator=をカスタムする

class any {

    // 非テンプレート基本クラス
    struct holder_base {
        virtual ~holder_base() {}
        virtual holder_base* clone() const = 0; // コピー対応
        virtual const std::type_info& type() const = 0; // anyに現在何の型が保持されているかチェック
    };

    // テンプレート派生クラス
    template <class T>
    struct holder : public holder_base {
        T value_;
        holder(const T& value) : value_(value) {}

        virtual holder_base* clone() const override { // コピー対応
            return new holder(value_);
        }

        virtual const std::type_info& type() const override {
            // 実行時型情報(RTTI)であるstd::type_infoで型を判断
            return typeid(T);
        }
    };


    // 基本クラスのポインタ
    holder_base* content_;

public:
    template <class T>
    any(const T& value)
        : content_(new holder<T>(value)) {}
    
    ~any() {
        delete content_;
    }

    template <class T>
    any& operator=(const T& value) {
        delete content_;
        content_ = new holder<T>(value);
        return *this;
    }

    any(const any& other) // コピー対応
        : content_(other.content_ ? other.content_->clone() : nullptr) {}
    
    any& operator=(const any& other) {
        delete content_;
        content_ = other.content_ ? other.content_->clone() : nullptr;
        return *this;
    }

    // anyクラスでもRTTIを利用できるようにする
    const std::type_info& type() const {
        return content_ ? content_->type() : typeid(void);
    }

    // 保持している値を取り出す
    template <class T>
    const T& cast() const {
        return dynamic_cast<holder<T>&>(*content_).value_;
    }
};
