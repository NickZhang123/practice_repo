#pragma once
# include <iostream>

using namespace std;

/*
class Base {
public:
    Base() { cout << "Base" << endl; }
    Base(int data): _data(data) { cout << "Base" << " " << data << endl; }
    
    virtual void Print() { cout << "Base::Print" << endl; } 
    virtual void Print2() { cout << "Base::Print2" << endl; } 

    virtual ~Base() { cout << "~Base" << endl; }
    
private:
    int _data;
};

class Derived : public Base {
public:
    Derived() { cout << "Derived" << endl; }
    ~Derived() { cout << "~Derived" << endl; }

    void Print() override { cout << "Derived::Print" << endl; } 
private:
    int _data_de;
    int _data_de2;
};


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
    base2(int a) : b(a) 
    {
        cout << "base2 int" << endl;
        b = a;
    }
    ~base2() { cout << "~~base2" << endl; }
    base b;
};

*/
/* 多继承
class Base1 {
public:
    virtual void f() { cout << "Base1::f" << endl; }
    virtual void g() { cout << "Base1::g" << endl; }
    virtual void h() { cout << "Base1::h" << endl; }
private:
    int b1 = 1;
};
class Base2 {
public:
    virtual void f() { cout << "Base2::f" << endl; }
    virtual void g() { cout << "Base2::g" << endl; }
    virtual void h() { cout << "Base2::h" << endl; }
private:
    int b2 = 2;
};

class Son1 : public Base1, public Base2 {
public:
    virtual void i() { cout << "Son1::i" << endl; }
    virtual void h() { cout << "Son1::h" << endl; }

private:
    int s = 4;
    int b1 = 8;
    int b2 = 16;
};
*/

/*
// 菱形继承1
class Base {
public:
    Base() { cout << "Base" << endl; }
    virtual void f() { cout << "Base::f" << endl; }
    virtual void f2() { cout << "Base::f2" << endl; }
private:
    int b = 0xFFFF;
};

class Base1 : public Base {
public:
    Base1() { cout << "Base1" << endl; }
    virtual void f() { cout << "Base1::f" << endl; }
    virtual void g() { cout << "Base1::g" << endl; }
    virtual void h() { cout << "Base1::h" << endl; }
private:
    int b1 = 1;
};
class Base2 : public Base {
public:
    Base2() { cout << "Base2" << endl; }
    virtual void f() { cout << "Base2::f" << endl; }
    virtual void g() { cout << "Base2::g" << endl; }
    virtual void h() { cout << "Base2::h" << endl; }
private:
    int b2 = 2;
};

class Son1 : public Base1, public Base2 {
public:
    Son1() { cout << "Son1" << endl; }
    virtual void i() { cout << "Son1::i" << endl; }
    virtual void h() { cout << "Son1::h" << endl; }

private:
    int s = 4;
    int b1 = 8;
    int b2 = 16;
};

*/
/*
// 菱形继承2
class Base {
public:
    // Base() { cout << "Base" << endl; }
    virtual void f() { cout << "Base::f" << endl; }
    virtual void f2() { cout << "Base::f2" << endl; }
public:
    int b = 0xFFFF;
};

class Base1 : virtual public Base {
public:
    // Base1() { cout << "Base1" << endl; }
    virtual void f() { cout << "Base1::f" << endl; }
    virtual void g() { cout << "Base1::g" << endl; }
    virtual void h() { cout << "Base1::h" << endl; }
public:
    int b1 = 1;
};

class Base2 : virtual public Base {
public:
    // Base2() { cout << "Base2" << endl; }
    virtual void f() { cout << "Base2::f" << endl; }
    virtual void g() { cout << "Base2::g" << endl; }
    virtual void h() { cout << "Base2::h" << endl; }
private:
    int b2 = 2;
};

class Son1 : public Base1, public Base2 {
public:
    // Son1() { cout << "Son1" << endl; }
    virtual void i() { cout << "Son1::i" << endl; }
    virtual void h() { cout << "Son1::h" << endl; }
    virtual void f() { cout << "Son1::f" << endl; }    // 必须覆盖Base1和Base2中都继承了的函数

private:
    int s = 4;
    int b1 = 8;
    int b2 = 16;
};

class testA {
public:
    virtual void ppp() = 0;
};

class testB : public testA {
public:
    void ppp() {
        testA::ppp();
    }
};

// 重载、重写、覆盖
class base {
public:
    virtual void print() { cout << "base" << endl; };
    virtual void print() const { cout << "const base" << endl; };
};

class derive : public base {
public:
    // 参数不同，无法发生重写； 可以发生覆盖，覆盖父类的虚函数
    virtual void print(int a) { cout << "son" << endl; };  
};
*/

class OpCls1 {
private:
    int value;
public:
    OpCls1(int v = 0) : value(v) {}

    // 成员函数重载 <<
    std::ostream& operator<< (std::ostream& out) const 
    {
        out << value;
        return out;
    }
};

class OpCls2 {
private:
    int value;
public:
    OpCls2(int v = 0) : value(v) {}
    // 重载为友元
    friend std::ostream& operator<< (std::ostream& out, const OpCls2 &cls2);
};

void test_inherit();