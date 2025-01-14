#include <iostream>
using namespace std;
/*   有元：为在外界访问类内私有成员                    */
// 有元函数
// 有元类  有元类不是双向的

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
    static void my_printf(void) // 这个静态成员变量参数没有  this
    {
        data++;
        cout << "Now: static void my_printf(void) data=  " << data << endl;
    }
    void test(void)
    {
        cout << "定义在类里" << endl;
    }

    // 有元函数  friend  声明时使用即可
    friend void fri_fun(const A &a, const A &b);
    // void fri_fun2(const A &a, const A &b);   没有使用friend 关键字是不行的 与fri_fun对比
    // 指出错误：a.a1 ， b.a1 时私有的
    friend class B;
    friend void B::add_fun(const A &a); // 限定 B内的成员函数时A类的有元
    void test2(void);
};
class B
{
private:
    int z;

public:
    B(int i = 0) : z(i)
    {
        cout << "B 构造" << endl;
    }
    // 下面这个函数不能用 friend 修饰
    void add_fun(const A &a)
    {
        z += a.a1;
        cout << "Now z = " << z << endl;
    }
};

void test2(void)
{
    cout << "声明在类里,定义在类外" << endl;
}

void fri_fun(const A &a, const A &b)
{
    cout << "有元函数 可以直接访问类内成员 两个类中的成员a1 相加 = " << a.a1 + b.a1 << endl;
}
// 有元函数的错误使用
//  void fri_fun2(const A &a, const A &b)
//  {
//      cout << "有元函数 可以直接访问类内成员 两个类中的成员a1 相加 = " << a.a1 + b.a1 << endl;
//  }
int A::data = 100;
int main()
{
    A a2(10);
    A b2(20);
    // a2.fun(); // 普通成员函数可以使用静态成员变量
    a2.A::fun();
    a2.fun(); // 与上一行相同效果

    A::my_printf();
    a2.my_printf(); // 静态成员函数可以使用静态成员变量
    // test1();      定义在类里  ，作用域是类内成员，不可以直接使用
    test2(); // 定义在类外  ，作用域是全局，可以直接使用
    fri_fun(a2, b2);
    // 友元类  测试
    B bb(9);
    bb.add_fun(a2);
    return 0;
}
