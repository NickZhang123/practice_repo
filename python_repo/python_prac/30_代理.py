import urllib.request
import urllib.parse


url = 'https://www.kuaidaili.com/free/'

headers = {
    "User-Agent" : "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/126.0.0.0 Safari/537.36 Edg/126.0.0.0",
}

request = urllib.request.Request(url=url, headers=headers)
res = urllib.request.urlopen(request)
print(res.read().decode())



'''
# 创建handler（代理ip和端口port）
handler = urllib.request.ProxyHandler({'http':'ip:端口'})

# 创建opener
opener = urllib.request.build_opener(handler)

# 配置url、header，创建request
url = ''
headers = {

}
request = urllib.request.Request(url=url, headers=headers)
response = opener.open(request)

with open('file.txt', 'wb') as f:
    f.write(response.read())

'''