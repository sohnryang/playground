#pragma once

#include <ast.h>
#include <lexer.h>

#include <map>
#include <memory>
#include <streambuf>
#include <string>
#include <utility>

class Parser {
private:
  Lexer lexer;
  Token current_token;
  Token next_token();
  std::map<std::string, int> binop_prec;
  int get_prec();

public:
  Parser(std::streambuf *sb);
  std::unique_ptr<ExprNode> parse_int();
  std::unique_ptr<ExprNode> parse_float();
  std::unique_ptr<ExprNode> parse_expr();
  std::unique_ptr<ExprNode> parse_paren_expr();
  std::unique_ptr<ExprNode> parse_identifier();
  std::unique_ptr<ExprNode> parse_primary();
  std::unique_ptr<ExprNode> parse_binop_rhs(int prec,
                                            std::unique_ptr<ExprNode> lhs);
  std::unique_ptr<PrototypeNode> parse_proto();
  std::unique_ptr<FunctionNode> parse_def();
  std::unique_ptr<FunctionNode> parse_toplevel_expr();
  std::unique_ptr<PrototypeNode> parse_extern();
};
