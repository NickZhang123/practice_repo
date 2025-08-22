


import socket

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, True)
server.bind(("", 10010))
server.listen(10)
cli = server.accept()

print(cli)
print(server)

cli[0].close()
server.close()

