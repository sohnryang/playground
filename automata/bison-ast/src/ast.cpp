#include "ast.h"

#include <memory>
#include <string>
#include <utility>
#include <variant>

#include <fmt/core.h>

NumberExprNode::NumberExprNode(double value) : value(value) {}

BinaryExprNode::BinaryExprNode(const std::string &op, ExprNode lhs,
                               ExprNode rhs)
    : op(op), lhs(std::move(lhs)), rhs(std::move(rhs)) {}

VariableExprNode::VariableExprNode(const std::string &name) : name(name) {}

void ASTPrinter::operator()(const NumberExprNode &node) {
  fmt::print("NumberExprNode({})", node.value);
}

void ASTPrinter::operator()(const VariableExprNode &node) {
  fmt::print("VariableExprNode({})", node.name);
}

void ASTPrinter::operator()(const std::unique_ptr<BinaryExprNode> &node) {
  fmt::print("BinaryExprNode({}, ", node->op);
  std::visit(*this, node->lhs);
  fmt::print(", ");
  std::visit(*this, node->rhs);
  fmt::print(")");
}
