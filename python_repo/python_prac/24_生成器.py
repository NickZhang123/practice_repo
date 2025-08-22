

ge = (i for i in range(5))
print(type(ge)) # <class 'generator'>
print(ge)   # <generator object <genexpr> at 0x000001BF7344DDD0>

print(next(ge)) # 0
print(next(ge)) # 1
print(next(ge)) # 2

for i in ge:
    print(i, end=' ')   # 3 4
print()


# yield生成器
def get_val(n):
    for i in range(1, n):
        yield i

c = get_val(5)
print(next(c))  # 1
print(next(c))  # 2
print(next(c))  # 3
