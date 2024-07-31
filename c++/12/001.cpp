#include <iostream>

class MyArray {
private:
    int* data;
    size_t size;

public:
    // 构造函数
    MyArray(size_t sz) : size(sz) {
        data = new int[size];
    }

    // 析构函数
    ~MyArray() {
        delete[] data;
    }

    // 重载 [] 运算符，增加越界检查
    int& operator[](size_t index) {
        if (index >= size) {
			std::cout<< "Index out of range";
        }
        return data[index];
    }

    // const 版本的重载 [] 运算符，增加越界检查
    const int& operator[](size_t index) const {
        if (index >= size) {
			std::cout <<"Index out of range";
        }
        return data[index];
    }

    // 获取数组大小
    size_t getSize() const {
        return size;
    }
};

int main() {
    MyArray arr(5);

    try {
        // 访问有效索引
        std::cout << "Element at index 2: " << arr[2] << std::endl;

        // 访问越界索引
        std::cout << "Element at index 10: " << arr[10] << std::endl;
    } catch (const char* msg) {
        std::cout << "Exception: " << msg << std::endl;
    }

    return 0;
}

