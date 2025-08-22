#pragma once
#include <iostream>

// 在头文件中的实现，声明为inline避免重定义，或者将实现转移至源文件
inline void testfunc1()
{
    std::cout << "test" << std::endl;
}

inline int g = 0;