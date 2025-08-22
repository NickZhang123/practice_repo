
# 单行注释

''' 
    多行注释
'''

import pprint
import copy

# 字符串， 注意和多行注释的格式
strrr = '''fdfafdaf'''
print(strrr)
a = 1
b = 2
a, b = b, a+b  
print(a, b) # 2， 3 

# 打包解包
a, b, *rest = [1, 2, 3, 4]  # 可变参数rest，带星号，推到为列表
print(rest) # [3, 4]  带星号的变量最终包含的总是一个列表

a, b, *rest = (1, 2, 3, 4)  # 可变参数rest，带星号，推到为列表
print(rest)


# 列表推导式
l3 = [(x,y) for x in range(5) for y in range(3)]
print(l3)

li = [x * 3 for x in range(2, 20) if x > 10]
print(reversed(li))
for i in li:
    print(i, end=' ') # 33 36 39 42 45 48 51 54 57
# 或者
print(list(reversed(li)))  			# [57, 54, 51, 48, 45, 42, 39, 36, 33]

print(r'===================')

# 对齐打印
print("{:<10}, {:>15.10f}".format(123, 19.23213))    # 123       ,           19.23
str = '{:<10}, {:>15.10f}'
print(str.format(123, 19.23213))          # 123       ,   19.2321300000
print(str.format(12234234, 14324143.13))  # 12234234  , 14324143.1300000008

# 居中显示
str = 'test'
print(str.center(15))       #       test     ，居中显示，使用空白填充
print(str.center(15, "*"))  # ******test*****

# 转换
table = str.maketrans('cs', 'kz')  # 表示将c装换为k、将s转换为z， table内容为{115: 122, 99: 107}
print('this is an incredible test'.translate(table)) # 'thiz iz an inkredible tezt'

#  maketrans还可提供可选的第三个参数，指定要将哪些字母删除
table = str.maketrans('cs', 'kz', ' ')	# 删除空格
print('this is an incredible test'.translate(table))  # 'thizizaninkredibletezt'

# 取地址
str = 'avaf'
strb = str
print(id(str), id(strb))    # 同一个地址，不可变对象

# in
s = 'hello world'
print('hell' in s)      # True
print('hellx' in s)     # False
print('hellx' not in s) # True

print('s' is 's')       # True
print('ss' is 's')      # False
print('ss' is not 's')  # True

# 浅拷贝
l1 = [1,2,3]
l2 = copy.copy(l1)
print(id(l1), id(l2))   # 浅拷贝，地址值不一样
print(l1 is l2)         # False

print("*" * 20)

# 类型
a = 1
b = '1'
print(f"type(a)={type(a)}, type(b)={type(b)}")

# 输出 
print("这是一个值%d"  %  2)
print("值一%d, 值二%d" %  (2, 3))

# 格式化输出
name = 'zhangsan'
age = '100'
print(f"name:{name}, age:{age}")  # 类似shell

print('%d' % 1)
print('%5d' % 1)
print('%05d' % 1)
print('%-5d' % 1)
print('%3d' % 12345)
print('%.3f' % 1)

'''
# 输入
a = input("input a num: ")
print(a, type(a))

b = int(input("input a num: "))
print(b, type(b))   # <class 'str'>
'''

# sep结合输出
print("I", "wish", "to", sep="_") # I_wish_to 带分隔符打印


# 美化输出
data = {
    'name': 'John Doe',
    'age': 30,
    'address': {
        'street': '123 Main St',
        'city': 'Anytown',
        'state': 'CA'
    },
    'phones': ['555-1234', '555-5678']
}

pprint.pprint(data)

# random模块
from random import choice
va = choice(['Hello, world!', [1, 2, 'e', 'e', 4], 'a', 'b'])  # 从列表中随机选择一个数
print("****************", va)