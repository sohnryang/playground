#include <lexer.h>

#include <cctype>

Lexer::Lexer(std::string code) : code(code), last_char(' ') {
  it = this->code.begin();
}

Token Lexer::get_token() {
  while (std::isspace(last_char))
    last_char = *(it++);
  if (std::isalpha(last_char)) {
    identifier = last_char;
    while (std::isalnum(last_char = *(it++)) || last_char == '_')
      identifier += last_char;
    if (identifier == "def")
      return {TokenKind::kDef, identifier};
    if (identifier == "extern")
      return {TokenKind::kExtern, identifier};
    return {TokenKind::kIdentifier, identifier};
  }

  if (std::isdigit(last_char) || last_char == '.') {
    std::string num_str;
    do {
      num_str += last_char;
      last_char = *(it++);
    } while (std::isdigit(last_char) || last_char == '.');
    if (num_str.find('.') != std::string::npos)
      return {TokenKind::kFloat, num_str};
    return {TokenKind::kInt, num_str};
  }

  if (last_char == '#') {
    do
      last_char = *(it++);
    while (last_char != '\0' && last_char != '\n' && last_char != '\r');
    if (last_char != '\0')
      return get_token();
  }

  if (last_char == '\0')
    return {TokenKind::kEof, ""};

  int this_char = last_char;
  last_char = *(it++);
  return {TokenKind::kMisc, std::string(1, this_char)};
}
