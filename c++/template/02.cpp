#include <iostream>
using  namespace std;
int  add(int a ,int b)
{
return (a+b);
}
template <class T>
T add1(T &a,T &b)
{
   return (a+b);
}
template <class T >
T  add2(T &a, char &b){
	return (a+b);
}
template <class T1, class T2>
T1 add3(T1 &a ,T2 &b)
{
	return (a+b);
}
void pri_add()
{
	int a =10;
	int b = 19;
	char ar = 'a';
	cout<< "add(a,b)"<<add(a,b) << endl;
	cout<< "add(a,ar)"<<add(a,ar) << endl;
	cout << "add1(a,b)" << add1(a,b) << endl;
//	cout << "add1(a,c)" << add1(a,c) << endl;  // a,c 不会自动隐式转换
//**********************
//使用 函数名<类型名>(参数名)   被称为： 显示指定类型  不会发生隐式转换
//	类型名必须是原有的（c++原有的）类型 ，不能是 T 
//	使用 函数名(参数名)           被称为： 自动类型推导  会发生隐式转换

	cout << "add1<int>(a,b)" << add1<int>(a,b) << endl; // 这里  加不加<int > 都一样
 	cout << "add2<int>(a,ar)" <<add2<int>(a,ar) << endl; // 
	cout << "add3(a,b)" << add3(a,b) << endl;
	cout << "add3<int ,char>(a,ar)= add3(a,ar)" << add3<int ,char >(a,ar) << endl;

}
int main (void)
{
	pri_add();
}

