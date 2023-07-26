let target = {
  secret: "this is secret!",
  public: "this is public",
};
let handler = {
  get(obj, prop) {
    if (prop === "secret") return "not allowed!";
    else return obj[prop];
  },
};
const p = new Proxy(target, handler);

console.log("public:", p.public);
console.log("secret:", p.secret);
