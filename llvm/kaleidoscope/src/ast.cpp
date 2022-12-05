#include <ast.h>

#include <cstdint>
#include <stdexcept>

#include <fmt/core.h>

template <typename T>
LiteralExprNode<T>::LiteralExprNode(T value) : value(value) {}

template <typename T> std::string LiteralExprNode<T>::to_string() {
  return fmt::format("Literal({})", value);
}

VariableExprNode::VariableExprNode(const std::string &name) : name(name) {}

std::string VariableExprNode::to_string() {
  return fmt::format("Variable({})", name);
}

BinaryExprNode::BinaryExprNode(std::string op, std::unique_ptr<ExprNode> lhs,
                               std::unique_ptr<ExprNode> rhs)
    : op(op), lhs(std::move(lhs)), rhs(std::move(rhs)) {}

std::string BinaryExprNode::to_string() {
  return fmt::format("BinaryExpr({}, {}, {})", op, lhs->to_string(),
                     rhs->to_string());
}

CallExprNode::CallExprNode(const std::string &callee,
                           std::vector<std::unique_ptr<ExprNode>> args)
    : callee(callee), args(std::move(args)) {}

std::string CallExprNode::to_string() {
  std::string arg_str;
  for (auto &arg : args) {
    if (!arg_str.empty())
      arg_str.append(", ");
    arg_str.append(arg->to_string());
  }
  return fmt::format("CallExpr({}, [{}])", callee, arg_str);
}

PrototypeNode::PrototypeNode(
    const std::string &name,
    std::vector<std::pair<std::string, std::string>> args,
    std::string return_type)
    : name(name), args(std::move(args)), return_type(return_type) {}
const std::string &PrototypeNode::get_name() const { return name; }

std::string PrototypeNode::to_string() {
  std::string arg_str;
  for (auto &arg : args) {
    if (!arg_str.empty())
      arg_str.append(", ");
    arg_str.append(fmt::format("Arg({}, {})", arg.first, arg.second));
  }
  return fmt::format("Prototype({}, [{}], {})", name, arg_str, return_type);
}

FunctionNode::FunctionNode(std::unique_ptr<PrototypeNode> proto,
                           std::unique_ptr<ExprNode> func_body)
    : proto(std::move(proto)), func_body(std::move(func_body)),
      extern_func(false) {}

FunctionNode::FunctionNode(std::unique_ptr<PrototypeNode> proto)
    : proto(std::move(proto)), func_body(nullptr), extern_func(true) {}

std::string FunctionNode::to_string() {
  if (extern_func)
    return fmt::format("ExternFunc({})", proto->to_string());
  return fmt::format("Func({}, {})", proto->to_string(),
                     func_body->to_string());
}

template class LiteralExprNode<int>;
template class LiteralExprNode<double>;
