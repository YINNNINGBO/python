#include <iostream>
using namespace std;
int main(void)
{
	auto ch = 'i';
	cout << typeid(ch).name() << endl;
	return 0;
}
