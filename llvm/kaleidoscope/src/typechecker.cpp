#include <typechecker.h>

#include <stdexcept>
#include <variant>

ExprTypeChecker::ExprTypeChecker() : globals(), functions() {}

ExprTypeChecker::ExprTypeChecker(
    std::map<std::string, Type> &globals,
    std::map<std::string, std::pair<Type, std::vector<Type>>> functions)
    : globals(globals), functions(functions) {}

Type ExprTypeChecker::operator()(const LiteralExprNode<int> &node) const {
  return Type::kInt;
}

Type ExprTypeChecker::operator()(const LiteralExprNode<double> &node) const {
  return Type::kFloat;
}

Type ExprTypeChecker::operator()(const VariableExprNode &node) const {
  return globals.at(node.name);
}

Type ExprTypeChecker::operator()(
    const std::unique_ptr<BinaryExprNode> &node) const {
  auto lhs_type = std::visit(*this, node->lhs),
       rhs_type = std::visit(*this, node->rhs);
  if (lhs_type == Type::kVoid || rhs_type == Type::kVoid)
    throw std::logic_error("void not allowed");
  if (lhs_type == Type::kFloat || rhs_type == Type::kFloat)
    return Type::kFloat;
  return Type::kInt;
}

Type ExprTypeChecker::operator()(
    const std::unique_ptr<CallExprNode> &node) const {
  for (auto &arg : node->args) {
    auto arg_type = std::visit(*this, arg);
    if (arg_type == Type::kVoid)
      throw std::logic_error("void not allowed here");
  }
  return functions.at(node->callee).first;
}
