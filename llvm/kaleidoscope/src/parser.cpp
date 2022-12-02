#include <parser.h>

#include <iostream>
#include <stdexcept>
#include <vector>

Parser::Parser(std::string code) : lexer(code) {
  binop_prec["<"] = 10;
  binop_prec["+"] = 20;
  binop_prec["-"] = 20;
  binop_prec["*"] = 40;
  next_token();
}

int Parser::get_prec() {
  if (binop_prec.count(current_token.second) == 0)
    return -1;
  int prec = binop_prec[current_token.second];
  return prec;
}

Token Parser::next_token() { return current_token = lexer.get_token(); }

std::unique_ptr<ExprNode> Parser::parse_int() {
  auto node =
      std::make_unique<LiteralExprNode<int>>(std::stoi(current_token.second));
  next_token();
  return std::move(node);
}

std::unique_ptr<ExprNode> Parser::parse_float() {
  auto node = std::make_unique<LiteralExprNode<double>>(
      std::stod(current_token.second));
  next_token();
  return std::move(node);
}

std::unique_ptr<ExprNode> Parser::parse_paren_expr() {
  next_token();
  auto node = parse_expr();
  if (node == nullptr)
    return nullptr;
  if (current_token.second != ")")
    throw std::logic_error("expected )");
  next_token();
  return node;
}

std::unique_ptr<ExprNode> Parser::parse_identifier() {
  std::string identifier = current_token.second;
  next_token();
  if (current_token.second != "(")
    return std::make_unique<VariableExprNode>(identifier);

  next_token();
  std::vector<std::unique_ptr<ExprNode>> args;
  if (current_token.second != ")") {
    while (true) {
      auto arg = parse_expr();
      if (arg != nullptr)
        args.push_back(std::move(arg));
      else
        return nullptr;

      if (current_token.second == ")")
        break;
      if (current_token.second != ",")
        throw std::logic_error("expected ) or , in arg list");
      next_token();
    }
  }
  next_token();
  return std::make_unique<CallExprNode>(identifier, std::move(args));
}

std::unique_ptr<ExprNode> Parser::parse_primary() {
  switch (current_token.first) {
  case TokenKind::kIdentifier:
    return parse_identifier();
  case TokenKind::kInt:
    return parse_int();
  case TokenKind::kFloat:
    return parse_float();
  default:
    throw std::logic_error("unknown token");
  }
}

std::unique_ptr<ExprNode>
Parser::parse_binop_rhs(int expr_prec, std::unique_ptr<ExprNode> lhs) {
  while (true) {
    int token_prec = get_prec();
    if (token_prec < expr_prec)
      return lhs;

    auto op = current_token;
    next_token();

    auto rhs = parse_primary();
    if (rhs == nullptr)
      return nullptr;
    int next_prec = get_prec();
    if (token_prec < next_prec) {
      rhs = parse_binop_rhs(token_prec + 1, std::move(rhs));
      if (rhs == nullptr)
        return nullptr;
    }
    lhs = std::make_unique<BinaryExprNode>(op.second, std::move(lhs),
                                           std::move(rhs));
  }
}

std::unique_ptr<ExprNode> Parser::parse_expr() {
  auto lhs = parse_primary();
  if (lhs == nullptr)
    return nullptr;
  return parse_binop_rhs(0, std::move(lhs));
}

std::unique_ptr<PrototypeNode> Parser::parse_proto() {
  if (current_token.first != TokenKind::kIdentifier)
    throw std::logic_error("expected function name");

  std::string func_name = current_token.second;
  next_token();

  if (current_token.second != "(")
    throw std::logic_error("expected ( in prototype");

  std::vector<std::pair<std::string, std::string>> arg_names;
  while (next_token().first == TokenKind::kIdentifier) {
    auto var_name = current_token.second;
    if (next_token().second != ":")
      throw std::logic_error("expected : after arg name");
    auto type_name = next_token().second;
    arg_names.push_back({var_name, type_name});
    if (next_token().second != ",")
      break;
  }
  if (current_token.second != ")")
    throw std::logic_error("expected ) in prototype");
  if (next_token().second != ":")
    throw std::logic_error("expected : after args");
  auto return_type = next_token().second;
  next_token();
  return std::make_unique<PrototypeNode>(func_name, std::move(arg_names),
                                         return_type);
}

std::unique_ptr<FunctionNode> Parser::parse_def() {
  next_token();
  auto proto = parse_proto();
  if (proto == nullptr)
    return nullptr;
  auto expr = parse_expr();
  if (expr != nullptr)
    return std::make_unique<FunctionNode>(std::move(proto), std::move(expr));
  return nullptr;
}

std::unique_ptr<FunctionNode> Parser::parse_toplevel_expr() {
  auto expr = parse_expr();
  if (expr == nullptr)
    return nullptr;
  auto proto = std::make_unique<PrototypeNode>(
      "__anon_expr", std::vector<std::pair<std::string, std::string>>(),
      "void");
  return std::make_unique<FunctionNode>(std::move(proto), std::move(expr));
}

std::unique_ptr<FunctionNode> Parser::parse_extern() {
  next_token();
  auto proto = parse_proto();
  auto func = std::make_unique<FunctionNode>(std::move(proto));
  return func;
}
