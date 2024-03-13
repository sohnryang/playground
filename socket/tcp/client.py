from socket import socket, AF_INET, SOCK_STREAM

sock = socket(AF_INET, SOCK_STREAM)
sock.connect(("localhost", 3000))
payload = input("payload: ")
sock.send(payload.encode())
res = sock.recv(1024)
print(f"response: {res}")
sock.close()
