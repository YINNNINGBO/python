#include <iostream>
using namespace std;
// 静态成员函数 只能访问静态成员变量 不能访问非静态成员变量
//  静态成员 是同一种类唯一的  共用一个；不像非静态成员，每个类都有都有一份
class A
{
    int a1;
    static int data;

public:
    A(int a = 0) : a1(a)
    {
        cout << " A(int a = 0):a1(a) a1 = " << a << endl;
    }

    void fun(void)
    {
        cout << "普通成员函数可以使用静态成员变量 a1+data = " << a1 + data << endl;
    }
    //  静态成员函数不能调用普通变量
    // static void user_a1(void){
    //     cout << "静态成员函数尝试调用普通变量 a1 " << a1 << endl;
    // }
    static void my_printf(void) // 这个静态成员变量参数没有  this
    {
        data++;
        cout << "Now: static void my_printf(void) data=  " << data << endl;
    }
};
int A::data = 100;
int main()
{
    A a2(10);
    // a2.fun(); // 普通成员函数可以使用静态成员变量
    a2.A::fun();
    a2.fun(); // 与上一行相同效果

    A::my_printf();
    a2.my_printf(); // 静态成员函数可以使用静态成员变量
    return 0;
}
/**
  ./main1
 A(int a = 0):a1(a) a1 = 10
普通成员函数可以使用静态成员变量 a1+data = 110
普通成员函数可以使用静态成员变量 a1+data = 110
Now: static void my_printf(void) data=  101
Now: static void my_printf(void) data=  102
 */