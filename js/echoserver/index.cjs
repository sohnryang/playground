const express = require("express");
const morgan = require("morgan");

const app = express();
app.use(morgan("combined"));

app.get("/echo", (req, res) => {
  res.setHeader("Content-Type", "text/html");
  res.send(`Your input: ${req.query.data}`);
});

app.get("/imageviewer", (req, res) => {
  res.setHeader("Content-Type", "text/html");
  res.send(`
    <html>
      <body>
        <img src="${req.query.url}" />
      </body>
    </html>
  `);
});

app.listen(3000, () => {
  console.log("Server listening on port 3000");
});
