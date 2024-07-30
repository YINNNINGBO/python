#include <iostream>
using namespace std;
class base{
	public:
		// virtual 关键字   是同名函数具有多态的特性
		//  只有基类中的 virtual 有效 
		//  且用virtual 修饰的函数 常数性、 返回值、参数必须一致
		virtual void func(void);
};
class derived: public base{
	public:
		//这里+ virtual 没有用
		void func(void);
};
void base::func(void){
	cout<< "base:func"<<endl;
}
void derived::func(void ){
	//base::func();
	cout <<"derived:func"<<endl;
}
int main(void)
{	derived* s1 = new derived;
	base* cur[128] = {0 };
	cur[0] = new base;
	// cur[1] = new dericed; 同下
	//
	cur[1] = s1;
	cur[0]->func();
	cur[1]->func();
	s1->base::func();
	s1->func();
	return 0;

}
