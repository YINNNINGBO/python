#include <iostream>
using  namespace std;
int  add(int a ,int b){
return (a+b);
}
void pri_add()
{
	int a =10;
	int b = 19;
	char ar = 'a';
	cout<< add(a,b) << endl;
	cout<< add(a,ar) << endl;
}
int main (void)
{
	pri_add();
}

