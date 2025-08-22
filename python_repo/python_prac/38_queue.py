from queue import Queue

# 1. 创建一个队列，并指定大小；若未指定，则队列大小没有限制
q = Queue(maxsize=3)   

# 2. 添加数据
q.put('y')
q.put('x')
q.put(3)

print(q.qsize(), q.full(), q.empty())   # 3, True, False

# 默认队列满的时候，添加数据会阻塞
# q.put(4)                              # 阻塞
# q.put(5, False)                       # 不阻塞，直接报错
# q.put(4, True, timeout=2)             # 阻塞，超时后报异常

# 3. 获取数据
print(q.get())  # y
print(q.get())  # x
print(q.get())  # 3

print(q.qsize(), q.full(), q.empty())   # 0, False, True

# 默认获取数据，队列空阻塞
# q.get()                   # 阻塞
# q.get(False)              # 不阻塞，直接报错
# q.get(True, timeout=2)    # 阻塞，等待超时后报错



