#include <cstddef>
#include <iostream>

struct A {
  int x;
  int y;
};

struct B {
  bool flag;
  char ch;
};

template <class... Types> struct TypeIndex {};

template <class T, class TypeIndex> struct TypeIndexer;

template <class T, class... Types>
struct TypeIndexer<T, TypeIndex<T, Types...>> {
  static constexpr std::size_t index = 0;
};

template <class T, class U, class... Types>
struct TypeIndexer<T, TypeIndex<U, Types...>> {
  static constexpr std::size_t index =
      1 + TypeIndexer<T, TypeIndex<Types...>>::index;
};

int main() {
  std::cout << TypeIndexer<int, TypeIndex<int, A, B>>::index << std::endl;
  std::cout << TypeIndexer<B, TypeIndex<int, A, B>>::index << std::endl;
}
