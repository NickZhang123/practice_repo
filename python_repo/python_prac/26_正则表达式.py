
import re

res = re.match("ll", "llo")
print(res, type(res))   # <re.Match object; span=(0, 2), match='ll'> <class 're.Match'>
print(res.start(), res.end(), res.span())   # 0 2 (0, 2)

res = re.match("ll", "hello") 
print(res)  # None 只能从头匹配


# 匹配单个字符

res = re.match('.*:(\d+).*:(\d+)', 'xxx:2134, yyy:3424')
print(res.group())      # xxx:2134, yyy:3424
print(res.group(0))     # xxx:2134, yyy:3424
print(res.group(1))     # 2134
print(res.group(2))     # 3423

# 匹配<div>后，引用第一个分组即div组装</div>后续匹配
res = re.match('<([a-zA-Z]+)>(.*)</\\1>', '<div>abab</div>')
print(res)
res = re.match(r'<([a-zA-Z]+)>(.*)</\1>', '<div>abab</div>')  # 使用r'字符串'
print(res)
res = re.match(r'<([a-zA-Z]+)>(.*)</(\1)>', '<div>abab</div>')  # 使用r'字符串'
print(res)

# 分组别名，使用别名的地方要加括号
res = re.match(r'<(?P<alias_name>[a-zA-Z]+)>(.*)</(?P=alias_name)>', '<div>abab</div>')  
print(res)


res = re.search('\d+', 'xxx:2134, yyy:3424')
print(res)  # <re.Match object; span=(4, 8), match='2134'>

res = re.findall('\d+', 'xxx:2134, yyy:3424')
print(res)  # ['2134', '3424']

res = re.sub('\d+', "$$$", 'xxx:2134, yyy:3424')
print(res)  # xxx:$$$, yyy:$$$


# 用空格，逗号，点号分割字符串，点号需要转义
res = re.split(' |,|\.', 'hello world,python.java.c++')
print(res)  # ['hello', 'world', 'python', 'java', 'c++']

# 多行匹配

string2 = r''''<tt>
abc
dfa
dfa2
tewtwe
fda
gagd
<tt>
'''

res = re.findall('<tt>.*<tt>', string2)
print(res)  # []
res = re.findall('<tt>.*<tt>', string2, re.S)
print(res)  # ['<tt>\nabc\ndfa\ndfa2\ntewtwe\nfda\ngagd\n<tt>']

print(re.sub('love', 'hate', 'i love you , you love me , love'))    # i hate you , you hate me , hate

def func(match):
    print(match)                # <re.Match object; span=(2, 5), match='100'>
    ret = int(match.group())    # 取匹配内容转换为int
    ret += 1000                 # 修改匹配内容
    return str(ret)             # 返回修改后并转化为字符串的内容

ret = re.sub('\d+', func, r'距离100公里')
print(ret)                      # 距离1100公里