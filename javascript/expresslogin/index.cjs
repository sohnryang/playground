const express = require("express");
const morgan = require("morgan");
const app = express();

app.use(morgan("combined"));
app.set("view engine", "pug");

app.get("/", (_, res) => {
  res.render("index");
});

app.listen(3000, () => {
  console.log("Server is listening on port 3000");
});
