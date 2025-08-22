
import multiprocessing
import os
import time

li = []

# 进程1任务
def task1():
    for i in range(10):
        print(f"A--{i}")
    print(f"pid = {os.getpid()}, ppid = {os.getppid()}")

    print(f"task1_id:{id(li)}")     # 1685007297536
    li.append(1)
    print(f"task1_id:{id(li)}")     # 1685007297536

# 进程2任务
def task2():
    for i in range(10):
        print(f"B--{i}")
    print(f"pid = {os.getpid()}, ppid = {os.getppid()}")

    print(f"task2_id:{id(li)}")     # 2349998205952
    time.sleep(0.5)

    # <Process name='test' parent=17996 started>
    print(multiprocessing.current_process())     

# 带参数的进程
def task3(str, count):
    for i in range(count):
        print(f"C--{str}--{i}")

def taskend():
    print(f"taskend_pid:{os.getpid()}. ppid={os.getppid()}")
    time.sleep(10)
    print("taskend")

if __name__ == '__main__':
    
    print(f"pid = {os.getpid()}")   # 父进程pid
    print(f"main——id:{id(li)}")     # 1626058838400

    # 获取当前进程名， <_MainProcess name='MainProcess' parent=None started>
    print(multiprocessing.current_process())    

    p1 = multiprocessing.Process(target=task1)  # 创建进程，指定任务
    p2 = multiprocessing.Process(target=task2, name='test') # 指定进程名
    p3 = multiprocessing.Process(target=task3, args=("task3",5))   # args元组传参
    p4 = multiprocessing.Process(target=task3, kwargs={'str':'tt2', 'count' : 5 }) #kwargs字典传参

    p3.start()
    p3.join()   # 等待p3完成后再执行
    
    p1.start()  # 进程启动
    p2.start()
    p4.start()

    # 测试主进程会等待子进程完成后才结束
    p5 = multiprocessing.Process(target=taskend, name = "test22")
    p5.start()