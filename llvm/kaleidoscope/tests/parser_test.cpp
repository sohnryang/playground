#include <parser.h>

#include <gtest/gtest.h>

#include <sstream>

TEST(ParserTest, Int) {
  Parser parser("42");
  EXPECT_NO_THROW(parser.parse_int());
}

TEST(ParserTest, Float) {
  Parser parser("2.71828");
  EXPECT_NO_THROW(parser.parse_float());
}

TEST(ParserTest, Prototype) {
  Parser parser("func(a: int, b: double, c: int): int");
  EXPECT_NO_THROW(parser.parse_proto());
}

TEST(ParserTest, Expr) {
  Parser parser("a*a + b*b - c*c");
  EXPECT_NO_THROW(parser.parse_expr());
}

TEST(ParserTest, ParenExpr) {
  Parser parser("(a + b)*(a + b);");
  EXPECT_NO_THROW(parser.parse_paren_expr());
}

TEST(ParserTest, All) {
  Parser parser("(a + b)*(a + b);");
  EXPECT_NO_THROW(parser.parse_all());
}
