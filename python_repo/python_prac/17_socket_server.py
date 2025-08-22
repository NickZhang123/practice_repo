'''
    服务端在accept后, 新开一个线程处理链接
'''

import socket
import threading

class TcpServer(object):
    def __init__(self, port) -> None:
        # 1. 创建socket
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        # 设置socket选项(地址和端口重复使用)
        self.server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, True)

        # 2. 绑定端口
        self.server.bind(("", port))  # 元组格式  

        # 3. 监听
        self.server.listen(10)     # 最大等待连接个数，超过这个数，后面的请求连接不上
    
    def start(self):
        while True:
            # 4. 接受链接（产生新的socket）
            cli_socket, cli_ip_port = self.server.accept()  # 解包客户端对象和(ip、地址), 产生了新对象，和server对象无关

            # 5. 和client交互
            cli = threading.Thread(target=self.DoClientConn, args=(cli_socket, cli_ip_port))    # 参数中不带self
            cli.daemon = True
            cli.start()

        # 6. 关闭连接
        self.server.close()

    def DoClientConn(self, cli_socket, cli_ip_port):
        print(f"接受到来自客户端{cli_ip_port[0]}:{cli_ip_port[1]}的链接请求")
        while True:
            try:
                # 接受消息
                data = cli_socket.recv(1024).decode("utf-8")    # 如果客户端建立连接后异常关闭，这里抛异常

                # 客户端断开连接
                if (len(data) == 0):
                    print(f"客户端[{cli_ip_port[0]}:{cli_ip_port[1]}]离开了")
                    break

                # 打印客户端消息
                print(f"接收到客户端消息：{data}")

                # 回复客户端内容
                cli_socket.send((data + "bak").encode("utf-8"))

            except Exception as e:
                print(f"Error:{e}")
                break

        cli_socket.close()

if __name__ == '__main__':
    server = TcpServer(10010)
    server.start()