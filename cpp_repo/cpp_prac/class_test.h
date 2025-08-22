#pragma once

class MyClass {
public:
    MyClass();
    ~MyClass();

    MyClass(const MyClass &cls);
    MyClass& operator=(const MyClass &ohter);

private:
    int len;
    int *p_data;
    static int data;

    friend void friend_func(const MyClass &cls);
    friend class MyClass2;
};

class MyClass2 {
public:
    void AccessCls(const MyClass &cls);
};

void friend_func(const MyClass &cls);


// 模板类，带默认模版参数
template <typename T1 = int, typename T2 = double>
class MyPair {
private:
    T1 first;
    T2 second;
public:
    MyPair(T1 f, T2 s) : first(f), second(s) {}

    T1 getFirst() const 
    {
        return first;
    }

    T2 getSecond() const 
    {
        return second;
    }

    T1 add(T1 v1, T1 v2) 
    {
        return v1 + v2;
    }
};




void test_cls();

void test_base();

void test_cls2();