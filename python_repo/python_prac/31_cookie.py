import urllib.request
import urllib.parse
import http.cookiejar

# 创建一个cookieJar对象，用来保存cookie
cj = http.cookiejar.CookieJar()

# 根据cookieJar创建一个handler
handler = urllib.request.HTTPCookieProcessor(cj)

# 根据handler创建一个opener
opener = urllib.request.build_opener(handler)

data = urllib.parse.urlencode(form_data).encode()
request = urllib.request.Request(url, headers)
responose = opener.open(request, data)