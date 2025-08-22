
import threading
import time

l1 = []

# 线程任务1
def task1():
    print("task1")
    for i in range(5):
        print(f"task1:{i}")

# 线程任务2
def task2():
    print("task2")
    t = threading.current_thread()  # 获取当前线程对象
    print(f"task2 thread, {t}") # task2 thread, <Thread(tttt, started 21960)> 线程名，状态，线程tid
    for i in range(5):
        print(f"task2:{i}")

# 线程带参数任务 args，kwargs
def task3(name, count):
    for i in range(count):
        print(f"{name} - {i}")

# 守护线程
def task4():
    print("task4 --- start")
    time.sleep(5)
    print("task4 --- end")

# 多线程共享全局变量
def task5(input_str):
    for i in range(10):
        l1.append(f"{input_str}, {i}")  # 多个线程存在竞争关系
        time.sleep(0.2)

cnt = 0     # 全局变量
mutex = threading.Lock() # 创建一个锁对象

# 多线程竞争关系
def task6():
    global cnt
    for i in range(10000000):
        mutex.acquire()  # 加锁
        cnt += 1
        mutex.release()  # 解锁
    print(f"{threading.current_thread()},{cnt}")

lock1= threading.Lock()
lock2 = threading.Lock()
# 死锁，哲学家吃饭
def person1_eat():
    for i in range(100):    # 各吃一百口饭，检测碰撞
        lock1.acquire()
        print("person1获得第一根筷子, 等待获取第二根筷子")
        lock2.acquire()
        print("person1获得第二根筷子，可以吃饭")
        lock2.release()
        print("person1吃完了，放下了第二根筷子")
        lock1.release()
        print("person1吃完了，放下了第一根筷子")

def person2_eat():
    for i in range(100):    # 各吃一百口饭，检测碰撞
        lock2.acquire()
        print("person2获得第二根筷子, 等待获取第一根筷子")
        lock1.acquire()
        print("person2获得第一个筷子，可以吃饭")
        lock1.release()
        print("person2吃完了，放下了第一根筷子")
        lock2.release()
        print("person2吃完了，放下了第二根筷子")



if __name__ == '__main__':
    t1 = threading.Thread(group=None, target=task1)
    t2 = threading.Thread(group=None, target=task2, name="tttt")

    print(t1)   # <Thread(Thread-1 (task1), initial)>  线程名，线程状态
    print(t2)   # <Thread(tttt, initial)>   线程名，线程状态

    t1.start()
    t2.start()

    print(t2)   # <Thread(tttt, started 21960)> 线程名，状态，线程tid
    
    # 带参数的线程
    t3 = threading.Thread(target=task3, args=('AAA', 4))
    t4 = threading.Thread(target=task3, kwargs={'name':'BBB', 'count':4})
    t3.start()
    t4.start()

    # 子线程设置为守护，主线程结束后自动结束子进程
    t5 = threading.Thread(target=task4, daemon=True)
    t5.start()

    t6 = threading.Thread(target=task4)
    t6.daemon = True
    t6.start()

    # 测试多线程共享全局变量
    t7 = threading.Thread(target=task5, args=("T1", ))
    t8 = threading.Thread(target=task5, args=("T2", ))
    t7.start()
    t8.start()
    t7.join()
    t8.join() # 等待T7/T8完成
    print(l1)   # ['T1, 0', 'T2, 0', 'T1, 1', 'T2, 1', 'T1, 2', 'T2, 2', 
                # 'T1, 3', 'T2, 3', 'T1, 4', 'T2, 4', 'T1, 5', 'T2, 5', 'T1, 6',
                # 'T2, 6', 'T1, 7', 'T2, 7', 'T1, 8', 'T2, 8', 'T1, 9', 'T2, 9']

    # 多线程竞争访问(取cnt，执行加一操作，两个线程没有互斥)
    t9 = threading.Thread(target=task6, name="xx")
    t10 = threading.Thread(target=task6, name="yy")
    t9.start()
    t10.start()
    time.sleep(2)
    print(f"cnt={cnt}")

    # 死锁问题
    t11 = threading.Thread(target=person1_eat)
    t12 = threading.Thread(target=person2_eat)
    t11.start()
    t12.start()

    print("main end")
    