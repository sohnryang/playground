from socket import socket, AF_INET, SOCK_STREAM

sock = socket(AF_INET, SOCK_STREAM)
sock.bind(("localhost", 3000))
sock.listen(1)
print("Listening on port 3000")

while True:
    conn, addr = sock.accept()
    payload = conn.recv(1024)
    print(f"Got payload from {addr}: {payload}")
    conn.send(str(len(payload)).encode())
    conn.close()
