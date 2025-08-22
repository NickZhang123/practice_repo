
'''
 利用闭包实现:
 装饰器特点：
    1. 不修改已有函数的源代码
    2. 不修改已有函数调用方式
    3. 给已有函数增加一个额外功能
'''
import time

###################################################################
def show():
    n = 0
    for i in range(1000000):
        n += i
    print("show -", n)

# 1.不修改原有代码
def count_time(func):
    def inner():
        start = time.time()
        func()
        end = time.time()
        print(f"共耗时{end-start}秒")
    return inner

# 3.装饰器原理，给原函数增加一个功能，返回的函数赋值给原函数
show = count_time(show)

# 2.不修改原函数调用方式
show()
    
###################################################################

# 1. 定义闭包
def count_time(func):
    def inner():
        start = time.time()
        func()
        end = time.time()
        print(f"共耗时{end-start}秒")
    return inner

# 2. 定义装饰器
@count_time     # ==>>  display = count_time(display)
def display():
    print("display")

@count_time     # ==>>  show2 = count_time(show2)  
def show2():
    print("show2")

# 3. 使用
display()
show2()


###################################################################
# 多个装饰器
def wrapper1(func):
    def inner(*args, **kwargs):
        return '<div>' + func(*args, **kwargs) + '</div>'
    return inner

def wrapper2(func):
    def inner(*args, **kwargs):
        return '<p>' + func(*args, **kwargs) + '</p>'
    return inner

@wrapper2
@wrapper1
def show():
    return "test line"

print(show())   # <p><div>test line</div></p>

###################################################################
# 类装饰器
class Wrapper3(object):
    def __init__(self, func):
       self.func = func

    def __call__(self, *args, **kwargs):  # 使得类对象可调用
        print("加料", end=' ')
        self.func(*args, **kwargs)

@Wrapper3  #  show = Wrapper3(show)
def show(msg):
    print("show ", msg)

show("heihei")  # 加料 show  heihei