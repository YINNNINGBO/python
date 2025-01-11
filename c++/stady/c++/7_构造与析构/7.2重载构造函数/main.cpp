#include <iostream>
using namespace std;
/**
 * 构造函数的重载问题：
 *
 */
class A
{
private:
    int a, b, c, d;

public:
    A(void)
    {
        cout << "无参构造函数" << endl;
        a = 0;
        b = 0;
        c = 0;
        d = 0;
    }
    A(int aa, int bb, int cc, int dd)
    {
        cout << "有参构造函数" << endl;
        a = aa;
        b = bb;
        c = cc;
        d = dd;
    }
    void my_printf(void)
    {
        cout << a << b << c << d << endl;
    }
};
int main()
{
    A a1;
    // a1.my_printf(); // 调用无参构造
    A a2(1, 2, 3, 4);
    // a2.my_printf(); // 调用有参构造
    return 0;
}
/**
g++ main.o -o main
./main
无参构造函数
有参构造函数
rm -r main.o main
*/