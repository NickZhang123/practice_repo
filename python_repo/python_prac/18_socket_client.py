
import socket

class TcpClient(object):
    def __init__(self) -> None:
        # 1. 创建socket，tcp&ipv4
        # AF_INET - IPV4
        # SOCK_STREAM - tcp
        self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    def connect(self, ip, port):
        # 2. 链接服务器
        # ip, port
        self.client.connect((ip, port))  # 元组格式

    def DoDataTrans(self):
        while True:
            data = input("输入要发送的数据(q-退出):")
            
            # 退出
            if (data == 'q'):
                break

            # 发送数据
            if (len(data) == 0):
                data = data + "\n"  # 空字符串不会触发服务端recv，需要主动发一个其他字符
            self.client.send(data.encode("utf-8"))

            # 接受数据
            res = self.client.recv(1024).decode("utf-8")

            # 断开判断
            if (len(res) == 0):
                print(f"服务端断开连接")
                break

            print(f"接收到服务端消息：{res}")    
            
        self.client.close()


if __name__ == "__main__":
    cli = TcpClient()
    cli.connect("localhost", 10010)
    cli.DoDataTrans()

