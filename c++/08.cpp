#include <iostream>
using namespace std;
class A{
	public:
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
		B(void){
			cout<<"B"<<endl;
		}
		~B(void){
			cout<<"~B"<<endl;
		}

};
int main(void )
{
	A * a1  = new B;//........1
	delete a1;//这里  只调用~A
	cout<<"______"<<endl;
	B * b1  = new B;//.........2
	delete b1;// 调用 先~B  后~A


	return 0;
}
