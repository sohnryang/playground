#include <cstddef>
#include <iostream>
#include <unordered_map>

template <std::size_t i, class T> struct TupleMapLeaf {
  std::unordered_map<std::size_t, T> m;
};

template <std::size_t i, class... Types> struct TupleMapImpl;

template <std::size_t i> struct TupleMapImpl<i> {};

template <std::size_t i, class Head, class... Tail>
struct TupleMapImpl<i, Head, Tail...> : public TupleMapLeaf<i, Head>,
                                        public TupleMapImpl<i + 1, Tail...> {};

template <std::size_t i, class Head, class... Tail>
std::unordered_map<std::size_t, Head> &
get(TupleMapImpl<i, Head, Tail...> &tuple_map) {
  return tuple_map.TupleMapLeaf<i, Head>::m;
}

template <class... Types> using TupleMap = TupleMapImpl<0, Types...>;

int main() {
  TupleMap<int, bool, char> t;
  get<0>(t)[0] = 42;
  std::cout << get<0>(t)[0] << std::endl;
}
