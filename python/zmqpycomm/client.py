import zmq

context = zmq.Context()
socket = context.socket(zmq.REQ)
socket.connect("ipc:///tmp/zmq_socket")
print("Connected to server")

for i in range(10):
    print(f"Sending req id={i}")
    socket.send(b"Hell")
    message = socket.recv()
    print(f"Got: {message}")
