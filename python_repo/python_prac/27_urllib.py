import urllib.parse
import urllib.request
import json

# 1. quote&unqoute
str = 'www.baidu.cn/特殊字符/abc.html'
res = urllib.parse.quote(str)
print(res)  # www.baidu.cn/%E7%89%B9%E6%AE%8A%E5%AD%97%E7%AC%A6/abc.html

res2 = urllib.parse.unquote(res)
print(res2) # www.baidu.cn/特殊字符/abc.html
print('*' * 20)

# 2. urlencode
params = {
    'para1' : 'value1',
    'para2' : 'value2',
    'para3' : '值3',
}
res = urllib.parse.urlencode(params)
print(res)                          # para1=value1&para2=value2&para3=%E5%80%BC3
print(urllib.parse.unquote(res))    # para1=value1&para2=value2&para3=值3
print('*' * 20)

# 3. urlopen

## 3.1 Get方法
url = 'http://www.baidu.com/'           # 最后要加/表示根目录
res = urllib.request.urlopen(url)
print(type(res))                        # <class 'http.client.HTTPResponse'>
content = res.read().decode('utf-8')    # read()读取全部内容，默认是二进制，解码为utf-8
#print(content)
print('*' * 20)

## 3.2 Get带参数
url = 'http://www.baidu.com/s?'
key_word = 'python'
data_form = {
    'ie':'utf-8',
    'wd': key_word
}
data_form = urllib.parse.urlencode(data_form)   # 转换字典格式、转换百分号格式
url += data_form                                # 拼接url param
res = urllib.request.urlopen(url)

#with open('test.html', 'wb') as f:
#    f.write(res.read())
# with open("test2.html", 'w', encoding='utf-8') as f :     # 解码后保存
#   f.write(res.read().decode())

print('*' * 20)

## 3.3 Post
url = 'https://fanyi.baidu.com/sug'
data = {
    'kw':'baby',
}
data = urllib.parse.urlencode(data).encode()        # urlencode转换格式，encode编码为字节
res = urllib.request.urlopen(url=url, data=data)    # post获取
print(res.read().decode())

print('*' * 20)

# 3. Request的Post
url = 'https://fanyi.baidu.com/sug'
data = {
    'kw':'baby',
}
headers = {
    "User-Agent" : "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/126.0.0.0 Safari/537.36 Edg/126.0.0.0",
    "accept-language" : "zh-CN",
}

data = urllib.parse.urlencode(data).encode()        # urlencode转换格式，encode编码为字节
req = urllib.request.Request(url, headers=headers)  # Request对象封装url、headers
res = urllib.request.urlopen(req, data=data)
#with open('test.html', 'w', encoding='utf-8') as f:
#    f.write(res.read().decode())

# 返回的数据是json格式，其中部分为Unicode转义字符，使用python中的json对象处理中文
jsonobj = json.loads(res.read().decode())

# ensure_ascii 参数决定了输出的 JSON 字符串中非 ASCII 字符的处理方式
#   True 时（这是默认设置），所有非ASCII字符都会被转义为其Unicode码点
#   False 时，非ASCII字符会直接输出，不进行转义。例如，中文字符会以原样输出
# indent指定缩进级别，同时美化输出
print(json.dumps(jsonobj, ensure_ascii=False, indent=2))

