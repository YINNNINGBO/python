#include <iostream>
using namespace std;
/*               类中不使用关键字（public..）标注变量，函数的化，成员默认是私有的    */

/*                       类                         */
class Complex
{
    // 默认私有
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
    // a.r = 4; // 这里默认是私有的 ‘double Complex::r’ is private within this context
    return 0;
}
/**
 *
g++ main.cpp -c  -o main.o
g++ main.o -o main
./main
2 + 3ilinux
 */