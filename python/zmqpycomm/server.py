import time
import zmq

context = zmq.Context()
socket = context.socket(zmq.REP)
socket.bind("ipc:///tmp/zmq_socket")
print("Server started")

while True:
    message = socket.recv()
    print(f"Got: {message}")
    time.sleep(1)
    socket.send(b"world")
