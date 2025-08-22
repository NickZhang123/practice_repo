#include <iomanip>
#include <iostream>
#include "cpp14_test.h"

using namespace std;
#if 0

template<typename T, T... I>
void print_sequence(std::integer_sequence<T, I...>) 
{
    ((std::cout << I << ' '), ...);  // 可变参数输出
    std::cout << std::endl;

    // (cout << ... << I) << endl;
    // ((cout << I << " "),...)
}

void cpp14_test()
{
    auto v = integer_sequence<int, 1, 2>{};
    print_sequence(v);

    print_sequence(index_sequence<3, 4, 5>{});

    print_sequence(make_index_sequence<5>{});

}

#endif