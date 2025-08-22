#include <iostream>
#include <future>
#include <thread>
#include <vector>
#include <iomanip>

using namespace std;

#if 0

int func(int y)
{
    cout << "func" << endl;
    this_thread::sleep_for(std::chrono::seconds(1));
    return y * y;
}

// 任务不返回目标值，通过promise对象保存目标值
void func2(std::promise<int> &p, int y)
{
    cout << "func2" << endl;
    this_thread::sleep_for(std::chrono::seconds(1));
    return p.set_value(y * y);  // promise set_value接口设置值
}

void test_async1()
{
    std::promise<int> p;
    std::future<int> fr = p.get_future();  // promise返回future对象
    thread t(func2, std::ref(p), 9);   // 引用传入std::promise值

    cout << fr.valid() << endl;     // 任务有效性
    fr.wait();                      // 等待完成
    
    try {
        int res = fr.get();         // get可能抛出异常
        cout << res << endl;
    } catch (const exception &e) {
        cout << e.what() << endl;
    }

    t.join();
}

void test_async2()
{
    // 模版实例：返回值(参数)
    std::packaged_task<int(int)> task(func);   // packaged_task包装任务
    std::future fr = task.get_future();

    thread t(std::move(task), 9);  // 移动

    cout << fr.valid() << endl;     // 任务有效性
    fr.wait();                      // 等待完成
    
    try {
        int res = fr.get();         // get可能抛出异常
        cout << res << endl;
    } catch (const exception &e) {
        cout << e.what() << endl;
    }

    t.join();
}

void worker(int x, promise<int> p) 
{
    p.set_value(func(x));
}

void test_async3()
{
    vector<int> vec1 = {1, 2, 3};
    vector<future<int>> vec2;

    for (const auto &ele : vec1) {
        promise<int> p;
        future fr = p.get_future();
        vec2.push_back(std::move(fr));
        thread(worker, ele, std::move(p)).detach();
    }

    for (auto &ele : vec2) {
        try {
            int val = ele.get();
            cout << val << endl;
        } catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    }
}

void test_async4()
{
    auto func = [](int a){
        std::chrono::milliseconds ms(2000);
        std::this_thread::sleep_for(ms);
        return a;
    };

    // 1. async
    std::future<int> f1 = std::async(std::launch::async, func, 23);  // async不用thread参与实现异步

    // 2. packaged_task
    std::packaged_task<int(int)> task(func);
    std::future<int> f2 = task.get_future();
    std::thread(std::move(task), 23).detach(); // move转移，task作为thread的func

    // 3. promise
    std::promise<int> p;
    std::future f3 = p.get_future();
    std::thread([func](std::promise<int> p) {
        std::chrono::milliseconds ms(2000);
        std::this_thread::sleep_for(ms);
        p.set_value(func(23));
    }, std::move(p)).detach(); // move转移， promise作为thread的func的参数

    std::cout << "wait" << std::endl;

    f1.wait();
    f2.wait();
    f3.wait();

    std::cout << f1.get() << " " << f2.get() << " " << f3.get() << std::endl;
}

template<typename T>
struct MyStruct {
    static void print() 
    {
        std::cout << "Generic implementation" << std::endl;
    }
};


template<>
struct MyStruct<int> {
    static void print() 
    {
        std::cout << "Specialized for int" << std::endl;
    }
};

template<typename T, typename U>
struct MyPair {
    static void print() 
    {
        std::cout << "Generic Pair" << std::endl;
    }
};

template<typename T>
struct MyPair<T, T> {
    static void print() 
    {
        std::cout << "Specialized Pair where both types are the same" << std::endl;
    }
};

template<typename T>
ostream& operator<<(ostream &out, const MyPair<T, int> &mp)
{
    out << "MyPair operator()" << endl;
    return out;
}

template<typename T>
struct MyPair<T, int> {
    static void print() 
    {
        std::cout << "Specialized Pair where both types are the same 3" << std::endl;
    }

    // 为偏特化重载友元operator<<
    // 1. ostream为引用，非const引用
    // 2. operator<<后面加<>表示模版类型
    // 3. 参数mp也要加偏特化模版
    // 4. 友元函数定义处，也要加template<T>表示参数mp是模版
    friend ostream& operator<< <>(ostream &out, const MyPair<T, int> &mp);
};

template <auto value> 
void foo() 
{
    std::cout << value << std::endl;
    return;
}

template <typename T, auto BufSize>
class buffer_t {
private:
    T data[BufSize]; 				// BufSize作为数组大小
};

// 参数个数
template<typename... Args>                              // 表示可变数量、类型模版
void printf1(Args... args)                             // 可变数量、类型参数
{
    std::cout << "参数个数: " << sizeof...(args) << std::endl;  // 参数个数
}

// 递归结束
template<typename T>
void printf2(T t)
{
    cout << "最后一个参数：";
    cout << t << endl;
}

// 递归打印参数
template<typename T, typename... Args>                              // 表示可变数量、类型模版
void printf2(T t, Args... args)                             // 可变数量、类型参数
{
    std::cout << "参数个数: " << sizeof...(args) ;  // 参数个数
    cout << " " << t << endl;
    printf2(args...);   // 传递可变参数
}

template<typename T, typename... Ts>
auto printf3(T value, Ts... args) 
{
    std::cout << value << "----" << std::endl; 

    // (lambda表达式(), value)... 方式展开
    // ()... 用于展开可变参数，展开的每个可变参数传递进括号
    // 括号内部进行逗号操作，lambda表达式()表示生成一个匿名函数并调用， value是占位符，参数作为list的值
    (void) std::initializer_list<T> {
        (
            // initializer_list<T> 之一initializer_list的泛型实例为T
            [&args] (){ std::cout << args << std::endl; } ()
            , value
        )...
    };

    std::cout <<  "----" << std::endl; 
}


void test_async()
{
    //test_async1();
    //test_async2();
    //test_async3();
    // test_async4();

    MyStruct<int> ms;
    ms.print();

    // 匹配第三个
    MyPair<double, int> mp;
    mp.print();

    // 匹配第二个
    MyPair<double, double> mp2;
    mp2.print();

    // 匹配默认
    MyPair<string, double> mp3;
    mp3.print();

    buffer_t<string, 100> bs;

    foo<10>();

    int a = 1;
    double b = 3.3;
    string str = "xxx";

    //printf1(a, b, str, mp);

    //printf2(a, b, str, mp);

    //printf3(a, b, str, mp);

    cerr << "err2" << endl;
    clog << "err" << endl;

    // 设置精度
    double pi = 3.1415926535897945646151;
    cout << pi << endl;
    cout << std::fixed << std::setprecision(2) << pi << std::endl;  // 3.14
    cout << pi << "-------" << endl;

    // 设置位宽
    std::cout <<  std::setw(10) << std::left << "Hello" << std::endl;   // Hello
    std::cout <<  std::setw(10) << std::right << "Hello" << std::endl;  //      Hello
    cout << pi << "-------" << endl;

    double pi2 = 3.1;
    cout << setw(15) << right << fixed << setprecision(4) << pi << endl;    //          3.1416
    cout << setw(15) << right << fixed << setprecision(4) << pi2 << endl;   //          3.1000
    cout << pi << "-------" << endl;

    // 默认格式和科学计数法
    std::cout << "Default format: " << std::defaultfloat << pi << std::endl;    // 3.142
    cout << pi << "-------" << endl;
    std::cout << "scientific format: " << std::scientific << pi << std::endl;   // 3.1416e+00
    cout << pi << "-------" << endl;
    

}
#endif