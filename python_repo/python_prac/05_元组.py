
t1 = ()
print(type(t1))     # <class 'tuple'>

t2 = (1, 2, 'a', "abc", 4.4)
print(t2)   # (1, 2, 'a', 'abc', 4.4)

# 元组嵌套
t3 = (4, 3, 'ad', t2)
print(t3)   # (4, 3, 'ad', (1, 2, 'a', 'abc', 4.4))

# 一个元素的元组
t4 = (1, )
print(type(t4)) # <class 'tuple'>

# 初始化一个元组（可迭代的参数）
t5 = tuple('hello') # ('h', 'e', 'l', 'l', 'o')
print(t5)


# 访问
print(t2[0])
print(t2[3])


# 遍历
for i in t2:
    print(i, end=' ')
print()

for i in range(len(t2)):
    print(t2[i], end=' ')
print()

for i in t3:
    if isinstance(i, tuple):
        for j in i:
            print(j, end=' ')
    else:
        print(i, end=' ')
print()


# 常用方法
print(t2.count(2))
print(t2.index(1))


t = ('a', 'b', ['A', 'B'])  # tuple中包含一个list，这个list可以修改
t[2][0] = 2                 # 内部list可修改
t[2].append(33);            # 同样内部list可修改
print(t)    # ('a', 'b', [2, 'B', 33]) 


t = ('a', 'b', ['A', 'B'])
print(t[1:]) # ('b', ['A', 'B'])