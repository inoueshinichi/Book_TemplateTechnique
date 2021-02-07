# TemplateTechnique
C++テンプレートテクニック第二版の実装</br>

C++11からC++14時代以降の変更として、以下を実装</br>
1) エイリアステンプレートの利用 CLASS<TemplateParams>::type -> CLASS_t<TemplateParams>を使用する.</br>
2) 変数テンプレートの利用       CLASS<TemplateParams>::valeu -> CLASS_v<TemplateParams>を使用する.</br>
3) 高階メタ関数型のコンパイル時if文は使用しない. 第一テンプレート引数のはbool型にしたほうが意味が明確!</br>
4) Chapter4のC++11時代のメタ関数でstd::declval()関数を使用した方法は分かりづらすぎるので、やらない.</br>
5) </br>

Chapter1: テンプレート前史</br>
Chapter2: テンプレートの基礎</br>
Chapter3: Generic Programingの基礎</br>
Chapter4: テンプレートメタプログラミング</br>
Chapter5: SFINE</br>
Chapter6: ポリシー</br>
Chapter7: コンセプト</br>
Chapter8: Type Erasure</br>
Chapter9: CRTP</br>
Chapter10: テンプレート型変換演算子</br>
Chapter11: Expression Template</br>
