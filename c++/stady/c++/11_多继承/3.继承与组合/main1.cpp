#include <iostream>
using namespace std;
// 继承 与  组合 用于解决代码重用的两种方案

class vehicles
{
    string goods;

public:
    vehicles(const string &dest) : goods(dest)
    {
        cout << " vehicles(const string &dest) " << endl;
    }
    void user(void)
    {
        cout << "货物信息：" << goods << endl;
    }
};
class tyre
{ // 轮胎
public:
    void run(const string dest) const
    {
        cout << "运送方向" << dest << endl;
    }
};
class car : public vehicles // 交通工具   //************** 继承
{
public:
    tyre wheel; //**********************组合
    car(const string &dest) : vehicles(dest)
    {
        cout << "car(const string & dest)" << endl;
    }
};
int main()
{
    car c1("电脑");
    c1.wheel.run("北京");
    c1.user();
    return 0;
}
/**
vehicles(const string &dest)
car(const string & dest)
运送方向北京
货物信息：电脑
*/