#include <iostream>
#include <vector>
#include <memory>
#include <vector>
#include <set>
#include <algorithm>
#include "toos.h"


using namespace std;


void test_auto()
{
    vector<int> vec = {1,2,3,4};
    for (auto &ele : vec) {
        cout << ele << " ";
    }
    cout << endl;
}

class Base {
public:
    virtual ~Base() {}
};
class Derived : public Base {};

void test_decltype()
{
    int x = 4;
    decltype(x) y = 111;
    const int t = 3;
    decltype(t) t2 = t;
    //t2 = y;   // error，具有const属性

    int &t3 = x;
    t3 = y;
    decltype(t3) t4 = x;
    t4 = y;

    // 使用 decltype 推断函数返回类型
    auto add = [](int a, int b) -> decltype(a + b) {
        return a + b;
    };

    decltype(add(1, 2)) result = add(3, 4); // result 的类型是 int
    print(result);

    auto vec = vector<double>();
    cout << typeid(vec).name() << endl;

    Base* b = new Derived();
    std::cout << typeid(*b).name() << std::endl; // 输出 Derived 的类型信息

    
}

void test_lambda()
{
    int value = 1;
    auto copy_value = [value] {
        return value;
    };
    value = 100;
    auto stored_value = copy_value(); 
    cout << stored_value << endl;       // 1

    int testint = 123;
    auto func = [testint]() {
        cout << testint <</* testint2 <<*/ endl;
        //testint+=1; // 编译错误, 非mutable修饰无法修改
    };

    // mutable修饰后
    auto func2 = [testint]() mutable {
        cout << testint <</* testint2 <<*/ endl;
        testint+=1;
        return testint;
    };
    cout << func2() << testint << endl; // 124 123
    cout << func2() << testint << endl; // 125 123
    cout << func2() << testint << endl; // 126 123
};


/*
void test_autoptr()
{
    auto_ptr<string> ptr(new string("test"));
    auto_ptr<string> ptr2 = ptr;
    //cout << *ptr << endl;
}
*/

void delterfunc(int *p)
{
    cout << "delterfunc" << endl;
    delete p;
}

void test_uniqueptr()
{
    auto deleter = [](int *p) {
        cout << "deleter" << endl;
        delete p;
    };

    unique_ptr<int, decltype(deleter)> p(new int(5), deleter);
    unique_ptr<int, decltype(delterfunc)*> p2(new int(5), delterfunc);

    auto deletearr = [](int *p) {
        cout << "deletearr" << endl;
        delete []p;
    };
    // 管理数组，定义数组删除器
    unique_ptr<int[], decltype(deletearr)> p3(new int[5], deletearr);

    unique_ptr<int> up = make_unique<int>(1);
    //auto spv = make_unique<std::vector<int>>({10, 20}); // 错误，make_unique使用()完美转发,不支持直接用{}
    auto initList = {10, 20};  // 创建一个 std::initializer_list<int>
    for (const auto& elem : initList) {
        cout << elem << endl;
    }

    // 智能指针管理vector
    auto spv = std::make_unique<std::vector<int>>(initList); 
    for (const auto &ele : *spv) {
        cout << ele << endl;
    }
}

class TestSharedPtr {
public:
    TestSharedPtr(int data) : data(data) {cout << "TestSharedPtr" << endl;}
    virtual ~TestSharedPtr() {cout << data << "  ~TestSharedPtr" << endl;}
    int data;
};

class TestSharedPtr2 : public TestSharedPtr {
public:
    TestSharedPtr2(int data) : data2(data), TestSharedPtr(data) {cout << "TestSharedPtr2" << endl;}
    ~TestSharedPtr2() {cout << "~TestSharedPtr2" << endl;}
    int data2;
};

class B;  // 前向声明

class A {
public:
    A() { cout << "A" << endl; }
    ~A() { cout << "~A" << endl; }
    std::weak_ptr<B> b_ptr;
};

class B {
public:
    B() { cout << "B" << endl; }
    ~B() { cout << "~B" << endl; }
    std::weak_ptr<A> a_ptr;
};


template <typename T>
class SmartPoint;       // 前向声明，记得带模版类型

template <typename T>
class UtilsPtr {
public:
    UtilsPtr(T *t) : t(t) {cnt = 1;}
    ~UtilsPtr() {delete t;}
private:
    friend class SmartPoint<T>;     // 友元类也要模版类型
    int cnt;
    T *t;
};

template <typename T>
class SmartPoint {
public:
    SmartPoint(T *t) : ptr(new UtilsPtr<T>(t)) {};
    ~SmartPoint() 
    {
        if (ptr->cnt <=0 ) {
            delete ptr;
        }
    };

    SmartPoint(const SmartPoint &sp) 
    {
        ptr = sp.ptr;
        ptr->cnt++;
        cout << "计数值：" << ptr->cnt << endl;
    }

    SmartPoint & operator=(const SmartPoint &sp)
    {
        if (ptr == sp.ptr) {
            cout << "二者管理同一个值， 引用计数值为：" << sp.ptr->cnt << endl;
            return *this;
        }

        (ptr->cnt)--;
        cout << "原计数" << ptr->cnt << endl;
        if (ptr->cnt == 0) {
            delete ptr;
            ptr = nullptr;
        }

        ptr = sp.ptr;
        ptr->cnt++;
        cout << "当前对象计数值：" << ptr->cnt << endl;
        return *this;
    }

    T* operator->()
    {
        return ptr->t;
    }

    T& operator*()
    {
        return *(ptr->t);
    }

private:
    UtilsPtr<T> *ptr;
};


void test_sharedptr()
{
    shared_ptr<int> sp(new int[5]{1,2,3,4,5}, [](int *p){ cout << p[2] << endl; delete []p;});

    //auto p = new TestSharedPtr(5);
    //{
    //    shared_ptr<TestSharedPtr> sp1(p);
    //}
    //shared_ptr<TestSharedPtr> sp2(p); // error
    cout << "-------" << endl;
    {
        unique_ptr<TestSharedPtr> up(new TestSharedPtr2(123));
    }
    cout << "-------" << endl;
    {
        shared_ptr<TestSharedPtr> up(new TestSharedPtr2(123));
    }

    cout << "xxxxxxxxxxxxxxx" << endl;

    // shared_ptr循环引用
    {
        std::shared_ptr<A> a = std::make_shared<A>();
        std::shared_ptr<B> b = std::make_shared<B>();
        a->b_ptr = b;   
        b->a_ptr = a;   
    }
    cout << "-------" << endl;
    {
        SmartPoint<TestSharedPtr> sp1(new TestSharedPtr(4));
        cout << sp1->data << " " << (*sp1).data << endl;
        sp1->data = 123;
        cout << sp1->data << " " << (*sp1).data << endl;

        SmartPoint<TestSharedPtr> sp2(sp1);
        SmartPoint<TestSharedPtr> sp3 = sp1;
        sp3 = sp2;

        SmartPoint<TestSharedPtr> sp4(new TestSharedPtr(5));
        sp4 = sp3;

    }
    cout << "-------" << endl;

    shared_ptr<TestSharedPtr> spx1(new TestSharedPtr(333));
    cout << spx1.use_count() << endl;
    weak_ptr<TestSharedPtr> wp(spx1);
    shared_ptr<TestSharedPtr> spx2(spx1);
    shared_ptr<TestSharedPtr> spx3(spx1);
    cout << wp.use_count() << endl;
    cout << "----abc---" << endl;
}

class MyClass : public enable_shared_from_this<MyClass> {
public:
    void show() 
    {
        cout << "MyClass" << endl;
    }

    shared_ptr<MyClass> CreateSharedPtr()
    {
        shared_ptr<MyClass> sp = shared_from_this();
        cout << "create shared ptr, cnt = " << sp.use_count() << endl;
        return sp;
    }
};

void test_share_from_this()
{
    MyClass *cls = new MyClass();
    //cls->CreateSharedPtr(); // 不能直接使用功能

    shared_ptr<MyClass> sp(cls);
    auto sp2 = sp->CreateSharedPtr();
    cout << sp.use_count() << endl;
}

void initialFunc(initializer_list<int> list)
{
    for (const auto &i : list) {
        cout << i << " ";
    }
    cout << endl;
}

class MyClassInit {
public:
    MyClassInit() { cout << "MyClassInit" << endl;}
    MyClassInit(initializer_list<int> list) { cout << "MyClassInit init" << endl;}
    ~MyClassInit() { cout << "~MyClassInit" << endl;}
};
void test_initializerlist()
{
    //initialFunc({1,2,3,4,5});
    
    int arr[3] = {1,3,4};
    std::vector<int> vec = {1, 2, 3, 4};  // 使用 initializer_list 初始化 vector
    std::set<int> mySet = {5, 10, 15};  // 使用 initializer_list 初始化 set
    MyClassInit cls = {1,2,3,4};         // 使用 initializer_list 初始化 MyClassInit 对象
    auto list = {1, 2, 3, 4};  // 类型自动推导为 std::initializer_list<int>
    MyClassInit cls2({1,2,3,4});         // 使用 initializer_list 初始化 MyClassInit 对象
}

int foo() {
    return 42;
}

decltype(auto) func_decl(int a) {
    cout << a << endl;
    return foo();
}

enum class new_enum : unsigned int {
    value1,
    value2,
    value3 = 100,
    value4 = 100
};

void print_list(std::initializer_list<int> list) {
    cout << "List contains " << list.size() << " elements: ";
    
    for (auto it = list.begin(); it != list.end(); ++it) {
        cout << *it << " ";
    }
    
    cout << endl;
}



void cpp11_test()
{
    //test_auto();
    //test_decltype();nick.,1234
    
    //test_lambda();
    //test_autoptr();
    //test_uniqueptr();
    //test_sharedptr();

    //test_share_from_this();
    
    //test_initializerlist();
    //decltype(foo()) a;
    //func_decl(2);

    //cout << (new_enum::value4 < new_enum::value2) << endl;

    print_list({10, 20, 30, 40, 50});

    std::vector<int> vec = {5, 3, 8, 1, 2};
    std::sort(vec.begin(), vec.end(), [](int a, int b) {return a > b;});
    std::for_each(vec.begin(), vec.end(), [](int a){cout << a << endl;});
    std::sort(vec.begin(), vec.end(), greater<int>());
    std::for_each(vec.begin(), vec.end(), [](int a){cout << a << endl;});
    std::reverse(vec.begin(), vec.end());  // 反转顺序
    std::for_each(vec.begin(), vec.end(), [](int a){cout << a << endl;});

    string str = "fdsafga";
    sort(str.begin(), str.end());
    cout << str << endl;
}
