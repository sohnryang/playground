#include <gtest/gtest.h>

#include <lexer.h>
#include <sstream>
#include <string>
#include <utility>

TEST(LexerTest, Def) {
  Lexer lexer("def");
  EXPECT_EQ(lexer.get_token(), Token(TokenKind::kDef, "def"));
  EXPECT_EQ(lexer.get_token(), Token(TokenKind::kEof, ""));
}

TEST(LexerTest, Number) {
  Lexer lexer("42 3.141592");
  EXPECT_EQ(lexer.get_token(), Token(TokenKind::kInt, "42"));
  EXPECT_EQ(lexer.get_token(), Token(TokenKind::kFloat, "3.141592"));
  EXPECT_EQ(lexer.get_token(), Token(TokenKind::kEof, ""));
}

TEST(LexerTest, FunctionDef) {
  Lexer lexer("def func()\n  0");
  EXPECT_EQ(lexer.get_token(), Token(TokenKind::kDef, "def"));
  EXPECT_EQ(lexer.get_token(), Token(TokenKind::kIdentifier, "func"));
  EXPECT_EQ(lexer.get_token(), Token(TokenKind::kMisc, "("));
  EXPECT_EQ(lexer.get_token(), Token(TokenKind::kMisc, ")"));
  EXPECT_EQ(lexer.get_token(), Token(TokenKind::kInt, "0"));
  EXPECT_EQ(lexer.get_token(), Token(TokenKind::kEof, ""));
}
