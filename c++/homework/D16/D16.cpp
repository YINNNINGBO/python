#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main() {
    // 打开 /etc/passwd 文件
    ifstream file("/etc/passwd");

    // 检查文件是否成功打开
    if (!file.is_open()) {
        cerr << "无法打开文件 /etc/passwd" << endl;
        return 1;
    }

    // 读取文件的每一行
    string line;
    while (getline(file, line)) {
        // 输出每一行到屏幕
        cout << line << endl;
    }

    // 关闭文件
    file.close();

    return 0;
}

