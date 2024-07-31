#include <iostream>
using namespace std;
class A {
	int b_t;
	int b_f;
	public:
	A(int x,int y):b_t(x),b_f(y){
	}
	int change_x(int x){
		b_t = x;
		return b_t;
	}
	int change_y(int y){
		b_f = y;
		return b_f;
	}
	int getx(void)const{
	return b_t;
	}
	int gety(void)const{
		return b_f;
	}
};
class B :public A{
	public:
		B(int x,int y):A(x,y){
		}
	B & operator=(const B &c){
		change_x(c.getx());
		change_y(c.gety());
		return *this;
	} 
	friend const B& operator!( B& l){
		if(l.getx()){
			l.change_x(0);
		}else{
			l.change_x(1);
		}
		if(l.gety()){
			l.change_y(0);
		}else{
			l.change_y(1);
		}
		return l;
	}  
	void show(void){
		cout << "b_t = :" << getx() <<"b_y = :" << gety() << endl;
	}
};
int main(void){
	B * b1 = new B(2,3);
	B   *b2;
   //!b1;
	cout<<b1->show()<<endl;
	return 0;
}
