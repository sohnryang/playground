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
  LiteralExprNode(T value);
};

class VariableExprNode : public ExprNode {
private:
  std::string name;

public:
  VariableExprNode(const std::string &name);
};

class BinaryExprNode : public ExprNode {
private:
  std::string op;
  std::unique_ptr<ExprNode> lhs, rhs;

public:
  BinaryExprNode(std::string op, std::unique_ptr<ExprNode> lhs,
                 std::unique_ptr<ExprNode> rhs);
};

class CallExprNode : public ExprNode {
private:
  std::string callee;
  std::vector<std::unique_ptr<ExprNode>> args;

public:
  CallExprNode(const std::string &callee,
               std::vector<std::unique_ptr<ExprNode>> args);
};

class PrototypeNode {
private:
  std::string name;
  std::string return_type;
  std::vector<std::pair<std::string, std::string>> args;

public:
  PrototypeNode(const std::string &name,
                std::vector<std::pair<std::string, std::string>> args,
                std::string return_type);
  const std::string &get_name() const;
};

class FunctionNode {
private:
  std::unique_ptr<PrototypeNode> proto;
  std::unique_ptr<ExprNode> func_body;

public:
  FunctionNode(std::unique_ptr<PrototypeNode> proto,
               std::unique_ptr<ExprNode> func_body);
};
