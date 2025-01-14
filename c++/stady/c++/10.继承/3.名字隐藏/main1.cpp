// 名字隐藏就是  派生类(子类) 与 基类(父类) 的函数名相同
//   两个类中函数构成l  哈桑农户隐藏的关系
// 因为不在一个作用域，这里不会构成构成函数重载
#include <iostream>
using namespace std;
// 基类
class base
{
    // 私有
private:
    int x;
    // 公有
public:
    // void set(int i) : this->x(i) {}  //非构造函数不能使用初始化列表
    void set(int i = 0)
    {
        x = i;
    }
    void printf()
    {
        cout << "in base : x=" << x << endl;
    }

    // 保护
protected:
};
// 派生类
class deriverd : public base
{
private:
    int m, n;

public:
    void set(int m1, int n1) // 与基类函数同名
    {
        m = m1;
        n = n1;
    }
    void printf()
    {
        cout << "in deriverd : m=" << m << " n=" << n << endl;
    }
};
int main()
{
    base a1;
    a1.set(10);
    a1.printf();
    cout << endl;

    deriverd b1;
    // 这里因为作用域 不会构成构成函数重载
    // 添加作用域 可以强行使用 基类中的同名函数
    b1.base::set(10);
    b1.printf();       // 这里打印使用派生类中的printf 会乱码
    b1.base::printf(); // 同理增加作用与修饰符  调用基类中的 printf
    cout << endl;

    b1.set(2, 3);
    b1.printf(); // 这里打印使用派生类中的printf 不会乱码
    return 0;
}
/**
in base : x=10

in deriverd : m=1143114048 n=32636
in base : x=10

in deriverd : m=2 n=3
*/