#include <iostream>
using namespace std;
namespace
{
    int a = 100;
}
int main()
{
    cout << ::a << endl;
}