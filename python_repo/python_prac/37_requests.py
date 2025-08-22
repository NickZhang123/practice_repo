import requests
import json

'''
# 不带参数的get
url = 'http://www.baidu.com'
res = requests.get(url)
print(res)

# 带参数的get
url = 'http://www.baidu.com'
params = {
    'key1': 'value1', 
    'key2': 'value2'
}

# 文本响应
res = requests.get(url=url, params=params)
print(res)
print(res.text)         # 读取服务器响应的内容(自动解码来自服务器的内容。大多数unicode字符集都能被无缝地解码)
print(res.encoding)     # 打印encoding
res.encoding = 'utf-8'  # 设置encoding
print(res.text)         # 改变了编码，使用新的编码
print('*' * 20)

# 二进制响应
print(res.content)      # 二进制响应内容（非文本内容如图片时处理）
print('*' * 20)


# json响应
r = requests.get('https://api.github.com/events')
json.dump(r.json(), open('test.json', 'w', encoding='utf-8'))
print('*' * 20)
'''

url = 'https://fanyi.baidu.com/sug'
headers = {
    "User-Agent" : "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/126.0.0.0 Safari/537.36 Edg/126.0.0.0",
}
form_data = {
    'kw':'baby',
}

res = requests.post(url=url, headers=headers, data=form_data)
#print(type(res))    # <class 'requests.models.Response'>
#print(res.json())
#print(res.text)
print(res.content)