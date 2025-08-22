
# 1. 定义

# 定义空列表
l1 = []
print(type(l1))     # <class 'list'>

# 定义一个元素
l2 = [1,]    
print(type(l2))     # <class 'list'>

# 定义多个元素
l3 = [1, 2, 'a', (3, 4, 'fd'), [5, 0, 'asss']]
print(l3)   # [1, 2, 'a', (3, 4, 'fd'), [5, 0, 'asss']]

# 使用list创建
l4 = list("abcdefg")
print(l4)   # ['a', 'b', 'c', 'd', 'e', 'f', 'g']


# 2. 访问
print(l3[0])    # 1
print(l3[3])    # (3, 4, 'fd')

# 3. 遍历  
for i in l3:
    if isinstance(i, tuple) or isinstance(i, list):
        for j in i:
            print(j, end=' ')
    else:
        print(i, end=' ')       
print()
    # 1 2 a 3 4 fd 5 0 asss


# 4. 修改
l3[0] = 'aaaaaaaaaaa'
print(l3) # ['aaaaaaaaaaa', 2, 'a', (3, 4, 'fd'), [5, 0, 'asss']]


# 5. 排序和逆序(会修改列表本身，函数没有返回值)
l4[2] = 'j'
l4.sort()   # 函数没有返回值
print(l4)   # ['a', 'b', 'd', 'e', 'f', 'g', 'j']

l4.sort(reverse=True)   # 函数没有返回值
print(l4)   # ['j', 'g', 'f', 'e', 'd', 'b', 'a']

l4.reverse()
print(l4)   # ['a', 'b', 'd', 'e', 'f', 'g', 'j']



# 6. 常用方法
# 6.1 增加：append，extend，insert
l5 = []
l5.append(2)
l5.append('a')
l5.append('ddd')
l5.append(l4)
print(l5) # [2, 'a', 'ddd', ['a', 'b', 'd', 'e', 'f', 'g', 'j']]

l6 = [1,2,('a','n'),[3,'d']]
l7 = [3,4]
l7.extend(l6)  # 将l6中的元素一一加入l7
print(l7) # [3, 4, 1, 2, ('a', 'n'), [3, 'd']]

l7.insert(1, 111) # 在下标为1的位置插入数据
print(l7) # [3, 111, 4, 1, 2, ('a', 'n'), [3, 'd']]

l7.insert(30, 111) # 指定位置超过列表最大个数，则为追加
print(l7) # [3, 111, 4, 1, 2, ('a', 'n'), [3, 'd'], 111]

# 6.2 查找：index, count, in, not in
l8 = [1,2,3,4,5,6,6,62,3]

# count()
print(l8.count(6))  # 2
print(l8.count(66)) # 0

# index()
print(l8.index(6))  # 5
print(l8.index(2))  # 1
# print(l.index(22))  # ValueError: 22 is not in list

# in - not in
print(2 in l8)      # True
print(22 in l8)     # False

print(2 not in l8)  # False
print(22 not in l8) # True

# 6.3 删除:
# list.pop默认删除最后，也可指定index, 
# list.remove, 删除指定对象，当有多个相同对象时，只删除 第一个
# list.clear清空列表但列表还在, 
# del(list)清空并删除列表, del(list[0]) 删除指定元素
print(l8)       # [1, 2, 3, 4, 5, 6, 6, 62, 3]
print(l8.pop()) # 3, 函数返回删除的元素
print(l8)       # [1, 2, 3, 4, 5, 6, 6, 62]
l8.pop(3)       # 指定inde先删除
print(l8)       # [1, 2, 3, 5, 6, 6, 62]

l8.remove(2)   
print(l8)       # [1, 3, 5, 6, 6, 62]

del(l8[0])  
print(l8)       # [3, 5, 6, 6, 62]

l8.clear()
print(l8)       # []

del(l8)

# 迭代过程中不要删除元素（和c++迭代器失效一个原理）
cl = [5, 3, 8,91]
for o in cl:
    cl.remove(o)
print(cl)   # [3, 91]  删除不完全，直接使用clear或者del
