#include <iostream>
using namespace std;
class A{
	public:
		int a;
		A(void){
			cout<<"A"<<endl;
		}
		~A(void){
		// 写成 virtual ~A main中  语句1 效果与2后的delete 效果相同 
		cout<<"~A"<<endl;
		}
};
class B:public A{
	public:
		int b;
		B(void){
			cout<<"B"<<endl;
		}
		~B(void){
			cout<<"~B"<<endl;
		}
};
int main(void )
{
	A a2;
	B b2;
	A * a1  = new B;//........1
	cout<<"______"<<endl;
	B * b1  = new B;//.........2
	cout<<"sizeof(A)"<<sizeof(A)<<"||sizeof(a1)"<<sizeof(a1)<<endl;
	cout<<"sizeof(B)"<<sizeof(B)<<"||sizeod(b1)"<<sizeof(b1)<<endl;
   // a1 b1 申请的空间大小是 B 类的大小 故 （）sizeof(a1)?sizeof(b1)相等
	cout<<"sizeof(A)"<<sizeof(A)<<"||sizeof(a2)"<<sizeof(a2)<<endl;
	cout<<"sizeof(B)"<<sizeof(B)<<"||sizeof(b2)"<<sizeof(b2)<<endl;
	delete a1;//这里  只调用~A
	delete b1;// 调用 先~B  后~A


	return 0;
}
