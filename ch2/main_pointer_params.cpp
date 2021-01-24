#include <iostream>
#include <string>

#include "pointer_params_of_template.hpp"

using namespace std;

class Cat
{
    int age_;
    string name_;
    int set_age(const int& age) { return age_ = age; }
    int get_age() const { return age_; }
    string set_name(const string& name) { return name_ = name; }
    string get_name() const { return name_; }
public:
    RWProperty<int, Cat, &Cat::get_age, &Cat::set_age> age;
    RWProperty<string, Cat, &Cat::get_name, &Cat::set_name> name;

    Cat() { age(this); name(this); }
};

int main(int argc, char** argv)
{
    Cat aCat;
    aCat.age = 4;       // 代入演算子
    aCat.name = "tama"; // 代入演算子
    int age = aCat.age; // 型変換演算子
    string name = aCat.name; // 同上
    std::cout << name << " is " << age << " years old." << std::endl;

    return 0;
}