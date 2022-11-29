#include <lexer.h>

#include <cctype>
#include <string>

Lexer::Lexer(std::streambuf *sb) : last_char(' '), stream(sb) {}

Token Lexer::get_token() {
  while (std::isspace(last_char))
    last_char = stream.get();
  if (std::isalpha(last_char)) {
    identifier = last_char;
    while (std::isalnum(last_char = stream.get()))
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
      last_char = stream.get();
    } while (std::isdigit(last_char) || last_char == '.');
    if (num_str.find('.') != std::string::npos)
      return {TokenKind::kFloat, num_str};
    return {TokenKind::kInt, num_str};
  }

  if (last_char == '#') {
    do
      last_char = stream.get();
    while (last_char != std::char_traits<char>::eof() && last_char != '\n' &&
           last_char != '\r');
    if (last_char != std::char_traits<char>::eof())
      return get_token();
  }

  if (last_char == std::char_traits<char>::eof())
    return {TokenKind::kEof, ""};

  int this_char = last_char;
  last_char = stream.get();
  return {TokenKind::kMisc, std::string(1, this_char)};
}
