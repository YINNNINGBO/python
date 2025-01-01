#include <iostream>
using namespace std;
// 型参使用引用修饰
void swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

// 参数用 const 修饰  如果修改可以提示，报错; 同时允许可以传入右值(1，a,2.2)

int add(const int &a, const int &b)
{
    return (a + b);
}
int main()
{
    int a = 5, b = 7;
    cout << "a = " << a << "; b = " << b << endl;
    swap(a, b);
    cout << "after in swap " << "a = " << a << "; b = " << b << endl;
    cout << "add(a,b) = " << add(a, b) << endl;
    cout << "add(4,5) = " << add(4, 5) << endl;

    return 0;
}