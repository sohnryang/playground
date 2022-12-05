#pragma once

#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class ExprNode {
public:
  virtual ~ExprNode() = default;
  virtual std::string to_string() = 0;
};

template <typename T> class LiteralExprNode : public ExprNode {
private:
  T value;

public:
  LiteralExprNode(T value);
  std::string to_string() override;
};

class VariableExprNode : public ExprNode {
private:
  std::string name;

public:
  VariableExprNode(const std::string &name);
  std::string to_string() override;
};

class BinaryExprNode : public ExprNode {
private:
  std::string op;
  std::unique_ptr<ExprNode> lhs, rhs;

public:
  BinaryExprNode(std::string op, std::unique_ptr<ExprNode> lhs,
                 std::unique_ptr<ExprNode> rhs);
  std::string to_string() override;
};

class CallExprNode : public ExprNode {
private:
  std::string callee;
  std::vector<std::unique_ptr<ExprNode>> args;

public:
  CallExprNode(const std::string &callee,
               std::vector<std::unique_ptr<ExprNode>> args);
  std::string to_string() override;
};

class StatementNode {
public:
  virtual ~StatementNode() = default;
  virtual std::string to_string() = 0;
};

class PrototypeNode : public StatementNode {
private:
  std::string name;
  std::string return_type;
  std::vector<std::pair<std::string, std::string>> args;

public:
  PrototypeNode(const std::string &name,
                std::vector<std::pair<std::string, std::string>> args,
                std::string return_type);
  const std::string &get_name() const;
  std::string to_string() override;
};

class FunctionNode : public StatementNode {
private:
  std::unique_ptr<PrototypeNode> proto;
  std::unique_ptr<ExprNode> func_body;
  bool extern_func;

public:
  FunctionNode(std::unique_ptr<PrototypeNode> proto,
               std::unique_ptr<ExprNode> func_body);
  FunctionNode(std::unique_ptr<PrototypeNode> proto);
  std::string to_string() override;
};
