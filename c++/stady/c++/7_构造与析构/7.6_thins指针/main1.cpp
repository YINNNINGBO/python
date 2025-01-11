#include <iostream>
using namespace std;
/**  this 是一个用于标识自身的隐式指针

*/
class A
{
    string name;
    int age;

public:
    // 成员函数中有一个不显示的隐式的参数 this
    // eg:  A(A *this ,string n = " NULL", int a = 0) : name(n), age(a)
    A(string n = " NULL", int a = 0) : name(n), age(a)
    {
        cout << "A(string n = NULL, int a= 0):name(n),age(a)"
             << endl;
    }
    void my_printf(void)
    {
        cout << "name = " << name << "; age  = " << age << endl;
    }
    // this 指针显现的样子
    //  void my_printf(A * this)
    //  {
    //      cout << "name = " << this->name << "; age  = " << this->age << endl;
    //  }
};
int main(void)
{
    // a1 a2类内的局部变量（name , age）存储在栈区的不同位置
    // a1 a2类内的函数存储在代码区，且只有一段my_printf函数代码
    // 通过this指针传递不同对象的不同成员给成员函数
    A a1("张飞", 22); // A a1(&a1,"张飞", 22);
    A a2("李逵", 19);
    a1.my_printf(); //  a1.my_printf(&a1);
    a2.my_printf(); //  a2.my_printf(&a2);
    return 0;
}
/*
./main1
A(string n = NULL, int a= 0):name(n),age(a)
A(string n = NULL, int a= 0):name(n),age(a)
name = 张飞; age  = 22
name = 李逵; age  = 19
*/