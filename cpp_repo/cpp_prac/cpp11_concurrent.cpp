#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <shared_mutex>
#include <vector>
#include "cpp11_test.h"

using namespace std;

#if 0

void hello() 
{
    cout << "hello ";
}


class ConTest {
public:
    ConTest(int data) : data(data) {cout << "ConTest" << endl;}
    ~ConTest() {cout << "~ConTest" << endl;}
    void ConTestFunc(int a) 
    {
        for (int i = 0; i < 100000; i++)
        {
            i++;
        }
        cout << a << "  " << data << endl;
    }
    int data;
};

void increment(int& value) 
{
    ++value;
}

void increment2(int value) 
{
    int n = 0; 
    while (n < 100000) {
        ++value;
        n++;
    }
    cout << n << " " << value << endl;
}

bool g_flag = true;
void run1()
{
    while (g_flag) {
        cout << "still running" << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

thread_local int cnt = 0;
void run2()
{
    for (int i = 0; i < 10; i++) {
        cnt++;
        cout << "Thread Id: " << this_thread::get_id() << ", cnt: " << cnt << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

void test_thread()
{
    //thread t(hello);
    //t.join();
    //thread t2([](){ cout << "world" << endl;});
    //t2.join();
/*
    ConTest ct(3);
    thread t3(&ConTest::ConTestFunc, &ct, 4);
    t3.join();

    int x = 11;
    thread t4(increment, std::ref(x));
    t4.join();
    cout << x << endl;

    thread t5(increment2, 1000);
    t5.detach();
    this_thread::sleep_for(chrono::seconds(3));
    
    thread t6(run1);
    this_thread::sleep_for(chrono::seconds(3));
    g_flag = false;
    t6.join();


    thread t7(run2);
    thread t8(run2);
    
    t7.join();
    t8.join();
*/
    thread t9(hello);
    cout << t9.get_id() << "  xxxxxxx " << this_thread::get_id() << endl;
    cout << thread::hardware_concurrency() << endl;
    cout << t9.hardware_concurrency() << endl;
    t9.join();
}

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void worker() 
{
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "Worker is waiting..." << std::endl;
    cv.wait(lock, [] { return ready; });         // 等待 ready == true
    std::cout << "tid: " << this_thread::get_id() << ", Worker is proceeding after getting the lock." << std::endl;
}

void set_ready() 
{
    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;
        std::cout << "Setting ready to true." << std::endl;
        cv.notify_one();  // 唤醒等待的 worker 线程
        std::this_thread::sleep_for(std::chrono::milliseconds(500));  // 延迟500毫秒，期间持有锁
        std::cout << "Notifier thread continues holding the lock." << std::endl;
    }
    std::cout << "Notifier thread released the lock." << std::endl;
}
void test_condition()
{
    std::thread t(worker);  // wait
    std::thread t2(worker); // wait
    std::this_thread::sleep_for(std::chrono::seconds(1)); // 模拟一些工作
    set_ready();    // notify
    set_ready();    // notify
    set_ready();    // notify
    set_ready();    // notify
    set_ready();    // notify

    t.join();
    t2.join();
}

std::mutex mtx1;
int gcnt = 0;
void getValAndInc()
{
    for (int i = 0; i < 10; i++) {
        mtx1.lock();
        gcnt++;
        cout << this_thread::get_id() << " , cnt = " << gcnt << endl;
        mtx1.unlock(); 
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

void getValAndInc2()
{
    for (int i = 0; i < 10; i++) {
        {
            lock_guard<mutex> lg(mtx1);
            gcnt++;
            cout << this_thread::get_id() << " , cnt = " << gcnt << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(500));  // 让出cpu，尽量切线程
    }
}

void getValAndInc3()
{
    for (int i = 0; i < 10; i++) {
        unique_lock<mutex> ul(mtx1);
        gcnt++;
        cout << this_thread::get_id() << " , cnt = " << gcnt << endl;
        ul.unlock();    // 手动释放
        this_thread::sleep_for(chrono::milliseconds(500));  // 让出cpu，尽量切线程    
    }
}

atomic<int> count1(0);   

void atomicInc()
{
    for (int i = 0; i < 10000000; i++) {
        ++count1;
    }
}

void test_atomic()
{
    thread t1(atomicInc);
    thread t2(atomicInc);
    t1.join();
    t2.join();
 
    cout << count1 << endl;
}

std::recursive_mutex rmtx;

void recursive_function(int depth) 
{
    std::lock_guard<std::recursive_mutex> lock(rmtx); // 每递归一次锁一次
    std::cout << "tid = " << this_thread::get_id() << ", Depth: " << depth << std::endl;
    
    if (depth > 0) {
        recursive_function(depth - 1);  // 递归调用
    }
}

void test_mutex()
{
    thread t1(recursive_function, 10);
   // thread t2(recursive_function, 3);

    t1.join();
    //t2.join();
}

std::shared_mutex remtx; // 读写锁
vector<int> vec;

// 读者
void reader(int id) 
{
    std::shared_lock<std::shared_mutex> lock(remtx);    // 获取共享锁， shared_lock管理
    std::cout << "Thread " << id << " is reading data: ";
    for (const auto& val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

// 写者
void writer(int id, int value) 
{
    std::unique_lock<std::shared_mutex> lock(remtx);    // 获取独占锁， unique_lock管理
    std::cout << "Thread " << id << " is writing data: " << value << std::endl;
    vec.push_back(value);
}


void test_rwlock() 
{
    
    thread t1(reader, 1);
    thread t2(reader, 2);
    thread t3(writer, 1, 4);
    t1.join();
    t2.join();
    t3.join();
}

std::once_flag flag;
void init() 
{
    std::cout << "Initialized!" << std::endl;
}

void threadFunc() 
{
    std::call_once(flag, init);
}
void  test_callonce()
{
    std::thread t1(threadFunc);
    std::thread t2(threadFunc);
    t1.join();
    t2.join();
}

void cpp11_concurrent()
{
    //test_thread();

    //test_mutex();
    //test_atomic();
    //test_condition();
    // test_rwlock();
    test_callonce();
    
}

#endif