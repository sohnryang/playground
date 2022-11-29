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
  std::string identifier;
  int last_char;
  std::istream stream;

public:
  Lexer(std::streambuf *sb);
  std::pair<TokenKind, std::string> get_token();
};
