# 闭包格式
def outer():
    n = 1
    def inner():
        print(n)

    return inner

# 使用
ret = outer()
print(ret)  # <function outer.<locals>.inner at 0x0000013205777670>
ret()       # 1


# 例子
def person(name):
    def say(msg):
        print( name + " say " + msg)
    return say

pa = person("a")
pb = person("b")

pa("hello")         # a say hello
pb("hello world")   # b say hello world

# 例子
def outer2():
    n = 1
    def inner():
        nonlocal n  # 仅限不可变类型， 使用外部函数
        n += 10
        print(n)

    return inner

ret = outer2()
ret()       # 11