
import os
'''
# 打开写
file = open("file1.txt", "w")
print(file) # <_io.TextIOWrapper name='file1.txt' mode='w' encoding='cp936'>

# 关闭
file.close()
'''

print(os.path.splitext('/foo/bar/baz.txt')) # ('/foo/bar/baz', '.txt')

file = open("file1.txt", 'rt')
#
# print(file.read())
print(file.readline())
print(file.readlines())
file.close()

# 改名
str = 'xxx.mp4'
print(str.rpartition('.'))

'''
# 按行读取文件
while True:
    res = file.readline()
    if res == "":
        break
    print(res)
'''

file.write

