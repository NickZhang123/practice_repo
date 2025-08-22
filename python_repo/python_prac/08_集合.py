
s = set()       # s = {}表示定义一个空字典
print(type(s))  # <class 'set'>

s = {1,2,3,4,5,6,7,7,7}
print(s)    # {1, 2, 3, 4, 5, 6, 7}

for v in s:
    print(v, end = '')  # 1234567


# set-list-tuple三者类型间转换
s = 'hello'
l = list(s)
    
print(l)                # ['h', 'e', 'l', 'l', 'o']
print(tuple(l))         # ('h', 'e', 'l', 'l', 'o')
print(set(l))           # {'o', 'l', 'e', 'h'}
print(''.join(set(l)))  # oleh


s1 = {1,2,3}
s2 = {2,3,4}
print(s1 & s2)  # {2, 3}
print(s1 | s2)  # {1, 2, 3, 4}