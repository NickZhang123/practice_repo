
import random

def func():
    '''
        函数说明
    '''
    print("test")


# 函数返回多个值（默认tuple打包）
def get_min_max():
    l1 = [0,3,53424,43,24,23,423,23,42]
    l1.sort()
    return l1[0], l1[len(l1)-1]

print(get_min_max())
min, max = get_min_max()
print(min, max) 


# 使用全局变量
count = 0
l1=[]
def test1():
    global count        # 需要声明
    count +=3
    l1.append(2323)     # 无需声明，直接使用

test1()
print(count, l1)

# 全局变量
parameter = 'berry'
def combine():
    global parameter    # 引用全局变量
    parameter = 'test'
combine()  
print(parameter) # 'test'

# 参数默认值
def show(a=0,b=0):
    print(f'a:{a},b:{b}')
    print(a + b)

show()
show(1)
show(1,2)

# 关键字参数
def show2(n,s):
	print(n,s)
show2(s='xxx',n=1)  # 关键字指定参数赋值

# 不定长位置参数
def my_sum(*args):  # 组包
    print(args)         # (1, 2, '1')
    print(type(args))   # <class 'tuple'>
    print(*args)        # 1 2 1
my_sum(1,2,'1')

# 不定长关键字
def show3(**kwargs):
    print(kwargs)   # 字典类型
show3(a=1)          # {'a': 1}
show3(a=1,b=2)      # {'a': 1, 'b': 2}
show3(a=1,b=2,c=3)  # {'a': 1, 'b': 2, 'c': 3}


# 任意个数参数
def display(*args,**kwargs):
    print(f'args:{args}', end=' ')
    print(f'kwargs:{kwargs}')
display()                   # args:() kwargs:{}
display(1,2,3)              # args:(1, 2, 3) kwargs:{}
display(a=1,b=2)            # args:() kwargs:{'a': 1, 'b': 2}
display(1,2,3,4,a=1,b=2)    # args:(1, 2, 3, 4) kwargs:{'a': 1, 'b': 2}

# lambda
func2 = lambda x : print(x*x)
func2(3)        # 9

func3 = lambda x : x*x
print(func3(33))

# 三目运算
func4 = lambda m, n: m if m > n else n
print(func4(11, 2))

# 定义一个可以接收任何参数的函数
def display(*args,**kwargs):
    print(f'args:{args}', end=' ')
    print(f'kwargs:{kwargs}') 
display()                   # args:() kwargs:{}
display(1,2,3)              # args:(1, 2, 3) kwargs:{}
display(a=1,b=2)            # args:() kwargs:{'a': 1, 'b': 2}
display(1,2,3,4,a=1,b=2)    # args:(1, 2, 3, 4) kwargs:{'a': 1, 'b': 2}

# 函数帮助文档
def square(x):
    'Calculates the square of the number x.'
    return x * x

print(square.__doc__)  # 'Calculates the square of the number x.'
help(square)

# 函数参数传递
def person(name, age, **kw): # 注意kw获得的dict是extra的一份拷贝
    kw[0] = 'a' 
    print('name:', name, 'age:', age, 'other:', kw)

extra = {'city': 'Beijing', 'job': 'Engineer'}
# name: Jack age: 24 other: {'city': 'Beijing', 'job': 'Engineer', 0: 'a'}
person('Jack', 24, **extra)  
person('Jack', 24, **extra)  
print(extra)  # 不影响原始字典 {'city': 'Beijing', 'job': 'Engineer'}

# 函数命名关键字参数
def person(name, age, *, city, job):  # 只接收city和job作为关键字参数
    print(name, age, city, job)
    return
person(name = 'Jack', age = 24, city='Beijing', job='Engineer') # Jack 24 Beijing Engineer

# 轮子：判断文件格式是否是图片
def is_img(file_name):
    img_type = ('.bmp', '.dib', '.png', '.jpg', '.jpeg', '.pbm', '.pgm', '.ppm', 
                '.tif', '.tiff', '.png', '.img', '.gif', '.webp')
    if(file_name.lower().endswith(img_type)):
        print(file_name)
        return True
    
    print(f'"{file_name}"不是图片，请选择正确的图片格式')
    return False
print(is_img("fsfdafdsa.img"))
print(is_img("fsfdafdsa.i"))
