1. 常量成员变量 (const成员)
const成员变量必须在对象创建时初始化，因为它们在对象的生命周期内是不可修改的，只能通过初始化列表赋值。
class Example {
    const int value;
public:
    Example(int v) : value(v) {} // 必须用初始化列表
};

2. 引用成员变量 (&成员)
引用成员变量必须在定义时绑定到某个对象，且绑定后无法更改，因此需要在初始化列表中初始化。
class Example {
    int& ref;
public:
    Example(int& r) : ref(r) {} // 必须用初始化列表
};

3. 没有默认构造函数的类成员
如果类成员是某种自定义类型，并且没有提供默认构造函数，必须通过初始化列表为它提供初始化参数。
class Member {
public:
    Member(int x) {}
};
class Example {
    Member m;
public:
    Example() : m(10) {} // 必须用初始化列表
};

4. 基类构造
派生类的构造函数必须通过初始化列表显式调用基类的构造函数，尤其是基类没有默认构造函数时。
class Base {
public:
    Base(int x) {}
};
class Derived : public Base {
public:
    Derived(int x) : Base(x) {} // 必须用初始化列表
};

5. 成员变量初始化优先级
某些情况下，为了避免默认构造后再赋值（造成额外的性能开销），应使用初始化列表直接初始化。
class Example {
    int value;
public:
    Example(int v) : value(v) {} // 避免value先被默认初始化后再赋值
};

6. 类成员是std::array或其他不支持默认构造的容器
某些标准容器如std::array，必须在初始化列表中初始化大小和内容。  
#include <array>

class Example {
    std::array<int, 3> arr;
public:
    Example() : arr{1, 2, 3} {} // 必须用初始化列表
};