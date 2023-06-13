#include <concepts>
#include <iostream>
#include <memory>
#include <type_traits>
#include <variant>

template <typename T1, typename T2>
concept Distinct = !
std::is_same<T1, T2>::value;

struct S {
  int a;
  bool b;
};

template <typename T> struct R {
  T a;
};

using Variant =
    std::variant<int, double, std::unique_ptr<int>, std::unique_ptr<double>,
                 std::unique_ptr<S>, std::unique_ptr<R<int>>,
                 std::unique_ptr<R<double>>, std::unique_ptr<struct A>,
                 std::unique_ptr<struct B>>;

struct A {
  Variant v;
};

struct B {
  Variant a, b;
};

class Visitor {
public:
  bool operator()(const int &a, const int &b) const {
    std::cout << "int vs int" << std::endl;
    return a == b;
  }

  bool operator()(const double &a, const double &b) const {
    std::cout << "int vs int" << std::endl;
    return a == b;
  }

  bool operator()(const std::unique_ptr<int> &a,
                  const std::unique_ptr<int> &b) const {
    std::cout << "int vs int" << std::endl;
    return *a == *b;
  }

  bool operator()(const std::unique_ptr<double> &a,
                  const std::unique_ptr<double> &b) const {
    std::cout << "double vs double" << std::endl;
    return *a == *b;
  }

  bool operator()(const std::unique_ptr<S> &a,
                  const std::unique_ptr<S> &b) const {
    std::cout << "S vs S" << std::endl;
    return a->a == b->a && a->b == b->b;
  }

  bool operator()(const std::unique_ptr<R<int>> &a,
                  const std::unique_ptr<R<int>> &b) const {
    std::cout << "R<int> vs R<int>" << std::endl;
    return a->a == b->a;
  }

  bool operator()(const std::unique_ptr<R<double>> &a,
                  const std::unique_ptr<R<double>> &b) const {
    std::cout << "R<double> vs R<double>" << std::endl;
    return a->a == b->a;
  }

  bool operator()(const std::unique_ptr<A> &a,
                  const std::unique_ptr<A> &b) const {
    std::cout << "A vs A" << std::endl;
    return std::visit(*this, a->v, b->v);
  }

  bool operator()(const std::unique_ptr<B> &a,
                  const std::unique_ptr<B> &b) const {
    std::cout << "A vs A" << std::endl;
    return std::visit(*this, a->a, b->a) && std::visit(*this, a->b, a->b);
  }

  template <typename T1, typename T2>
  bool operator()(const T1 &, const T2 &) const {
    std::cout << "type mismatch" << std::endl;
    return false;
  }
};

int main() {
  Variant v1(std::make_unique<int>(42)), v3(std::make_unique<double>(4.2)),
      v2(std::make_unique<S>(S{1, false})),
      v4(std::make_unique<R<int>>(R<int>{42})), v5(42);
  Visitor visitor;
  std::cout << std::visit(visitor, v1, v1) << std::endl;
  std::cout << std::visit(visitor, v2, v2) << std::endl;
  std::cout << std::visit(visitor, v3, v3) << std::endl;
  std::cout << std::visit(visitor, v3, v4) << std::endl;
  std::cout << std::visit(visitor, v2, v4) << std::endl;
  std::cout << std::visit(visitor, v5, v5) << std::endl;
  std::cout << std::visit(visitor, v4, v5) << std::endl;
  return 0;
}
