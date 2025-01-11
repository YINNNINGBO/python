#include <iostream>
using namespace std;

//     常成员函数
// 函数内你 只能对成员读，不更更改成员值
// 同名的常函数与 普通函数之间 构成了 重载的关系
class A
{
private:
    string name;
    mutable int age; // mutable 修饰的变量常函数也可以修改

public:
    A(string name = "null", int age = 0)
    {
        this->name = name;
        this->age = age;
        cout << " A(string name = null, int age = 0)"
             << "name  = " << name
             << ": age = " << age << endl;
    }
    // error
    /* 原理同：void add(const A * this): */
    //  void add(void) const
    //  {
    //      age++;
    //  }
    void const_add(void) const
    {
        age;
    }
    void printf(void)
    {
        cout << "printf(void)" << endl;
    }
};
int main(void)
{
    A a1("张飞", 18);
    const A a2;
    a2.const_add(); // 常对象只能调用常函数
    // a2.printf();   //error常对象只能调用普通函数
    return 0;
}