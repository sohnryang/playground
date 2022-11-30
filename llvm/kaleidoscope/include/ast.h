#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

class ExprNode {
public:
  virtual ~ExprNode() = default;
};

template <typename T> class LiteralExprNode : public ExprNode {
private:
  T value;

public:
  LiteralExprNode(T value) : value(value) {}
};

class VariableExprNode : public ExprNode {
private:
  std::string name;

public:
  VariableExprNode(const std::string &name) : name(name) {}
};

class BinaryExprNode : public ExprNode {
private:
  std::string op;
  std::unique_ptr<ExprNode> lhs, rhs;

public:
  BinaryExprNode(std::string op, std::unique_ptr<ExprNode> lhs,
                 std::unique_ptr<ExprNode> rhs)
      : op(op), lhs(std::move(lhs)), rhs(std::move(rhs)) {}
};

class CallExprNode : public ExprNode {
private:
  std::string callee;
  std::vector<std::unique_ptr<ExprNode>> args;

public:
  CallExprNode(const std::string &callee,
               std::vector<std::unique_ptr<ExprNode>> args)
      : callee(callee), args(std::move(args)) {}
};

class PrototypeNode {
private:
  std::string name;
  std::vector<std::string> args;

public:
  PrototypeNode(const std::string &name, std::vector<std::string> args)
      : name(name), args(std::move(args)) {}
  const std::string &get_name() const { return name; }
};

class FunctionNode {
private:
  std::unique_ptr<PrototypeNode> proto;
  std::unique_ptr<ExprNode> func_body;

public:
  FunctionNode(std::unique_ptr<PrototypeNode> proto,
               std::unique_ptr<ExprNode> func_body)
      : proto(std::move(proto)), func_body(std::move(func_body)) {}
};
