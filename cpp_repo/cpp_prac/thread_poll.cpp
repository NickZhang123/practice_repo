#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <atomic>
#include <functional>
#include <condition_variable>
#include <mutex>
#include <chrono>
#include <future>
#include <concepts>

using namespace std;

using Task = function<void()>;

class ThreadPool {
public:
    ThreadPool(int threadNum) : threadNum(threadNum) {
        cout << "线程启动，线程数量:" << threadNum << endl;
        stop.store(false);
        for (int i = 0; i < threadNum; i++) {
            threads.emplace_back(thread(&ThreadPool::worker, this)); // 注意捕获类成员函数时的格式，参数为this
        }
    }

    ~ThreadPool() {
        stop.store(true);           // 置退出标记位为true
        cv.notify_all();            // 唤醒所有线程

        for (auto &t : threads) {   // 等待所有线程完成任务 -- 改成范围for
            cout << "正在销毁线程[" << t.get_id() << "]" << endl; 
            if (t.joinable()) {
                t.join();           // 阻塞主线程，等待子线程完成任务
            }
        }
        
    }

    void PushTask(Task t) {
        // 优化，加入队列后可释放锁
        {
            lock_guard<mutex> lg(mtx);
            tasks.push(t);
            //cout << "添加任务成功" << endl;
        }
        cv.notify_one();
    }

private:
    // 线程工作函数
    void worker() {
        cout << "线程[" << this_thread::get_id() << "]" << "启动完成" << endl;
        while (!stop.load()) {
            // 获取锁  -- 优化，锁范围不用包括任务执行
            Task t;
            {
                unique_lock<mutex> ul(mtx);

                // cv等待，校验条件  -- 注意，捕获this对象； 返回判断条件为队列不为空，或者停止标记打上
                cv.wait(ul, [this](){return stop.load() || tasks.size() > 0;});   // !tasks.empty()

                // 再次判断是否退出
                if (stop.load()) return;

                // 从队列中取出任务   -- 注意移动语句
                t = tasks.front();  // t = std::move(tasks.front());

                tasks.pop();
            }
            
            //cout << "线程：" << this_thread::get_id() << "正在运行任务" << endl; 

            // 运行任务
            t();
        }
    }

    vector<thread> threads;     // 保存线程的容器
    queue<Task> tasks;          // 保存任务的容器
    atomic<bool> stop;          // 停止标志
    condition_variable cv;      // 任务唤醒标志
    mutex mtx;                  // 保证任务互斥
    int threadNum;              // 线程数量 
};



void TestThreadPoll()
{
    int testTaskInt = 0;
    
    ThreadPool pool(5);
    this_thread::sleep_for(chrono::milliseconds(10));

    pool.PushTask([testTaskInt](){cout << "thred: " << this_thread::get_id() << ", task running " << testTaskInt << endl;});  testTaskInt++;
    pool.PushTask([testTaskInt](){cout << "thred: " << this_thread::get_id() << ", task running " << testTaskInt << endl;});  testTaskInt++;
    pool.PushTask([testTaskInt](){cout << "thred: " << this_thread::get_id() << ", task running " << testTaskInt << endl;});  testTaskInt++;
    pool.PushTask([testTaskInt](){cout << "thred: " << this_thread::get_id() << ", task running " << testTaskInt << endl;});  testTaskInt++;
    pool.PushTask([testTaskInt](){cout << "thred: " << this_thread::get_id() << ", task running " << testTaskInt << endl;});  testTaskInt++;
    pool.PushTask([testTaskInt](){cout << "thred: " << this_thread::get_id() << ", task running " << testTaskInt << endl;});  testTaskInt++;
    pool.PushTask([testTaskInt](){cout << "thred: " << this_thread::get_id() << ", task running " << testTaskInt << endl;});  testTaskInt++;

    this_thread::sleep_for(chrono::seconds(2));
    return;
}


class ThreadPoll2 {
public:
    ThreadPoll2(int min, int max) : min(min), max(max), stop_all(false) {
        stop_flags.reserve(max);
        for (int i = 0; i < min; i++) {
            threads.emplace_back(thread(&ThreadPoll2::worker, this, i));
            stop_flags.emplace_back(make_unique<atomic<bool>>(false));
        }
    }
    
    ~ThreadPoll2() {
        stop_all = true;
        cv.notify_all();
        for (auto &t : threads) {
            if (t.joinable()) {
                t.join();
            }
        }
    }

    void AddTask(Task t) {
        {
            lock_guard<mutex> lg(mtx);
            tasks.emplace(t);
        }
        cv.notify_one();
    }

    void AdjustThreadNum(int num) {
        if (num == stop_flags.size()) return;
        if (num < min || num > max) {
            cout << "设置值不合法:" << num << ", min = " << min << ", max = " << max << endl;
            return ;
        }
        
        if (num < stop_flags.size()) {
            // 缩小
            for (int i = num; i < stop_flags.size(); i++) {
                stop_flags[i] = make_unique<atomic<bool>>(true);
            }
            cv.notify_all();                // 唤醒所有以便线程退出
            for (int i = num; i < stop_flags.size(); i++) {
                if (threads[i].joinable()) {
                    threads[i].join();      // 等待多余线程退出
                }
            }
            stop_flags.resize(num);         // 调整标记位
            threads.resize(num);            // 调整线程数量
        } else {
            // 扩大
            for (int i = stop_flags.size(); i < num; i++) {
                threads.emplace_back(thread(&ThreadPoll2::worker, this, i));
                stop_flags.emplace_back(make_unique<atomic<bool>>(false));
            }
        }
    }


    template<class FUNC, class... Args>
    auto AddTask(FUNC&& func, Args&&... args) -> std::future<typename std::result_of<FUNC(Args...)>::type> 
    {
        // 声明返回类型
        using return_type = typename std::result_of<FUNC(Args...)>::type;

        // 包装异步任务，返回future对象
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<FUNC>(func), std::forward<Args>(args)...)
        );
        std::future<return_type> res = task->get_future();

        // 包装为lambda，在无参数无返回值的lambda中执行原本任务
        {
            std::unique_lock<std::mutex> lock(mtx);
            if (stop_all) throw std::runtime_error("add on stopped pool");
            tasks.emplace([task]() { (*task)(); }); 
        }
        cv.notify_one();
        return res;
    }
/*
    template<typename F, typename... Args>
    auto AddTask2(F&& f, Args&&... args) 
        -> std::future<std::invoke_result_t<F, Args...>> 
    {
        // invoke_result_t代替result_of
        using return_type = std::invoke_result_t<F, Args...>;
        
        // 使用 C++14 泛型 Lambda + 完美转发捕获参数
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            [func = std::forward<F>(f), ...args = std::forward<Args>(args)]() mutable 
            { return std::invoke(func, std::forward<Args>(args)...); }
        );

        std::future<return_type> res = task->get_future();
        {
            std::unique_lock lock(mtx);  
            if (stop_all) throw std::runtime_error("add on stopped pool");
            tasks.emplace([task]() { (*task)(); });
        }
        cv.notify_one();
        return res;
    }
*/


private:
    void worker(int index) {
        cout << "线程:" << index << "正在启动" << endl;
        while (!stop_all && !(*stop_flags[index])) {
            Task t;
            {
                unique_lock<mutex> ul(mtx);
                cv.wait(ul, [this, index](){return !tasks.empty() || stop_all || (*stop_flags[index]);});  // 不为空，或者有停止标记
                if (stop_all || (*stop_flags[index])) {
                    cout << "线程:" << index << "正在销毁" << endl;
                    return;
                }
                t = move(tasks.front());
                tasks.pop();
            }
            t();
        }
    }

    vector<thread> threads;
    queue<Task> tasks;
    atomic<bool> stop_all;
    vector<unique_ptr<atomic<bool>>> stop_flags;  // 使用unique包装atomic，因为atomic不能移动和拷贝
    mutex mtx;
    condition_variable cv;
    int min;
    int max;
};

void TestThreadPoll2()
{
    ThreadPoll2 pool(3,6);
    this_thread::sleep_for(chrono::milliseconds(10));
    for (int i = 0; i < 6; i++) {
        pool.AddTask([i](){cout << "task running " << i << endl;});
    }
    this_thread::sleep_for(chrono::milliseconds(10));
    
    pool.AdjustThreadNum(5);
    this_thread::sleep_for(chrono::milliseconds(10));
    for (int i = 0; i < 6; i++) {
        pool.AddTask([i](){cout << "task running " << i << endl;});
    }
    this_thread::sleep_for(chrono::milliseconds(10));

    pool.AdjustThreadNum(3);
    this_thread::sleep_for(chrono::milliseconds(10));
    for (int i = 0; i < 6; i++) {
        pool.AddTask([i](){cout << "task running " << i << endl;});
    }
    this_thread::sleep_for(chrono::milliseconds(10));


    auto res = pool.AddTask([](int a, int b){return a + b;}, 100, 200);
    cout << res.get() << endl;
}