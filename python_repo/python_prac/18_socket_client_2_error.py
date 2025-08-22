
import socket
import time

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(("localhost", 10010))
print("connect")
time.sleep(2)
print(client.send("xxxxxx".encode("utf-8")))
print(client)
