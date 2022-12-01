#pragma once

#include <istream>
#include <streambuf>
#include <string>
#include <utility>

enum class TokenKind {
  kEof,
  kDef,
  kExtern,
  kIdentifier,
  kInt,
  kFloat,
  kMisc,
};
typedef std::pair<TokenKind, std::string> Token;

class Lexer {
private:
  std::string identifier, code;
  std::string::iterator it;
  int last_char;

public:
  Lexer(std::string code);
  std::pair<TokenKind, std::string> get_token();
};
