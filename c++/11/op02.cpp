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
    friend B operator!( B& b);

};

// 友元函数重载逻辑非操作符 !
B operator!( B& b) {
    return B(!(b.b_t), !(b.b_f));
}

int main() {
    B *b1 = new B(2, 3);
    A a = !(*b1);  // 使用 operator!() 返回的 A 对象

    cout << "After logical NOT operation:" << endl;
    cout << "a.b_t = " << a.getx() << ", a.b_f = " << a.gety() << endl;
    
    return 0;
}

