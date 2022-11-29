#include <gtest/gtest.h>

#include <lexer.h>
#include <sstream>
#include <string>
#include <utility>

TEST(LexerTest, Def) {
  auto sb = new std::stringbuf("def");
  Lexer lexer(sb);
  auto res = lexer.get_token();
  EXPECT_EQ(res.first, TokenKind::kDef);
  EXPECT_EQ(res.second, "def");
  delete sb;
}

TEST(LexerTest, FunctionDef) {
  auto sb = new std::stringbuf("def func()\n  0");
  Lexer lexer(sb);
  EXPECT_EQ(lexer.get_token(),
            std::make_pair(TokenKind::kDef, std::string("def")));
  EXPECT_EQ(lexer.get_token(),
            std::make_pair(TokenKind::kIdentifier, std::string("func")));
  EXPECT_EQ(lexer.get_token(),
            std::make_pair(TokenKind::kMisc, std::string("(")));
  EXPECT_EQ(lexer.get_token(),
            std::make_pair(TokenKind::kMisc, std::string(")")));
  EXPECT_EQ(lexer.get_token(),
            std::make_pair(TokenKind::kNumber, std::string("0")));
  delete sb;
}
