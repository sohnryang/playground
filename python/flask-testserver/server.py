from flask import Flask, request

app = Flask("test_server")


@app.route("/")
def index():
    remote_addr = request.remote_addr
    return f"remote_addr: {remote_addr}"


if __name__ == "__main__":
    app.run("0.0.0.0", 8080)
