#include <iostream>
// 构造时顺序 1：基类，2成员类，3派生类
//  析构顺序  与构造顺序正好相反
using namespace std;
class Base
{
private:
    int x, y;

public:
    Base(int x1 = 0, int y1 = 0) : x(x1), y(y1)
    {
        cout << "in Base 析构" << endl;
    }
    ~Base()
    {
        cout << "leave Base" << endl;
    }
};

class dev
{
    int z;

public:
    dev(int z1 = 0) : z(z1)
    {
        cout << "in dev " << endl;
    }
    ~dev()
    {
        cout << "leave dev" << endl;
    }
};
// 派生类
class derivative : public Base
{
private:
    int m, n;
    dev de1;

public:
    derivative(int m1, int n1, int x1 = 0, int y1 = 0) : Base(x1, y1), de1(), m(m1), n(n1)
    {
        cout << "in derivative 析构" << endl;
    }
    ~derivative()
    {
        cout << "leave derivative" << endl;
    }
};
int main()
{
    Base b1(1, 2);
    cout << endl;

    derivative d1(3, 4, 5, 6);
    cout << endl;
    return 0;
}

/**
in Base 析构

in Base 析构
in dev
in derivative 析构

leave derivative
leave dev
leave Base
leave Base
*/