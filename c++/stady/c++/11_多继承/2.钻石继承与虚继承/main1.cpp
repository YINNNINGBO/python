#include <iostream>
using namespace std;
// 一个派生类的多个基类有同一个公共基类:这种继承叫做钻石继承
/* eg:
                                    class Base_A

    class Bfor_A : public Base_A                    class Cfor_A : public Base_A

                    class derivative : public Cfor_A, public Bfor_A

derivative的基类不是  Base_A  ；且Cfor_A Bfor_A同于同一个基类Base_A，所以当用derivative直接调用Base_A内的成员函数是有二义性的问题
//所以不能直接调用 Base_A 的成员函数

*/
class Base_A
{
    string name;

public:
    Base_A(const string &n = NULL) : name(n)
    {
        cout << "Base_A(const string &n)" << endl;
    }
    void printf(void)
    {
        cout << "name is:" << name << endl;
    }
};
class Bfor_A : public Base_A
{
private:
    int age;

public:
    Bfor_A(const int &a = 0, const string &n = NULL) : age(a), Base_A(n)
    {
        cout << "Bfor_A(const int &a = 0,const string &n = NULL) " << endl;
    }
    void printf(void)
    {
        cout << "that age is:" << age << endl;
    }
};
class Cfor_A : public Base_A
{
private:
    int height;

public:
    Cfor_A(const int &h = 0, const string &n = NULL) : height(h), Base_A(n)
    {
        cout << "Cfor_A(const int &a = 0,const string &n = NULL) " << endl;
    }
    void printf(void)
    {
        cout << "that age is:" << height << endl;
    }
};
// 派生类
class derivative : public Cfor_A, public Bfor_A
{
    string phone;

public:
    derivative(const string &p, const int &b, const int &c, const string &n) : phone(p), Bfor_A(b, n), Cfor_A(c, n)
    {
        cout << "derivative(const string &p, const int &b, const int &c, const string &n)" << endl;
    }
    void printf(void)
    {
        cout << "that phone is:" << phone << endl;
    }
};
int main()
{
    derivative d1("1537001365", 25, 188, "小明");
    cout << endl;

    d1.Bfor_A::printf(); // 使用作用域限定符
    d1.Cfor_A::printf();
    // d1.Cfor_A::Base_A::printf();

    // d1.Base_A::printf();  error: ‘Base_A’ is an ambiguous base of ‘derivative’    Base_A 不是 derivative的基类

    return 0;
}
/**
Base_A(const string &n)
Cfor_A(const int &a = 0,const string &n = NULL)
Base_A(const string &n)
Bfor_A(const int &a = 0,const string &n = NULL)
derivative(const string &p, const int &b, const int &c, const string &n)

that age is:25
that age is:188
*/