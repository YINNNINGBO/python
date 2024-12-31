#include <iostream>
#include <cstring>
using namespace std;
// c++ 结 可以在结构体内定义函数
struct stu
{
    int age;
    char name[20];
    // 直接在结构体内定义
    int fun_add(int x, int y)
    {
        return (x + y);
    }
};
// 支持匿名联合

int main(int argc, const char **argv)
{
    union
    { // 支持匿名联合  联合体内不能定义成员函数
        int num;
    };
    stu my_stu;
    strcpy(my_stu.name, "Hello\n");
    cout << my_stu.name << my_stu.fun_add(2, 3) << endl;
    return 0;
}
