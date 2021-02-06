#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <list>

#include <iostream>

namespace Is {
    using std::string;
    using std::ostringstream;

    ///////////////////
    // パラメータ化継承
    ///////////////////
    // 既存クラスに追加・修正を加えることができる

    // 文字列をそのまま出力するクラス
    class Plain {
    public:
        virtual ~Plain() {}

        string convert(const string& str) const {
            return str;
        }
    };

    // Bold装飾をするクラス
    template <typename Base>
    class Bold : public Base {
    public:
        virtual ~Bold() {}

        string convert(const string& str) const {
            return "<b>" + Base::convert(str) + "</b>";
        }
    };

    // Italic装飾をするクラス
    template <typename Base>
    class Italic : public Base {
    public:
        virtual ~Italic() {}

        string convert(const string& str) const {
            return "<i>" + Base::convert(str) + "</i>";
        }
    };

    ///////////////////////////////////////////////////////
    // 仮想関数を導入して多態的に振る舞うパラメータ化継承
    ///////////////////////////////////////////////////////
    class VirtualPlain {
    public:
        virtual ~VirtualPlain() {}

        virtual string convert(const string& str) const {
            return str;
        }
    };


    // Bold with virtual
    template <typename Base = VirtualPlain>
    class VirtualBold : public Base {
    public:
        using Base::Base; // コンストラクタを継承する(C++11)

        virtual ~VirtualBold() {}

        virtual string convert(const string& str) const override {
            return "<b>" + Base::convert(str) + "</b>";
        }
    };


    // Italic with virtual
    template <typename Base = VirtualPlain>
    class VirtualItalic : public Base {
    public:
        using Base::Base;

        virtual ~VirtualItalic() {}

        virtual string convert(const string& str) const override {
            return "<i>" + Base::convert(str) + "</i>";
        }
    };

    // Size
    template <typename Base = VirtualPlain>
    class VirtualSize : public Base {
        string size_;
    public:
        using Base::Base;

        virtual ~VirtualSize() {}

        VirtualSize(int s) {
            ostringstream ss;
            ss << s;
            size_ = ss.str();
        }

        virtual string convert(const string& str) const override {
            return "<font size='" + size_ + "'>" + Base::convert(str) + "</font>";
        }
    };

    /////////////////////////////////////////////
    // パラメータ化継承によって関数を追加する例
    /////////////////////////////////////////////
    template <typename Base>
    class Printable : public Base {
    public:
        using Base::Base;

        std::ostream& print_on(std::ostream& stream, const char* delim = " ") const {
            for (const auto& x : *this) {
                stream << x << delim;
            }
            return stream;
        }
    };
}




