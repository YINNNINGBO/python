#include <iostream>
using namespace std;
// 首先一个类内的所有成员再内部都剋以直接调用
// 但是  私有成员，保护成员外部不能调用
//****私有与保护区别：
/*
特性	         private	    protected
类内访问	     ✅ 允许	        ✅ 允许
派生类访问	     ❌ 不允许       ✅ 允许
外部代码访问     ❌ 不允许      ❌ 不允许
继承后权限	     无法访问	    根据继承方式变化（通常仍是protected）
*/
//  公有成员可以外部直接调用
class A
{
    // 私有
private:
    int a;
    // 守护
protected:
    int b;
    // 公有
public:
    int c;
    A(int a1 = 0, int b1 = 0, int c1 = 0) : a(a1), b(b1), c(c1)
    {
        cout << "构造" << endl;
    }
    void show()
    {
        cout << "A::a=" << a << " b=" << b << " c= " << c << endl;
    }
};
class B : private A
{
public:
    B(int a1 = 0, int b1 = 0, int c1 = 0) : A(a1, b1, c1) {}
    void printf(void)
    {
        cout << "b=" << A::b << " c=" << c << endl;
    }
    ////a 是基类 A 的私有成员，不能被子类 B 直接访问。
    // void set_a()
    // {

    //     A::a = 10;
    // }
};
class C : public A
{
    int C_c;

public:
    C(int a1 = 0, int b1 = 0, int c1 = 0) : A(a1, b1, c1)
    {
        cout << "C 构造" << endl;
        C_c = a1 + b1;
    }
    void printf(void)
    {

        cout << "in C: b=" << A::b << ": c=" << c << " C_c:= " << C_c << endl;
    }
    ////a 是基类 A 的私有成员，不能被子类 B 直接访问。无论基类与派生类之间是什么关系
    // void set_a()
    // {

    //     A::a = 10;
    // }
};
class D : protected A
{
public:
    D(int a1 = 0, int b1 = 0, int c1 = 0) : A(a1, b1, c1) {}
    void printf(void)
    {

        cout << "b:" << A::b << " c: " << c << endl;
    }
    ////a 是基类 A 的私有成员，不能被子类 B 直接访问。无论基类与派生类之间是什么关系
    // void set_a()
    // {

    //     A::a = 10;
    // }
};
int main()
{
    // 私有继承
    B bb(1, 2, 3); // 需要能向A传入参数的构造函数
    bb.printf();

    // B的基类是A 且与A的关系是私有，故A内的所有函数对于B都是私有不能再外部调用
    // bb.show();  error
    // bb.c = 10;
    // 公有继承
    C cc(2, 4, 5);
    cc.show();
    cc.printf();
    cc.c = 10;
    // cc.b = 10;  //基类保护成员  不能外部调用

    // 保护继承
    D dd(6, 7, 8);
    dd.printf();
    // dd.c = 10;   //关系是保护，基类中任何成员都不能外部调用。
    // dd.b = 10;
    // dd.show();
}
/**
构造
b=2 c=3
构造
C 构造
A::a=2 b=4 c= 5
in C: b=4: c=5 C_c:= 6
构造
b:7 c: 8
*/