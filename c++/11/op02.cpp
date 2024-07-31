#include <iostream>
using namespace std;

class A {
protected:
    int b_t;
    int b_f;
public:
    A(int x, int y) : b_t(x), b_f(y) {}

    int change_x(int x) {
        b_t = x;
        return b_t;
    }

    int change_y(int y) {
        b_f = y;
        return b_f;
    }

    int getx() const {
        return b_t;
    }

    int gety() const {
        return b_f;
    }

   };

class B : public A {
public:
    B(int x, int y) : A(x, y) {}

    void show() const {
        cout << "b_t = " << b_t << ", b_y = " << b_f << endl;
    }
	 // 声明友元函数，用于访问 B 类的私有成员
	 //这个函数返回值不是引用  返回赋值体 ， 原b 不改变
	 //******'!' 是不改变原数值的**
	friend B operator!( B& b)
		// 友元函数重载逻辑非操作符 !
		 {
			return B(!(b.b_t), !(b.b_f));
		}
		/*   这个是返回值是 &  原b 发生改变
	friend B& operator!(B& b) {
        b.b_t = !(b.b_t);
        b.b_f = !(b.b_f);
        return b;
    }
*/

};

int main() {
    B *b1 = new B(2, 3);
	cout << "b1.b_t = " << b1->getx() << ", b1.b_f = " << b1->gety() << endl;

    A a = !(*b1);  // 使用 operator!() 返回的 A 对象

    cout << "After logical NOT operation:" << endl;
    cout << "b1.b_t = " << b1->getx() << ", b1.b_f = " << b1->gety() << endl;

	cout << "a.b_t = " << a.getx() << ", a.b_f = " << a.gety() << endl;
    
    return 0;
}

