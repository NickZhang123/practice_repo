# include <iostream>
# include <initializer_list>
# include <cstring> 
# include "toos.h"
# include "class_test.h"
#include <concepts>

using namespace std;

MyClass::MyClass() : len(10)
{
    cout << "MyClass()" << endl;
    p_data = new int[len];
}

MyClass::~MyClass()
{
    cout << "~MyClass()" << endl;
    delete []p_data;
}

MyClass::MyClass(const MyClass &cls)
{
    cout << "MyClass(const MyClass &)" << endl;
    len = cls.len;
    p_data = new int[len];
    memcpy(p_data, cls.p_data, len);
}

MyClass& MyClass::operator=(const MyClass &cls)
{
    cout << "MyClass::operator=(const MyClass &cls)" << endl;
    // 1. 自我赋值检查
    if (this == &cls) {
        return *this;
    }

    // 2. 释放旧资源
    if (p_data != nullptr) {
        delete []p_data;
    }

    // 3. 进行深拷贝(c++11以后可以进行move)
    p_data = new int[len];
    memcpy(p_data, cls.p_data, len);

    // 4. 返回对象自身，提供链式赋值
    return *this;

}

void MyClass2::AccessCls(const MyClass &cls)
{
    cout << cls.len << endl; 
}

void friend_func(const MyClass &cls)
{
    cout << cls.len << endl;    // 友元函数访问类中私有变量
}

void test_cls()
{    
    MyClass cls;                    // 构造
    MyClass cls2 = cls;             // 拷贝构造
    MyClass cls3;                   // 构造
    cls3 = cls;                     // 赋值拷贝

    friend_func(cls);
    MyClass2().AccessCls(cls2);


    MyPair<int, int> p1(1, 2);
    print(p1.getFirst(), p1.getSecond(), p1.add(3, 4));
    MyPair<int, string> p2(222, "str");
    print(p2.getFirst(), p2.getSecond(), p2.add(3, 4));
}


class b {
public:
    b() { cout << "b" << endl; }
    b(int a) { cout << "b int" << endl; }
    ~b() { cout << "~b" << endl; }
};

class base {
public:
    base() {cout << "base" << endl; }
    base(const base &b) { cout << "base&" << endl; }  
    base(int a) { cout << "base int" << endl; }
    ~base() { cout << "~~base" << endl; }
    base &operator=(const base&b) { cout << "operator" << endl; return *this; }
};

class base2 : public b {
public:
    base2() { cout << "base2" << endl; }
    base2(int a) : b1(a) 
    {
        cout << "base2 int" << endl;
        b1 = a;  // 这里发生了隐式转换，int型的a转换为base类，使用explicit修饰函数可避免这种隐式转换
    }
    ~base2() { cout << "~~base2" << endl; }
    base b1;
};


void handle(int& x) 
{
    std::cout << "Lvalue\n";
}

void handle(int&& x) 
{
    std::cout << "Rvalue\n";
}

void handle(const int& x) 
{
    std::cout << "const Lvalue\n";
}

void handle(const int&& x) 
{
    std::cout << "const Rvalue\n";
}

template<typename T>
void process(T&& arg)               // 通用引用模版（可接收左值引用和右值引用）
{               
    //handle(std::forward<T>(arg));   // 完美转发， T可推导为int或者int&&
    //handle(static_cast<T&&>(arg));
    handle(move(arg));
}


class cls {
public:
    cls(initializer_list<pair<string, int>> l) {
        for (auto ele : l) {
            cout << ele.first << " - " << ele.second << endl;
        }
    }
};

class cls2 {
public:
    virtual void func(){
        cout << "cls2" << endl;
    }
};

class cls3 : public cls2 {
public:
    virtual void func(){
        cout << "cls3" << endl;
    }
    cls3() {
        func();
    }
};

struct B {
    char e;      // 1 字节
    int a;       // 4 字节
    char b;      // 1 字节
    double c;    // 8 字节
    char d;      // 1 字节
};

/*
template <typename T>
void printx(T value) {
    if constexpr (std::is_integral<T>::value) {
        std::cout << "Integral: " << value << std::endl;
    } else if constexpr (std::is_floating_point<T>::value) {
        std::cout << "Floating-point: " << value << std::endl;
    } else {
        std::cout << "Unknown type" << std::endl;
    }
}

// 对整数类型有效
template <std::integral T>
void printxx(T value) {
    std::cout << "Integral: " << value << std::endl;
}

// 对浮点数类型有效
template <std::floating_point T>
void printxx(T value) {
    std::cout << "Floating-point: " << value << std::endl;
}

int mainxxx() {
    printx(42);        // 输出 "Integral: 42"
    printx(3.14);      // 输出 "Floating-point: 3.14"

    cout << __cplusplus << " " <<  endl;

    #ifdef __cpp_concepts
    std::cout << "Concepts are supported. Version: " << __cpp_concepts << std::endl;
    #else
        std::cout << "Concepts are NOT supported." << std::endl;
    #endif

    printxx(33);
    printxx(33.333);

    return 0;
}

void test_cls2()
{
    int x = 0;
    const int y = 0;
    process(x);
    process(move(x));
    process(y);
    process(move(y));

    cls cls1 = {{"a", 1},{"b", 2}};

    cout << "sizeof(B):" << sizeof(B) << endl; 

    cls3();

    mainxxx();
}
*/