from collections import deque

# 1. 创建一个双端队列
# d = deque()
d = deque([1, 2])      # 从列表初始化双端队列

# 2. append
d.append(6)
print(d)            # deque([1, 2, 6])
d.appendleft(7)
print(d)            # deque([7, 1, 2, 6])

# 3. pop
print(d.pop(), d)       # 6 deque([7, 1, 2])
print(d.popleft(), d)   # 7 deque([1, 2])
print(d.pop(), d)       # 2 deque([1])
print(d.pop(), d)       # 1 deque([])
# 队列空，再次pop则抛异常
# d.pop()         # IndexError