#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <cstdint>
#include <tuple>
#include <type_traits>

#include "kernels.h"

using namespace testing;

template <typename Types> class StridedPsumTest : public Test {};

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
  using S = std::tuple_element_t<1, decltype(TypeParam())>;

  constexpr int LEN = 47;
  T inputs[LEN];
  std::fill_n(inputs, LEN, 1);

  T scalar_out[LEN], avx512_out[LEN];
  std::copy_n(inputs, LEN, scalar_out);
  std::copy_n(inputs, LEN, avx512_out);
  kernel_scalar<T, S::value>(scalar_out, LEN);
  kernel_avx512<T, S::value>(avx512_out, LEN);

  EXPECT_THAT(avx512_out, Pointwise(FloatEq(), scalar_out));
}

TYPED_TEST(StridedPsumTest, Alternating2) {
  using T = std::tuple_element_t<0, decltype(TypeParam())>;
  using S = std::tuple_element_t<1, decltype(TypeParam())>;

  constexpr int LEN = 47;
  T inputs[LEN];
  for (int i = 0; i < LEN; i++)
    inputs[i] = i % 2 + 1;

  T scalar_out[LEN], avx512_out[LEN];
  std::copy_n(inputs, LEN, scalar_out);
  std::copy_n(inputs, LEN, avx512_out);
  kernel_scalar<T, S::value>(scalar_out, LEN);
  kernel_avx512<T, S::value>(avx512_out, LEN);

  EXPECT_THAT(avx512_out, Pointwise(FloatEq(), scalar_out));
}

TYPED_TEST(StridedPsumTest, Alternating3) {
  using T = std::tuple_element_t<0, decltype(TypeParam())>;
  using S = std::tuple_element_t<1, decltype(TypeParam())>;

  constexpr int LEN = 47;
  T inputs[LEN];
  for (int i = 0; i < LEN; i++)
    inputs[i] = i % 3 + 1;

  T scalar_out[LEN], avx512_out[LEN];
  std::copy_n(inputs, LEN, scalar_out);
  std::copy_n(inputs, LEN, avx512_out);
  kernel_scalar<T, S::value>(scalar_out, LEN);
  kernel_avx512<T, S::value>(avx512_out, LEN);

  EXPECT_THAT(avx512_out, Pointwise(FloatEq(), scalar_out));
}

TYPED_TEST(StridedPsumTest, Alternating5) {
  using T = std::tuple_element_t<0, decltype(TypeParam())>;
  using S = std::tuple_element_t<1, decltype(TypeParam())>;

  constexpr int LEN = 47;
  T inputs[LEN];
  for (int i = 0; i < LEN; i++)
    inputs[i] = i % 5 + 1;

  T scalar_out[LEN], avx512_out[LEN];
  std::copy_n(inputs, LEN, scalar_out);
  std::copy_n(inputs, LEN, avx512_out);
  kernel_scalar<T, S::value>(scalar_out, LEN);
  kernel_avx512<T, S::value>(avx512_out, LEN);

  EXPECT_THAT(avx512_out, Pointwise(FloatEq(), scalar_out));
}

TYPED_TEST(StridedPsumTest, Alternating7) {
  using T = std::tuple_element_t<0, decltype(TypeParam())>;
  using S = std::tuple_element_t<1, decltype(TypeParam())>;

  constexpr int LEN = 47;
  T inputs[LEN];
  for (int i = 0; i < LEN; i++)
    inputs[i] = i % 7 + 1;

  T scalar_out[LEN], avx512_out[LEN];
  std::copy_n(inputs, LEN, scalar_out);
  std::copy_n(inputs, LEN, avx512_out);
  kernel_scalar<T, S::value>(scalar_out, LEN);
  kernel_avx512<T, S::value>(avx512_out, LEN);

  EXPECT_THAT(avx512_out, Pointwise(FloatEq(), scalar_out));
}
