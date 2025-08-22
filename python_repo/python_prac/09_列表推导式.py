

# 列表推导式
l1 = [ x for x in range(10)]
print(l1)

# 带条件的列表推导式
l2 = [x for x in range(10) if x % 3 == 0]
print(l2)

# 嵌套推导，相当于两层for循环
l3 = [(x,y) for x in range(5) for y in range(3)]
print(l3)