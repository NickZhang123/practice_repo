# include <iostream>
# include "inherit_test.h"
# include <memory>
# include "toos.h"

/*
void test_memalloc()
{
    allocator<Base> alloc;
    int cnt = 5;
    Base *p = alloc.allocate(cnt);          // 分配内存，指定对应模版数量即可
    
    for (int i = 0; i < cnt; i++) {
        if (i > 3) {
            alloc.construct(p + i);         // 使用默认无参构造函数
        } else {
            alloc.construct(p + i, 666);    // 使用参数333作为构造函数入参，则会调用有参的构造函数
        }
    }

    for (int i = 0; i < cnt; i++) {
        alloc.destroy(p + i);               // 调用对象的析构函数
    }

    alloc.deallocate(p, cnt);               // 释放内存
}



void testA::ppp()
{
    cout << "testA::ppp" << endl;
}
*/

std::ostream& operator<< (std::ostream& out, const OpCls2 &cls2) 
{
    out << cls2.value;
    return out;
}

class Base {
public:
    virtual void f() { cout << "Base::f" << endl; }
    virtual void f2() { cout << "Base::f2" << endl; }
private:
    int b = 0xFFFF;
};

class Base1 : public Base {
public:
    virtual void f() { cout << "Base1::f" << endl; }
    virtual void g() { cout << "Base1::g" << endl; }
    virtual void h() { cout << "Base1::h" << endl; }
private:
    int b1 = 1;
};
class Base2 : public Base {
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


void test_inherit()
{   
    // 构造顺序测试
    //base2 b;
    // base2 b(2);

    // 内存分配测试
    //test_memalloc();
    //Derived dev;

    // 虚函数表测试
    //Base *p = new Derived();
    //p->Print();

    // print(sizeof(Base));
/*
    using Fn = void(*)();

    Base b(333);
    cout << sizeof(Base) << endl;       // 16，包含一个虚汗是表指针8， 一个int成员4， 然后8对齐，形成16
    cout << sizeof(Derived) << endl;    // 24, 包含一个虚汗是表指针8， 一个基类int4， 两个子类int8， 对齐后24

    // 将b地址转化为int指针类型并取值，目的是要取出虚函数表地址
    // 因为地址是指针，可能占用8字节空间，这里使用int4字节不一定正确
    int addr = *(int *)(&b);
    
    // 取虚函数表的第一个指针偏移，即第一个函数 
    Fn f1 = (Fn)(*(int *)addr);  
    f1();                                       // Base::Print
    f1 = (Fn)(*(int *)(*(int *)(&b)));          // 直接转换，Base::Print
    f1(); 


    // 取虚函数表第二个指针偏移，因为指针大小是8，这里偏移两个int
    Fn f2 = (Fn)(*((int *)addr + 2));  
    f2();                                       // Base::Print2
    f2 = (Fn)(*((int *)(*(int *)(&b)) + 2));    // Base::Print2
    f2(); 

    // 先将对象转化为三级指针（第一级指针的解引用取虚函数表地址，后面两级指针形成虚函数表的数组表达形式）
    // 好处：1. 对三级指针的解引用获取指针数组格式的二级指针； 
    //      2. 解引用大小取决于解引用的类型，这里类型是void**, void**的大小依然是指针大小，这里是8字节，
    //          相当于对内存中第一个8字节进行解析，即内存中虚函数表指针的解析
    void **table = *(void ***)&b;

    // 直接利用指针数组格式的方式将元素转化为函数指针进行访问
    Fn f3 = (Fn)table[0];   
    f3();
    Fn f4 = (Fn)table[1];
    f4();


    cout << sizeof(long) << sizeof(long long) << endl;
    long **tab = (long **)(&b);
    cout << "指向虚函数表的指针地址: " << (long long *)&b << endl;
    cout << "虚函数表地址: " << *(long long *)&b << endl;
    long long **func = (long long **)&b;
    cout << "虚函数表中第一个函数指针地址: " << func[0] << endl;
    ((Fn)func[0][0])();
    ((Fn)func[0][1])();
    // 也可以（先取得虚函数表地址，将地址转换为指针数组，每次平移一个指针）
    long long *p_func = (long long *)*(long long *)&b;
    ((Fn)p_func[0])();
    ((Fn)p_func[1])();


    // 多继承测试
    using Func = void(*)();
    Base1 b1;
    Base2 b2;
    Son1 son1;
    cout << &b1 << " " << &b2 << " " << &son1 << endl;

    long long **func = (long long **)&son1;
    ((Func)func[0][0])();
    ((Func)func[0][1])();
    ((Func)func[0][2])();
    ((Func)func[0][3])();

    cout << &son1 + 16 << endl;
    func = (long long **)((char *)&son1 + 16); // 转成char*，跳过第一个虚函数表和成员变量
    ((Func)func[0][0])();
    ((Func)func[0][1])();
    ((Func)func[0][2])();
*/
/*
    // 菱形继承
    using Func = void(*)();
    Base1 b1;
    Base2 b2;
    Son1 son1;
    cout << &b1 << " " << &b2 << " " << &son1 << endl;

    long long **func = (long long **)&son1;
    ((Func)func[0][0])();   // Base1::f
    ((Func)func[0][1])();   // Base::f2
    ((Func)func[0][2])();   // Base1::g
    ((Func)func[0][3])();   // Son1::h
    ((Func)func[0][4])();   // Son1::i

    cout << &son1 + 16 << endl;
    func = (long long **)((char *)&son1 + 16);
    ((Func)func[0][0])();   // Base2::f
    ((Func)func[0][1])();   // Base::f2
    ((Func)func[0][2])();   // Base2::g
    ((Func)func[0][3])();   // Son1::h
*/

/*
    Base1 b1;
    using Func = void(*)();
    long long **func = (long long **)&b1;
    ((Func)func[0][0])();
    ((Func)func[0][1])();
    ((Func)func[0][2])();

    cout << sizeof(Base1) << endl;

    print(&b1, &b1.b1, &(b1.Base::b));
    
    cout << (long long *)((char *)&b1 + 16) << endl;

    func = (long long **)((char *)&b1 + 16);
    cout << func[0][0] << endl;
    //((Func)func[1][0])();

    // 纯虚函数
    testB b;
    b.ppp();

    // 重载、重写、覆盖
    derive d;  
    //d.print(); 	// compile error 虚函数也会发生同名函数覆盖，可以使用d.base::print()调用
    d.print(2);

    const derive& b = d;
    //b.print();  // compile error 虚函数也会发生同名函数覆盖，可以使用d.base::print()调用

    //Son1 s;


    OpCls1 obj1(12313);
    OpCls1 obj2(111);

    obj1 << cout;
    obj2 << (obj1 << cout);
    cout << endl;

    OpCls2 obj3(333);
    OpCls2 obj4(444);
    cout << obj3 << obj4 << endl;
    */

    Son1 son1;
    Base1 *b1 = new Son1();
    b1->g();   
}
