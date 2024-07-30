#include <iostream>
#include <typeinfo>
using namespace std;
class A{
	public:
		int b;
		void func(void){
		}
};
class B:public A{
};
class c{
};
int main(void )
{
	int d;
	A *pa ,paa;
	B *pb ,pbb;
	cout << "typeid(d).name().."<<typeid(d).name()<<endl;
	cout << "tyeid(int).name().." << typeid(int).name( ) << endl;
	
	cout << "......dynamic_cast........" << endl; 
	/**    down is  error 
	pb = dynamic_cast< B* >(&paa);
	cout<< "down";
	if(pb){
		cout<< "ok" << endl;
	}else{
		cout << "error" << endl; 
	}*/
	cout<< "up...........:";

	pa = dynamic_cast< A* >(&pbb); 
	if(pa){
		cout<< "ok" << endl;
	}else{
		cout << "error" << endl;
	}
	return 0;
}
