import urllib.request
import urllib.parse

url = 'http://www.baidu.com'

headers = {
    "User-Agent" : "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/126.0.0.0 Safari/537.36 Edg/126.0.0.0",
}

# 定义一个handler
handler = urllib.request.HTTPHandler()

# 定义一个opener， opener对象发送url请求，替换urlopen
opener = urllib.request.build_opener(handler)

request = urllib.request.Request(url=url, headers=headers)

response = opener.open(request)
print(response.read().decode())


