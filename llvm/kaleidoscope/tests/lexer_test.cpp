#include <gtest/gtest.h>

#include <lexer.h>
#include <sstream>
#include <string>
#include <utility>

TEST(LexerTest, Def) {
  auto sb = new std::stringbuf("def");
  Lexer lexer(sb);
  EXPECT_EQ(lexer.get_token(), Token(TokenKind::kDef, "def"));
  delete sb;
}

TEST(LexerTest, Number) {
  auto sb = new std::stringbuf("42 3.141592");
  Lexer lexer(sb);
  EXPECT_EQ(lexer.get_token(), Token(TokenKind::kInt, "42"));
  EXPECT_EQ(lexer.get_token(), Token(TokenKind::kFloat, "3.141592"));
  delete sb;
}

TEST(LexerTest, FunctionDef) {
  auto sb = new std::stringbuf("def func()\n  0");
  Lexer lexer(sb);
  EXPECT_EQ(lexer.get_token(), Token(TokenKind::kDef, "def"));
  EXPECT_EQ(lexer.get_token(), Token(TokenKind::kIdentifier, "func"));
  EXPECT_EQ(lexer.get_token(), Token(TokenKind::kMisc, "("));
  EXPECT_EQ(lexer.get_token(), Token(TokenKind::kMisc, ")"));
  EXPECT_EQ(lexer.get_token(), Token(TokenKind::kInt, "0"));
  delete sb;
}
