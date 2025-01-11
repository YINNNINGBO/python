#include <iostream>
using namespace std;
// 1.当成员名与成员函数型参名相同时
// 2.成员函数返回值是 当前类
// 3.当前类的销毁
class A
{
private:
    int count;

public:
    A(const int count = 0)
    {
        this->count = count;
        cout << " A(const int count =0 )" << endl;
    }
    void my_printf(void)
    {
        cout << "count  = " << count << endl;
    }
    // 对count ++  同时返回当前类
    A &add(void)
    {
        count++;
        return *this; // 区别于指针  这里用 <* this>
    }
    // 当前类的销毁
    void destroy(void)
    {
        cout << " destroy(void)" << endl;
        delete this; // delete 的参数是 指针类型
    }
};
int main(void)
{
    A a1(19);       // A(const int count =0 )
    a1.my_printf(); // count  = 19

    A a2 = a1.add().add(); // count = 21
    a2.my_printf();

    A *a3 = new A(22);
    a3->my_printf();
    a3->destroy(); // 同理于： delete (a3);

    return 0;
}
