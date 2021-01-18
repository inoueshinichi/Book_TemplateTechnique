#include "smalltalk.hpp"

#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    cout << "========== ch1 : smalltalk container ==========" << endl;
    Vector v;
    v.add(new Integer(12));
    v.add(new Integer(34));
    v.add(new String("mistake")); // エラー検出されない
    for (int i = 0; i < v.size(); ++i)
    {
        Integer* ptr = (Integer*)v.at(i);
        cout << ptr->value() << endl;
    }

    return 0;
}