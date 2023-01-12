const http = require("http");

const server = http.createServer((_, res) => {
  res.writeHead(200, {"Content-Type": "text/plain"});
  res.end("hell world!");
});

server.listen(8080, "0.0.0.0");
