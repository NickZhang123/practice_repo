
a = 1
b = 2.2 
c = 'c'
d = "string"

# 格式化方式1(占位符, tuple解包)
s1 = "%s, %s, %s, %s" % (a, b, c, d)    # , 2.2, c, string
print(s1)

# 格式化方式2（类f_str，类shell）
s2 = f"{a}, {b}, {c}, {d}"  # , 2.2, c, string
print(s2)

# 格式化方式3（format，tuple解包）
s3 = "{}, {}, {}, {}".format(a,b,c,d)   # 1, 2.2, c, string
print(s3)

# {}中的编号对应后面format参数位置（带位置的format）
s3 = "{0}, {3}, {2}, {1}".format(a,b,c,d)   # 1, string, c, 2.2
print(s3)

# 分别指定输出格式(format带位置和格式)
s3 = "{0:05d}, {1:.4f}, {2}, {3}".format(a,b,c,d)  # 00001, 2.2000, c, string
print(s3)

# 多行字符串
str = '''str
dsf
fdaf
fa
'''
print(str)


# 切片
s = '0123456789'
print(s[2:4])
print(s[:4])
print(s[2:])
print(s[:6:2])
print(s[2:8:3])

print(s[8:2:-1])
print(s[8:2:-2])
print(s[::-1])

print(s[-1:-5:-1])


# patitioan，rpatition
str = "abc/bcd/efg.xxx"
print(str.partition("/"))  # ('abc', '/', 'bcd/efg.xxx')
print(str.rpartition("/"))  # ('abc/bcd', '/', 'efg.xxx')


# 查找
str = "hello world hello world"
print(str.find("wo", 7, 20))

# title
print(str.title())  # Hello World Hello World

# capitalize
print(str.capitalize()) # Hello world hello world

# strip
s = '    hello1     world1      '
print(s)    # hello1     world1

print('|' + s.strip() + '|')    # |hello1     world1|
print('|' + s.rstrip() + '|')   # |    hello1     world1|
print('|' + s.lstrip() + '|')   # |hello1     world1      |

# join
print(" ".join(s.split()))      # hello1 world1

# index/find/rfind/replace
print(str.index("wo"))
print(str.rfind("wo"))
print(str.replace('he', 'HE'))
print(str.replace('e', 'E', 1))

# count
print(str.count('he'))

# upper
print(str.upper())

# split,和join相反
print(str.split(" "))
print(str.split("ll"))
print(str.split(" ", 1))

ss = 'Hello\tWorld Hello \t\nWorld Hello\n Python'
print(ss)
print(ss.split(" "))

# partition
ss = 'HellohahaHelloHellohahaHello'
print(ss.partition('haha'))

print(str)
print(str.split())
print(str)

# join, 和split相反
print("-".join(str))

str = "ABC abc"
print("-".join(str))
print("-".join(str.split()))

print(str.lower())
print(str.title())
