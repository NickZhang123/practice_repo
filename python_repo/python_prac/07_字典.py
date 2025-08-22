
# 1. 定义
d1 = {}
print(type(d1)) # <class 'dict'>

d1 = {'k1':'v1', 'k2':'v2'}
print(d1)

# 2. 访问
# 字典也是通过下标方式来访问元素，但是字典中没有索引，
# 也就是没有下标编号，字典通过下标的中括号中书写key的方式来直接访问key所对应的值
print(d1.keys())    # dict_keys(['k1', 'k2'])
print(d1['k1'])     # v1

#print(d1['k'])     # 下标方式在访问数据时，如果key不存在，会报错
print(d1.get('k'))  # None, get方法方式 访问数据时，如果key不存在，返回None

# 3. 修改value
d1['k1'] = 'vvvv1'
print(d1)   # {'k1': 'vvvv1', 'k2': 'v2'}


# 4. 遍历
for i in d1:  # 将所有的key遍历出来
    print(i, d1[i], end=' ')  # k1 vvvv1 k2 v2
print()
    
for i in d1.keys():  # 将所有的key遍历出来
    print(i, d1[i], end=' ')  # k1 vvvv1 k2 v2
print()

for i in d1.values():  # 将所有的value遍历出来
    print(i, end=' ')  # vvvv1 v2
print()

for i in d1.items():  # 将所有的tuple(k,v)
    print(type(i), end=' ') # <class 'tuple'>
    print(i[0], i[1], end=' ')  # k-v
print()

for k,v in d1.items():      # 使用k,v变量去接tuple(k,v)中的元素（解包）
    print(k, v, end=' ')    # k-v
print()

# 解包
item = (1,2,3,4,5)
a,b,c,d,e = item
print(a,b,c,d,e, item)  # 1 2 3 4 5 (1, 2, 3, 4, 5)

# 5. 增删改查
# 5.1 增, 直接使用d[k]=v的格式加入数据
# 5.2 改，使用d[k]=v格式修改，和增格式相同，即如果已经存在相同k则修改，否则添加
# 5.3 删，popitem()删除最后一个kv，
#        pop(key)删除指定key， 
#        del(d['k'])删除字典中的某个key,  del(d)删除整个字典


if 'k1' in d1:
    print(d1['k1'])

d1['k3'] = 'vvv3'
print(d1.setdefault('k3', 'vvvv4')) # vvv3. 存在，返回已存在的值
print(d1.setdefault('k4', 'vvvv4')) # vvvv4. 不存在，存入，并返回存入值的value

