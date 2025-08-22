import urllib.request

# 发送 GET 请求
url = 'http://httpbin.org/get'
response = urllib.request.urlopen(url)

# 获取状态码
status_code = response.status
print(f"Status Code: {status_code}")        # Status Code: 200

# 获取响应头
headers = response.headers
print(type(headers))    # <class 'http.client.HTTPMessage'>
for header, value in headers.items():
    print(f"{header}: {value}")

# 获取响应内容
content = response.read()
print("Response Content:")
print(content.decode('utf-8'))
