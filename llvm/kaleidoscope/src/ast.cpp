#include <ast.h>

template <typename T>
LiteralExprNode<T>::LiteralExprNode(T value) : value(value) {}

VariableExprNode::VariableExprNode(const std::string &name) : name(name) {}

BinaryExprNode::BinaryExprNode(std::string op, std::unique_ptr<ExprNode> lhs,
                               std::unique_ptr<ExprNode> rhs)
    : op(op), lhs(std::move(lhs)), rhs(std::move(rhs)) {}

CallExprNode::CallExprNode(const std::string &callee,
                           std::vector<std::unique_ptr<ExprNode>> args)
    : callee(callee), args(std::move(args)) {}

PrototypeNode::PrototypeNode(
    const std::string &name,
    std::vector<std::pair<std::string, std::string>> args)
    : name(name), args(std::move(args)) {}
const std::string &PrototypeNode::get_name() const { return name; }

FunctionNode::FunctionNode(std::unique_ptr<PrototypeNode> proto,
                           std::unique_ptr<ExprNode> func_body)
    : proto(std::move(proto)), func_body(std::move(func_body)) {}

template class LiteralExprNode<int>;
template class LiteralExprNode<double>;
