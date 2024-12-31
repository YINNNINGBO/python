#include <iostream>
#include <cstdlib>
/**
 * 类型转换 分： 1；隐式转换（编译器自动转换，应避免）   2：显示转换 （手动转换，建议使用）
 * 隐式转换：  字节小的向字节大的转化  int->float
 * c++ 类型转换 增加方法    float(a)
 * 另外增加4中更严格的类型转换
 *  1.静态类型转换   static_cast<目标类型>（源类型）   用于风险最低，不能用于不同类型指针的转换，基本类型与指针的转换
 *  2.重解释类型转换 reinterpret_cast<>()             高风险    可以用于不同类型指针的转换，基本类型与指针的转换
 *  3.常类型类型转换 const_cast<>()                  取出指针的常属性
 *  4.动态类型转换   dynamic_cast<>()                 用于多态中类型指针的向下转型，可以检测是否转型成功 在编译阶段可以判断
 */
using namespace std;
int main()
{
    int a = 100;
    double a1 = (double)a; // c风格
    double a2 = double(a); // c++ 风格
    double b1 = static_cast<double>(a);
    void *p1 = malloc(100);
    int *p2 = static_cast<int *>(p1);
    char *pc = static_cast<char *>(p1);
    // int num = p1;      //不行
    // int num = static_cast<int>(p1)     //风险较高 也不行
    // pi =  static_cast<int * >(pc);     //c++ 严谨不行，
    // 但是在c中  不报错
    // eg: int num =  (int)p1;
    int n = 0x00414243; // 主机字节序 （小端字节序）  高地址存地位数据
    int num = 123;      // 0x00 00 00 7b
    int num2 = 0x7b;
    char *ps = reinterpret_cast<char *>(&n); // c++  可以
    cout << ps << endl
         << "num = " << hex << num << "  num2 = " << dec << num2 << endl; // hex:16进制  dec:10进制
    int tmp = 123;
    const int *p_tmp = &tmp; // 不能通过(*p_tmp)++ 修改指针指向的值
    // c++ error ：   (*p_tmp)++;     int * c_p = p_tmp;
    int *c_p = const_cast<int *>(p_tmp); // 修改掉常量的常属性
    (*c_p)++;
    cout << "(*c_p)++ = " << *c_p << endl;

    return 0;
}