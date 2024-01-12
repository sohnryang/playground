const express = require("express");
const morgan = require("morgan");
const session = require("express-session");
const bodyParser = require("body-parser");
const path = require("path");

const app = express();
app.use(morgan("combined"));
app.set("view engine", "pug");
app.use(session({ secret: "totally secret" }));
app.use(bodyParser.urlencoded({ extended: false }));
app.use("/static", express.static(path.join(__dirname, "public")));

function isSignedIn(req, res, next) {
  if (req.session.user) {
    next();
  } else {
    res.status(401).send("Unauthorized");
  }
}

app.get("/", (req, res) => {
  res.render("index", { user: req.session.user, title: "Index" });
});

app.get("/signin", (_, res) => {
  res.render("signin", { title: "Sign In" });
});

app.post("/signin", (req, res) => {
  if (req.body.username === "admin" && req.body.password === "admin") {
    req.session.user = req.body.username;
    res.redirect("/");
  }
});

app.get("/signout", (req, res) => {
  req.session.destroy();
  res.redirect("/");
});

app.get("/secret", isSignedIn, (_, res) => {
  res.render("secret", { title: "Index" });
});

app.listen(3000, () => {
  console.log("Server is listening on port 3000");
});
