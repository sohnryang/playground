#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <cstdint>
#include <tuple>
#include <type_traits>

#include "kernels.h"

using namespace testing;

template <typename Types> class StridedPsumTest : public Test {
public:
  using T = std::tuple_element_t<0, Types>;
  using S = std::tuple_element_t<1, Types>;

  void copy_and_run(const T *input, T *scalar_out, T *avx512_out, int n) {
    std::copy_n(input, n, scalar_out);
    std::copy_n(input, n, avx512_out);
    kernel_scalar<T, S::value>(scalar_out, n);
    kernel_avx512<T, S::value>(avx512_out, n);
  }
};

using Implementations =
    Types<std::tuple<float, std::integral_constant<int, 2>>,
          std::tuple<float, std::integral_constant<int, 3>>,
          std::tuple<float, std::integral_constant<int, 4>>,
          std::tuple<float, std::integral_constant<int, 5>>,
          std::tuple<float, std::integral_constant<int, 6>>,
          std::tuple<uint32_t, std::integral_constant<int, 2>>,
          std::tuple<uint32_t, std::integral_constant<int, 3>>,
          std::tuple<uint32_t, std::integral_constant<int, 4>>,
          std::tuple<uint32_t, std::integral_constant<int, 5>>,
          std::tuple<uint32_t, std::integral_constant<int, 6>>>;
TYPED_TEST_SUITE(StridedPsumTest, Implementations);

TYPED_TEST(StridedPsumTest, Ones) {
  using T = std::tuple_element_t<0, decltype(TypeParam())>;
  constexpr int LEN = 47;
  T input[LEN], scalar_out[LEN], avx512_out[LEN];
  std::fill_n(input, LEN, 1);
  this->copy_and_run(input, scalar_out, avx512_out, LEN);
  EXPECT_THAT(avx512_out, Pointwise(FloatEq(), scalar_out));
}

TYPED_TEST(StridedPsumTest, Alternating) {
  using T = std::tuple_element_t<0, decltype(TypeParam())>;
  constexpr int LEN = 47;
  T input[LEN], scalar_out[LEN], avx512_out[LEN];
  for (int i = 0; i < LEN; i++)
    input[i] = i % 7 + 1;
  this->copy_and_run(input, scalar_out, avx512_out, LEN);
  EXPECT_THAT(avx512_out, Pointwise(FloatEq(), scalar_out));
}
