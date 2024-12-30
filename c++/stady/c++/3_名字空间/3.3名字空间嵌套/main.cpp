#include <iostream>
using namespace std;
namespace ns1
{
    namespace ns2
    {
        int a = 100;
    }
}
using namespace ns1;
using namespace ns2; // 嵌套名字空间时  要声明  内部嵌套的名字空间

int main()
{
    cout << "a= " << ns1::ns2::a << endl; // 没有生命名字空间

    cout << "a= " << a << endl; // 声明全部名字空间

    return 0;
}