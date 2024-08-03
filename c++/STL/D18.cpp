#include <iostream>
#include <vector>
#include <limits>
using namespace std;
int main() {
    std::vector<int> numbers;
    int input;

    // 读取一组整数到vector
    std::cout << "请输入一组整数，以非数字字符结束输入:" << std::endl;
    while (std::cin >> input) {
        numbers.push_back(input);
    }

    // 清除输入流的错误状态和余留的输入
    std::cin.clear();  // 清除错误状态
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 忽略余留的输入

    // 计算并输出每对相邻元素的和
    std::cout << "每对相邻元素的和:" << std::endl;
    for (size_t i = 0; i < numbers.size() - 1; ++i) {
        std::cout << numbers[i] + numbers[i + 1] << std::endl;
    }

    // 如果元素个数为奇数，提示用户最后一个元素没有求和
    if (numbers.size() % 2 != 0) {
        std::cout << "最后一个元素没有参与求和: " << numbers.back() << std::endl;
    }

    // 计算并输出头尾元素两两配对的和
    std::cout << "头尾元素两两配对的和:" << std::endl;
    size_t n = numbers.size();
    for (size_t i = 0; i < n / 2; ++i) {
        std::cout << numbers[i] + numbers[n - i - 1] << std::endl;
    }

    return 0;
}

