#include <iostream>
using namespace std;

// 函数声明与函数定义  只允许其中一个有参数默认值
int add(int x, int y, int z); // 正确声明
// int add(int x, int y, int z =100); //错误声明
int helloworld(int a, int b = 10); // 正确声明
int add(int x, int y, int z = 100)
{ // 设置参数的默认值
    return (x + y + z);
}
/**
 * 靠右原则：
 * 设有默认参数的右边的所有参数都必须有默认参数
 */
//         正确示例
int sub(int x, int y = 40, int z = 10)
{ // 设置参数的默认值
    return (x + y + z);
}
//         错误示例
// int min(int x = 0, int y)
// {
//     return ((x > y) ? x : y);
// }
int helloworld(int a, int b)
{
    return a;
}
// 只有参数类型没有参数名的参数 称为哑元
// 作用 保证函数向下的兼容性
int func(int x, int)
{
    cout << "哑元" << endl;
    return x;
}
int main()
{
    cout << "__fun__" << endl;
    cout << "add(1, 2, 3) = " << add(1, 2, 3) << endl;
    cout << "add(1, 2) = " << add(1, 2) << endl;
    cout << "sub(1) = " << sub(1) << endl;
    // cout << "min(1, 2) = " << min(1, 2) << endl;
    // cout << "sub(1, 2) = " << min(1) << endl;
    return 0;
}