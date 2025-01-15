#include <iostream>
using namespace std;
// 单一继承：   派生类的基类只有一个
// 多重继承   ：派生类的基类不止一个时称为
// 基类
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
class Base_B
{
private:
    int age;

public:
    Base_B(const int &a = 0) : age(a)
    {
        cout << "Base_B(const int &a = 0)" << endl;
    }
    void printf(void)
    {
        cout << "that age is:" << age << endl;
    }
};
// 派生类
class derivative : public Base_A, public Base_B
{
    string phone;

public:
    derivative(const string &p, const int &a, const string &n) : phone(p), Base_B(a), Base_A(n)
    {
        cout << "derivative(const string &p,const int &a, const string &n)" << endl;
    }
    void printf(void)
    {
        cout << "that phone is:" << phone << endl;
    }
};
int main()
{
    derivative d1("1537001365", 25, "小明");
    cout << endl;
    d1.Base_A::printf(); // 使用作用域限定符
    d1.Base_B::printf();
    d1.printf();

    return 0;
}
/**
./main1
Base_A(const string &n)
Base_B(const int &a = 0)
derivative(const string &p,const int &a, const string &n)

name is:小明
that age is:25
that phone is:1537001365
*/