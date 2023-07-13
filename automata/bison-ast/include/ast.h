#pragma once

#include <memory>
#include <string>
#include <variant>

struct NumberExprNode {
  double value;

  NumberExprNode(double value);
  NumberExprNode(NumberExprNode &&) = default;
  NumberExprNode &operator=(NumberExprNode &&) = default;
};

struct VariableExprNode {
  std::string name;

  VariableExprNode(const std::string &name);
  VariableExprNode(VariableExprNode &&) = default;
  VariableExprNode &operator=(VariableExprNode &&) = default;
};

struct BinaryExprNode;

using ExprNode = std::variant<NumberExprNode, VariableExprNode,
                              std::unique_ptr<BinaryExprNode>>;

struct BinaryExprNode {
  std::string op;
  ExprNode lhs, rhs;

  BinaryExprNode(const std::string &op, ExprNode lhs, ExprNode rhs);
  BinaryExprNode(BinaryExprNode &&) = default;
  BinaryExprNode &operator=(BinaryExprNode &&) = default;
};

class ASTPrinter {
public:
  void operator()(const NumberExprNode &node);
  void operator()(const VariableExprNode &node);
  void operator()(const std::unique_ptr<BinaryExprNode> &node);
};
