# include <iostream>
# include <functional>
# include <algorithm>
# include <vector>
# include <cstdarg>
# include "base_test.h"
# include "toos.h"
# include <thread>

using namespace std;

void func1(int &p)
{
    print(p);
}

void func2(int x, int y) 
{
    std::cout << x << " " << y << std::endl;
}

void func3(std::ostream& os, int value) 
{
    os << value << std::endl;
}

void test_return()
{
    cout << "test_return1" << endl;
    cout << "test_return2" << endl;
    cout << "test_return3" << endl;
    cout << "test_return4" << endl;
    cout << "test_return5" << endl;
    cout << "test_return6" << endl;
}


void func13t(int &p)
{
    p++;
}
void func12(int &p)
{
    p = 32;
}

void func_static() {
    static int x = 10;  // 存储在 .data 段，因为它已初始化
    static int y;       // 存储在 .bss 段，因为它未初始化
    std::cout << "x: " << x << ", y: " << y << std::endl;
}

void base_test()
{

    cout << "base_test start" << endl;
/*
    int a = 3;
    int &b = a;
    int &c = b;
    c = 100;
    print(a, b, c);     // 100 100 100
    print(&a, &b, &c);  // 0x7fff52b24e44 0x7fff52b24e44 0x7fff52b24e44

    print("==========");

    double d = 23.33;
    double &a = d;
    print("==========");

    int a = 3;
    print(std::ref(a));

    int value = 42;
    auto bound_print = std::bind(func1, std::ref(value));
    bound_print();
    print("==========");


    // 新对象bound_print的第一个参数传递给func2的第二个参数
    auto bound_print = std::bind(func2, 10, std::placeholders::_1); 
    bound_print(123);   // 10 123
    

    std::ostream& os = std::cout;
    auto bound_print = bind(func3, ref(os), 42);
    bound_print();
    print("==========");

    double d = 3.14;
    int i = static_cast<int>(d);  
    print(i);

    class Base {};
    class Derived : public Base {};
    Base* b = new Derived();
    Derived* d1 = static_cast<Derived*>(b);     // 向下转换


    test_return();

    for (int i = 0; i < 10; i++) {
        cout << "i = " << i << endl;
    }

    cout << "fdas1" << endl;
    cout << "fdas2" << endl;
    cout << "fdas3" << endl;
    cout << "fdas4" << endl;

    const int &aa2 = 123;
    int &&aa3 = 123;
    cout << "base_test end" << endl;
   


    int value = 42;
    auto bound_print = std::bind(func12, std::ref(value));  // ref显示传递引用
    bound_print();  
    cout << value << endl; // 32

    std::thread tt(func13t, std::ref(value));
    tt.join();
    cout << value << endl;
 */
    func_static();

}


class Base {
public:
    virtual ~Base() = default;  // 启用 RTTI
};

class Derived : public Base {};

void func4(const int* ptr) 
{
    int* non_const_ptr = const_cast<int*>(ptr); // 去除 const 限定符
    *non_const_ptr = 20;                        // 修改值
}

void base_test2() 
{
    cout << "base_test2 start" << endl;
/*
    Base* basePtr = new Derived;
    Derived* derivedPtr = dynamic_cast<Derived*>(basePtr);
    if (derivedPtr != nullptr) {
        std::cout << "Conversion successful\n";     // here
        delete basePtr;
    } else {
        std::cout << "Conversion failed\n";
    }
    
    Base* basePtr2 = new Base();
    Derived* derivedPtr2 = dynamic_cast<Derived*>(basePtr);
    if (derivedPtr2 != nullptr) {
        std::cout << "Conversion successful\n";
        delete derivedPtr2;
    } else {
        std::cout << "Conversion failed\n";         // here
    }
    
    const int a = 10;
    func4(&a);                      // 警告：修改了常量对象
    std::cout << a << std::endl;    // 输出 20 (未定义行为)
*/
    cout << "base_test2 end" << endl;
}

void func5(int a)
{
    cout << a << " ";
}

void base_test3() 
{
    cout << "base_test3 start" << endl;
    std::vector<int> vec = {1, 2, 3, 4, 5};
    for_each(vec.begin(), vec.end(), func5);
    cout << endl;

    for_each(vec.begin(), vec.end(), [](int a){ cout << a << " ";});
    cout << endl;

    print(sizeof(int), sizeof(short), sizeof(long), sizeof(long long));
    print(sizeof(unsigned int), sizeof(unsigned short), sizeof(unsigned long), sizeof(unsigned long long));

    print(sizeof(float), sizeof(double), sizeof(long double)); // 4 8 16
    print(sizeof(char), sizeof(wchar_t));
    cout << "base_test3 end" << endl;
}

void func6(int a = 1, int b = 2)
{
    cout << a << " " << b << endl;
}

void func7(int b, int a = 1)
{
    cout << a << " " << b << endl;
}

void print_var(const char* format, ...) {
    va_list args;               // 1. va_list用于存储参数列表
    va_start(args, format);     // 2. va_start初始化va_list
    
    const char* ptr = format;
    while (*ptr) {
        if (*ptr == '%') {      // 解析格式化参数
            ++ptr;
            if (*ptr == 'd') {  
                int i = va_arg(args, int);                      // 3. va_arg 访问参数
                std::cout << i << " ";
            } else if (*ptr == 'f') {
                double d = va_arg(args, double);                // va_arg 访问参数
                std::cout << d << " ";
            } else if (*ptr == 's') {
                const char* s = va_arg(args, const char*);      // va_arg 访问参数
                std::cout << s << " ";
            }
        }

        ++ptr;
    }
    
    va_end(args);           // 4. va_end 结束处理。
    std::cout << std::endl;
}

void func9(int value, void (*func)(int));

void func9(int value, void (*func)(int)) 
{
    func(value);
}

void func8(int x) {
    std::cout << x << std::endl;
}


template<typename T>
void print_var2(T t)        // 相当于递归的退出条件
{
    cout << t << endl;
}

// 第一个参数类型为T，后续参数类型形成可变模版ARGS
template<typename T, typename... ARGS>      // 变长模版格式 typename... ARGS
void print_var2(T first, ARGS... args)      // 可变参数格式 ARGS... args
{
    cout << first << " ";
    print_var2(args...);                    // 可变参数被使用的格式 args...
}

/*
// 模板函数，接受任意数量的参数
template <typename... Args>
void print_var3(Args... args) {
    // 折叠表达式(将args中的元素逐个引用cout，即输出，中间没有空格)
    // (std::cout << ... << args) << std::endl; 

    // 输出空格, 这种格式是将args中的参数逐个引用在表达式 cout << " " << args中
    // ((std::cout << " " << args), ...) << std::endl; // 折叠表达式

    // 输出空格，且第一个元素不输出空格
    //  (first ? (first = false, "") : " ")  三元运算处理第一个输出"", 后续元素输出空格
    bool first = true;
    ((std::cout << (first ? (first = false, "") : " ") << args), ...) << endl;
}
*/
void func10(int a, int b)  
{
}
int func11(int a)
{
    cout << a << " ";
    return a;
}

// 左值参数
void func13(int &t)
{
    cout << "func13(int &t)" << endl;
}

// 右值参数
void func13(int &&t)
{
    cout << "func13(int &&t)" << endl;
}

template<typename T>
void func12(T&& t)                  // 通用模版，可接受左值和右值
{   
    func13(std::forward<T>(t));     // 完美转发左值和右值
}

void base_test4()
{
    // 默认参数测试
    func6();            // 1 2
    func6(10);          // 10 2
    func6(10, 20);      // 10 20
    
    // 函数作为参数
    func9(100, func8);  // 100
    func9(101, [] (int val) { cout << val << endl;});   // 101

    // 可变参数测试
    print_var("%d, %f, %s", 4, 3.3, "stringTest");
    print_var("%d, %f, %s", 4, 3.3, "stringTest", 3, 4);
    print_var2(4, 3.3, "stringTest");
    //print_var3(4, 3.3, "stringTest", 'c', "test");  // 4 3.3 stringTest c test201703
    
    // 参数构造顺序
    func10(func11(1), func11(12));  // 12 1 
    cout << endl;
    // c++版本
    auto VER = __cplusplus;
    print(VER);

    // 参数转发
    int a = 1;
    func12(a);              // func13(int &t)
    func12(std::move(a));   // func13(int &&t)
    func12(1);              // func13(int &&t)

}

int *func20(int size)
{
    return new int[size];
}

int &func20(vector<int> &vec, int idx)
{
    return vec[idx];  
}

void func21(int i) { cout << "int " <<  i << endl;}
void func21(double d) { cout << "double " <<  d << endl;}
void func21(const string &s) { cout << "string " <<  s << endl;}

int Max(int a, int b)
{
    cout << "int Max(int a, int b)  ";
    return a > b ? a : b;
}

template<typename T>
T Max(T a, T b)  // 模板包括普通函数
{
    cout << "T Max(T a, T b) ";
    return a > b ? a : b;
}

template<typename T>
T Max(T a, T b, T c) // 模板函数重载
{
    cout << "T Max(T a, T b, T c)  ";
    return Max(Max(a, b), c);
}

int factorial(int n)
{
    if (n == 0) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

template <typename T>
class MyClass {
    public:
        static int cnt;     // 这里只是声明，定义需要再类外
        static T cnt2;
};

template<typename T>
int MyClass<T>::cnt = 0;    // 在类外定义，需要携带模版

template<typename T>
T MyClass<T>::cnt2 = 0;    // 在类外定义，需要携带模版

class BigObject {
public:
    BigObject() {
        std::cout << "BigObject constructed\n";
    }
    BigObject(const BigObject&) {
        std::cout << "BigObject copied\n";
    }
    BigObject(BigObject&&) noexcept {
        std::cout << "BigObject moved\n";
    }
    ~BigObject() {
        std::cout << "BigObject destructed\n";
    }
};

BigObject createBigObject() {
    return BigObject();
}

void base_test5()
{
    int *p = func20(10);
    delete []p;

    vector<int> vec = {1,2,3};          
    cout << func20(vec, 0) << endl;     // 返回引用
    func20(vec, 2) = 122;               // 修改返回的引用
    for_each(vec.begin(), vec.end(), [](int val){cout << val << " ";});  // 1 2 122
    cout << endl;

    func21(1);          // int 1
    func21(2.3);        // double 2.3
    func21("str");      // string str

    int a = 1;
    int b = 2;
    cout << Max(a, b) << endl;          // int Max(int a, int b)  2 当函数模板和普通函数都符合调用时,优先选择普通函数
    cout << Max<>(a, b) << endl;        // T Max(T a, T b) 2        若显示使用函数模板,则使用<> 类型列表
    cout << Max(3.0, 4.0) << endl;      // T Max(T a, T b) 4        如果函数模板产生更好的匹配使用函数模板
    cout << Max(5.0, 6.0, 7.0) << endl; // T Max(T a, T b, T c)  T Max(T a, T b) T Max(T a, T b) 7
    cout << Max('a', 100) << endl;      //int Max(int a, int b)  100    调用普通函数 可以隐式类型转换

    print(factorial(3));

    // 模板中的static
    MyClass<int> cls; 
    MyClass<int> cls2; 
    MyClass<double> dcls;
    MyClass<double> dcls2;
    
    cls.cnt = 23;    
    dcls.cnt = 24;
    print(cls.cnt, cls2.cnt, MyClass<int>::cnt);        // 23 23 23
    print(dcls.cnt, dcls2.cnt, MyClass<double>::cnt);   //  24 24 24


    MyClass<int>::cnt2 = 33;
    dcls.cnt2 = 44;
    print(cls.cnt2, cls2.cnt2, MyClass<int>::cnt2);         // 33 33 33
    print(dcls.cnt2, dcls2.cnt2, MyClass<double>::cnt2);    // 44 44 44

    
    cout << "---------" << endl;
    BigObject obj1 = createBigObject();
}