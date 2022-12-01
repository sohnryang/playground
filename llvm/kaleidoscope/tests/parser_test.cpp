#include <parser.h>

#include <gtest/gtest.h>

#include <sstream>

TEST(ParserTest, Int) {
  auto sb = new std::stringbuf("42");
  Parser parser(sb);
  EXPECT_NO_THROW(parser.parse_int());
  delete sb;
}

TEST(ParserTest, Float) {
  auto sb = new std::stringbuf("2.71828");
  Parser parser(sb);
  EXPECT_NO_THROW(parser.parse_float());
  delete sb;
}

TEST(ParserTest, Prototype) {
  auto sb = new std::stringbuf("func(a: int, b: double, c: int)");
  Parser parser(sb);
  EXPECT_NO_THROW(parser.parse_proto());
  delete sb;
}

TEST(ParserTest, Expr) {
  auto sb = new std::stringbuf("a*a + b*b - c*c");
  Parser parser(sb);
  EXPECT_NO_THROW(parser.parse_expr());
  delete sb;
}

TEST(ParserTest, ParenExpr) {
  auto sb = new std::stringbuf("(a + b)*(a + b)");
  Parser parser(sb);
  EXPECT_NO_THROW(parser.parse_paren_expr());
  delete sb;
}
