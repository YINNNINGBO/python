#include <iostream>
using namespace std;

// 结构体中 不写private  public   等关键字 ，默认是public （共有的）
//  复数
struct Complex
{
    // 私有
private:
    double r; // 实部
    double i; // 虚部

    // 函数公有
public:
    void init(double rr, double ii)
    {
        r = rr;
        i = ii;
    }
    double real()
    {
        return r;
    }
    double image()
    {
        return i;
    }
    void set_r(double rr)
    {
        r = rr;
    }
};
int main()
{
    Complex a; // 定义一个复数结构
    a.init(2, 3);
    cout << a.real() << " + " << a.image() << "i" << endl;
    // a.r = 8; // 私有的不能被调用 error: ‘double Complex::r’ is private within this context

    a.set_r(4); // 这样实现  用公有函数 改变私有数据
    cout << a.real() << " + " << a.image() << "i" << endl;
    return 0;
}