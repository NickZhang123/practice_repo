
import functools
# 函数式编程

# 1. map
l1 = [1,2,4,5,5,5,32]
print(l1)

def func(n):        # 只有一个参数
    return n*n
res = map(func, l1)
print(type(res))  # <class 'map'>
for i in res: 
    print(i, end=' ')   # 1 4 16 25 25 25 1024
print()

# lambda替换
print(*map(lambda x : x * x, l1))


# 2. reduce
l1 = [1,2,4,5,5,32]
def func2(x,y):
    return x+y  #  这里实现累加
res = functools.reduce(func2, l1)
print(type(res)) # <class 'int'>
print(res)       # 49

# lambda实现
print(functools.reduce(lambda x,y : x+y, l1))

l2 = [i for i in range(1,5)]
print(functools.reduce(lambda x,y : x*y, l2))


# 3. filter
my_list = ['123','234','abc','@#$','  ','abc234','132abc']

# 过滤出所有的数字字符串
res = filter(lambda s: s.isdigit(), my_list)
print(type(res)) # <class 'filter'>
for i in res:
    print(i)



my_list = [{'id': 1,'name': 'tom','age':12},{'id': 3,'name': 'rose','age':3},{'id': 2,'name': 'Jack','age':22}]
print(my_list)
my_list.sort(key = lambda x: x['id'])  # 按照id排序
print(my_list)
my_list.sort(key = lambda x: x['age'])  # 按照age升序
print(my_list)
my_list.sort(key = lambda x: x['age'], reverse=True)  # 按照age降序
print(my_list)