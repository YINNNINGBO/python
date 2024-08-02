#include <iostream>
using namespace std;
//若 普通函数与 模板的可以调用  编译器优先使用 普通函数
//通过一个 空模板的参数列表  强制调用函数模板
// 函数模板可以重载
// 若模板可以更好匹配，优先使用模板
// 函数模板 与普通函数 实现功能相同时 不要同时  两个都定义（显然 模板更好用）
void maPrint(int a, int b){
cout <<"调用普通函数" << endl;
}
template <class T>
void myPrint( T a,T b){
cout <<"调用模板函数0" << endl;
}
template <class T>
void myPrint( T a,T b,T c){// 遇上个函数模板  构成重载
cout <<"调用模板函数1" << endl;
}
void text1(){
	int a = 10;
	int b = 20;
	char c = 'A';
	char d =  'B';
	maPrint(a,b); // 这条代码调用  普通函数
    myPrint< >(a, b); //这样会强制调用  函数模板
	myPrint(a,b,100);
	myPrint(c,d);// 普通函数与函数模板都可以调用
				  // ，但是普通函数需要隐式转换，模板只需要将T 看作  制定类型
				  // 所以编译器会优先使用模板
}
int main(void )
{
	text1();
	return 0;

}
