#include <iostream>
#include <cstdlib>
#include <cstring>
/** ***********************  引用 &   *****************
 * 用指针的地方  可以用引用 ，一定程度上减少指针的使用
 * 传值：使用实参的型参需要 2倍的地址空间  ；传址：相当于只用实参的地址，地址空间开销少一半，引用相当于传址
 * 引用的本质：  指针常量
 *  相当于：
 *          int m =100;
 *          int * const x = &m;   //指向地址不能改
 *          由此可以理解： int &x =100; 为何是错的
 *           因为：int * const x = 100; //这样地址指向的数据不能改
 *           所以：const int * const x = 100 // 是对的   指向地址与地址上数据都不能改
 *
 *  区别于：
 *          const  int *x  =&m;   //指向地址上存储的址不能改
 *
 */

/**错误使用
 * float f;
 * float &r2;  //应该在定义时就初始化
 *  r2 =f;
 */
void swap(int &x, int &y)
{                // 使用&  相比使用指针   更便于阅读
    int tmp = x; // tmp  = *x
    x = y;       // *x =  *y
    y = tmp;     // *y  =  tmp
}
using namespace std;
int main()
{
    int i = 100;
    int &ir = i; // 给变量 i  起了一个别名  同一个地址  在做型参时可使用
    cout << "i  = " << i << "; i的地址:" << &i << endl
         << "ir  = " << ir << "; ir的地址:" << &ir << endl;

    int b = 120;
    cout << "i  =" << i << "; b = " << b << endl;
    swap(i, b);
    cout << "after for swap: i  =" << i << "; b = " << b << endl;
    // int &r2 = 100; //错误
    const int &r3 = 100; // 正确
    return 0;
}