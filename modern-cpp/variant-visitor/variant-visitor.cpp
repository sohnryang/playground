#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <variant>

template <typename T> struct Const {
  T value;
  Const(T value) : value(value) {}
};

struct Variable {
  std::string name;
  Variable(std::string name) : name(name) {}
};

using Expr =
    std::variant<Const<int>, Variable, std::unique_ptr<struct BinaryExpr>>;

struct BinaryExpr {
  std::string op;
  Expr lhs, rhs;
  BinaryExpr(std::string op, Expr lhs, Expr rhs)
      : op(op), lhs(std::move(lhs)), rhs(std::move(rhs)) {}
};

class Calculator {
private:
  std::map<std::string, int> variables;

public:
  Calculator(std::map<std::string, int> &variables) : variables(variables) {}
  int operator()(Const<int> c) { return c.value; }
  int operator()(Variable var) { return variables.at(var.name); }
  int operator()(std::unique_ptr<BinaryExpr> &expr) {
    if (expr->op == "+")
      return std::visit(*this, expr->lhs) + std::visit(*this, expr->rhs);
    else
      throw std::logic_error("not implemented");
  }
};

int main() {
  Expr expr(std::make_unique<BinaryExpr>("+", Const<int>(1), Variable("x")));
  std::map<std::string, int> variables;
  variables["x"] = 42;
  Calculator calc(variables);
  std::cout << std::visit(calc, expr) << std::endl;
  return 0;
}
