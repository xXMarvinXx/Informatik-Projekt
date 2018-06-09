import socket
s= socket.socket()
s.connect(('192.168.1.235' , 30303))
s.setblocking(False)

s.send(b "Hello World\n")

s.recv(1024)
