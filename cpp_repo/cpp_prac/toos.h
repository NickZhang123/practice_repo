# pragma
#include <iostream>

// 基础模板函数，用于处理单一类型的参数
template <typename T>
void print(const T& value) {
    std::cout << value << std::endl;
}

// 递归模板函数，用于处理多个参数
template <typename T, typename... Args>
void print(const T& first, const Args&... rest) {
    std::cout << first << " ";
    print(rest...); // 递归调用，处理剩余的参数
}
