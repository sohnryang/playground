#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Expr;
class BinOpExpr;
class LiteralExpr;

class Visitor {
public:
  virtual void visit(BinOpExpr *expr);
  virtual void visit(LiteralExpr *expr);
};

void Visitor::visit(BinOpExpr *expr) {}
void Visitor::visit(LiteralExpr *expr) {}

class Expr {
public:
  virtual ~Expr() = default;
  virtual void accept(Visitor &visitor) = 0;
};

struct BinOpExpr : public Expr {
  std::string op;
  std::unique_ptr<Expr> lhs, rhs;

  BinOpExpr() = default;
  BinOpExpr(const std::string &op, std::unique_ptr<Expr> lhs,
            std::unique_ptr<Expr> rhs);
  void accept(Visitor &visitor) { visitor.visit(this); }
};

BinOpExpr::BinOpExpr(const std::string &op, std::unique_ptr<Expr> lhs,
                     std::unique_ptr<Expr> rhs)
    : op(op), lhs(std::move(lhs)), rhs(std::move(rhs)) {}

struct LiteralExpr : public Expr {
  int val;

  LiteralExpr() = default;
  LiteralExpr(int val);
  void accept(Visitor &visitor) { visitor.visit(this); }
};

LiteralExpr::LiteralExpr(int val) : val(val) {}

class PrefixPrintVisitor : public Visitor {
private:
  std::vector<std::string> expr_tokens;

public:
  std::string operator()(Expr *expr);
  void visit(BinOpExpr *expr) override;
  void visit(LiteralExpr *expr) override;
};

void PrefixPrintVisitor::visit(BinOpExpr *expr) {
  expr_tokens.push_back("(");
  expr_tokens.push_back(expr->op);
  expr->lhs->accept(*this);
  expr->rhs->accept(*this);
  expr_tokens.push_back(")");
}
void PrefixPrintVisitor::visit(LiteralExpr *expr) {
  expr_tokens.push_back(std::to_string(expr->val));
}
std::string PrefixPrintVisitor::operator()(Expr *expr) {
  expr_tokens.clear();
  expr->accept(*this);
  std::string res;
  for (const auto &token : expr_tokens) {
    if (!res.empty())
      res += " ";
    res += token;
  }
  return res;
}

int main() {
  PrefixPrintVisitor vis;
  std::unique_ptr<BinOpExpr> expr = std::make_unique<BinOpExpr>(
      "+",
      std::make_unique<BinOpExpr>("*", std::make_unique<LiteralExpr>(32),
                                  std::make_unique<LiteralExpr>(12)),
      std::make_unique<LiteralExpr>(42));
  std::cout << vis(expr.get()) << std::endl;
}
