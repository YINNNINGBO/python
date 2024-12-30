#include <iostream>
/**
 * 不同名字空间中的成员名字不能相同
 * 使用名字空间中成员的方法有三种    且三种同时使用  不会排斥
 * 1.      ns1::take_add(1, 4);
 * 2.      先声明名字空间中的要使用的成员 using ns1::take_add;      再  take_add(2, 4);
 * 3.      再定义的名字空间后 声明整个名字空间using namespace ns1;  再  take_add(2, 4);
 *     **** 在使用后两种方法时，要切记避免多个名字空间中有相同名的成员****
 */
using namespace std;

//  定义一个字节的名字空间
namespace ns1
{
    void take_add(int a, int b)
    {
        cout << "and=: " << a + b << endl;
    }
}
using namespace ns1; // 声明名字空间
int main()
{

    // using ns1::take_add; // 单独引用名字空间中的一个要使用的成员
    cout << "main" << endl;
    ns1::take_add(1, 4);
    take_add(2, 4); // 不声明 名字空间时使用
    return 0;
}
