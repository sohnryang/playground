from flask import (
    Flask,
    make_response,
    redirect,
    render_template,
    request,
    send_file,
    url_for,
)

app = Flask("test_server")


@app.route("/")
def index():
    remote_addr = request.remote_addr
    return f"remote_addr: {remote_addr}"


@app.route("/get-header")
def get_header():
    if "X-Test-Header" not in request.headers:
        return "X-Test-Header not in request"
    else:
        header = request.headers["X-Test-Header"]
        return f"X-Test-Header = {header}"


@app.route("/set-header")
def set_header():
    res = make_response("response with X-Test-Header set")
    res.headers.set("X-Test-Header", "hello from flask")
    return res


@app.route("/get-cookie")
def get_cookie():
    if "testcookie" not in request.cookies:
        return "testcookie not set"
    else:
        cookie = request.cookies["testcookie"]
        return f"testcookie = {cookie}"


@app.route("/set-cookie")
def set_cookie():
    res = make_response("response for setting cookie")
    res.set_cookie("testcookie", "cookie for testing")
    return res


@app.route("/render")
def render():
    return render_template("index.html", message=request.args.get("message"))


@app.route("/upload", methods=["GET", "POST"])
def upload():
    if request.method == "GET":
        return render_template("upload.html")
    if "file" not in request.files:
        return redirect(request.url)
    file = request.files["file"]
    if not file.filename:
        return redirect(request.url)
    file.save("./uploaded/" + file.filename)
    return redirect(request.url)


@app.route("/download")
def download():
    filename = request.args.get("filename", "")
    return send_file("./uploaded/" + filename)


if __name__ == "__main__":
    app.run("0.0.0.0", 8080)
