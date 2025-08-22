
# 组包
a = 1,2,3,4
print(a)  # (1, 2, 3, 4)
print(type(a))  # <class 'tuple'>

# 拆包
a1,a2,a3,a4= a  # 相当于遍历a中的元素，赋值给每个变量
print(a1,a2,a3,a4)  # 1 2 3 4