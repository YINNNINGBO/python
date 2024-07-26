#include <iostream>
#include <iomanip>  
//iomanip 是可以用来设置小数 精度的
using namespace std;
double add(double x, double y)
{
	return (x+y);
}
double sub(double x, double y)
{
	return (x-y);
}
double mul(double x, double y)
{
	return (x*y);
}
double dirsion(double x, double y)
{
	if(y == 0)
	{
		cout<<"分子 ==0 "<<endl;
		exit(000.00);
	}else{
		return (x/y);
	}
}
void printf_fun(double (*pri_fun)(double,double),double x, double y)
{ // 函数指针可以作为参数
	cout<<x<<':'<<y<<"="<< pri_fun(x,y)<<endl;
}
int main(void)
{	cout<<fixed;
	cout<< setprecision(2);
// 上两句 是设置小数点后精确程度 可以做到四舍五入
	double (*pri_ccc)(double ,double);
	// 定义函数指针  指向一个函数的指针  可以先不赋值
	double  num1,num2;
	char ch;
	cout<<"输入num1 , num2的数值"<<endl;
	cin>>num1>>num2;
	cout<<"现在选择你想要的算法"<<endl;
	cout<<"输入:+ - * /:";
	cin>>ch;
	switch(ch)
	{
	case'+':
	//	cout<<add(num1,num2)<<endl;
		pri_ccc = add;
		//将选用函数赋给  函数指针
		break;
	case'-':
		pri_ccc = sub;
		break;
	case'*':
		pri_ccc = mul;
		break;
	case '/':
		pri_ccc = dirsion;
		break;
	}
	printf_fun(pri_ccc,num1,num2);
	//调用含有函数指针的 函数
	cout<<"计算结束"<<endl;

	return 0;
}



