
#include <iostream>
#include <chrono>
#include <ctime>
#include <math.h>

using namespace std;

void test_high_perfermance()
{

 /*

    chrono::time_point<chrono::system_clock> t1 = chrono::system_clock::now();
    time_t t1r = chrono::system_clock::to_time_t(t1);
    cout << ctime(&t1r) << endl;

    auto start1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; i++)
    {
        float c = exp(2.0);
    }
    auto end1 = chrono::high_resolution_clock::now();
    chrono::duration<double> du = end1 - start1;
    cout << du.count() << endl;  // 默认为秒

    chrono::duration<double, micro> du2 = end1 - start1;
    cout << du2.count() << endl;  // 微秒

    auto du3 = chrono::duration_cast<chrono::nanoseconds>(du2);
    cout << du3.count() << endl;

    chrono::duration<double, std::nano> du4 = end1 - start1;
    cout << du4.count() << endl;


    chrono::time_point<chrono::high_resolution_clock> th1 = chrono::high_resolution_clock::now();
    chrono::duration<double> duh = th1.time_since_epoch();
    cout << duh.count() << endl; // 秒
    cout << chrono::duration_cast<chrono::hours>(duh).count() / 24 / 365 << endl; // 年

    chrono::time_point<chrono::high_resolution_clock, chrono::duration<double, micro>> th2 = chrono::high_resolution_clock::now();
    cout << th2.time_since_epoch().count() << endl; // 微秒

    cout << chrono::time_point_cast<chrono::seconds>(th2).time_since_epoch().count() << endl;  // 转换精度为秒


    auto start_st = chrono::steady_clock::now();
    for (int i = 0; i < 10000; i++)
    {
        float c = exp(2.0);
    }
    auto end_st = chrono::steady_clock::now();
    chrono::duration<double, micro> du_st = end_st - start_st;
    cout << du_st.count() << endl;

    auto start = chrono::steady_clock::now(); 
    cout << start.time_since_epoch().count() << endl;

    chrono::time_point<chrono::system_clock> p0;
    std::time_t epoch_time = std::chrono::system_clock::to_time_t(p0);
    std::cout << "epoch: " << std::ctime(&epoch_time);

*/

    //cout << std::chrono::milliseconds(1s).count() << endl;

    

   
    clock_t start = clock();
    // do something
    for (int i = 0; i < 100000000; i++)
    {
        float c = exp(2.0);
    }

    clock_t end = clock();
    cout << end << " " << start << endl;

    // 打印程序耗时，单位：秒s
    std::cout << (double)(end - start) / CLOCKS_PER_SEC << std::endl;

    //auto start = chrono::steady_clock::now(); //chrono::high_resolution_clock::now();
    //cout << start << endl;

    time_t t;
    cout << ctime(&t) << endl;
    time_t t2 = time_t(0);
    cout << ctime(&t2) << endl;
    
    time_t now = time(0);
    cout << ctime(&now) << endl;

    tm *tm1 = localtime(&now);
    cout << tm1->tm_year + 1900 << " " << tm1->tm_mon + 1 << " " << tm1->tm_hour << endl;

    tm *tm2 = gmtime(&now);
    cout << tm2->tm_year + 1900 << " " << tm2->tm_mon + 1 << " " << tm2->tm_hour << endl;

    time_t t3 = mktime(tm1);
    cout << ctime(&t3) << endl;

    time_t t4 = mktime(tm2);
    cout << ctime(&t4) << endl;


}