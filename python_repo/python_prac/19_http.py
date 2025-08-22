

import socket

httpSer = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
httpSer.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, True) # 记住格式
httpSer.bind(("", 10011)) # 元组
httpSer.listen(12)

while True:
    cliSock, cliInfo = httpSer.accept()
    print(f"接受到来自客户端{cliInfo[0]}:{cliInfo[1]}的链接请求")

    print(f"接受的数据：{cliSock.recv(1024).decode()}")

    # 准备响应体
    with open('index.html', 'rb') as f:  # 二进制读取响应体
        res_body = f.read()
    
    # 响应行
    res_line = 'HTTP/1.1 200 OK\r\n'

    # 响应头
    res_header = 'Server:PSWS1.0\r\n'

    # 响应行和响应头是文本，需要编码； 内容直接使用二进制读出来，不需要转换
    res = (res_line + res_header + '\r\n').encode() + res_body
    print(f"响应消息{res}")

    # 发送响应体
    cliSock.send(res)

    # 关闭客户端
    cliSock.close()

# 服务端关闭
httpSer.close()
