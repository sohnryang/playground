#include "gmock/gmock.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <cstdint>

#include "kernels.h"

using namespace testing;

TEST(Stride2FP32, Constants) {
  constexpr int LEN = 47;
  float inputs[LEN];
  std::fill_n(inputs, LEN, 1.0f);

  float scalar_out[LEN], avx512_out[LEN];
  std::copy_n(inputs, LEN, scalar_out);
  std::copy_n(inputs, LEN, avx512_out);
  kernel_scalar<float, 2>(scalar_out, LEN);
  kernel_avx512<float, 2>(avx512_out, LEN);

  EXPECT_THAT(avx512_out, Pointwise(FloatEq(), scalar_out));
}

TEST(Stride2Int32, Ones) {
  constexpr int LEN = 47;
  uint32_t inputs[LEN];
  std::fill_n(inputs, LEN, 1);

  uint32_t scalar_out[LEN], avx512_out[LEN];
  std::copy_n(inputs, LEN, scalar_out);
  std::copy_n(inputs, LEN, avx512_out);
  kernel_scalar<uint32_t, 2>(scalar_out, LEN);
  kernel_avx512<uint32_t, 2>(avx512_out, LEN);

  EXPECT_THAT(avx512_out, ContainerEq(scalar_out));
}

TEST(Stride3FP32, Ones) {
  constexpr int LEN = 47;
  float inputs[LEN];
  std::fill_n(inputs, LEN, 1.0f);

  float scalar_out[LEN], avx512_out[LEN];
  std::copy_n(inputs, LEN, scalar_out);
  std::copy_n(inputs, LEN, avx512_out);
  kernel_scalar<float, 3>(scalar_out, LEN);
  kernel_avx512<float, 3>(avx512_out, LEN);

  EXPECT_THAT(avx512_out, Pointwise(FloatEq(), scalar_out));
}

TEST(Stride3FP32, Alternating2) {
  constexpr int LEN = 47;
  float inputs[LEN];
  for (int i = 0; i < LEN; i++)
    inputs[i] = i % 2 + 1;

  float scalar_out[LEN], avx512_out[LEN];
  std::copy_n(inputs, LEN, scalar_out);
  std::copy_n(inputs, LEN, avx512_out);
  kernel_scalar<float, 3>(scalar_out, LEN);
  kernel_avx512<float, 3>(avx512_out, LEN);

  EXPECT_THAT(avx512_out, Pointwise(FloatEq(), scalar_out));
}

TEST(Stride3FP32, Alternating3) {
  constexpr int LEN = 47;
  float inputs[LEN];
  for (int i = 0; i < LEN; i++)
    inputs[i] = i % 3 + 1;

  float scalar_out[LEN], avx512_out[LEN];
  std::copy_n(inputs, LEN, scalar_out);
  std::copy_n(inputs, LEN, avx512_out);
  kernel_scalar<float, 3>(scalar_out, LEN);
  kernel_avx512<float, 3>(avx512_out, LEN);

  EXPECT_THAT(avx512_out, Pointwise(FloatEq(), scalar_out));
}

TEST(Stride3FP32, Alternating5) {
  constexpr int LEN = 47;
  float inputs[LEN];
  for (int i = 0; i < LEN; i++)
    inputs[i] = i % 5 + 1;

  float scalar_out[LEN], avx512_out[LEN];
  std::copy_n(inputs, LEN, scalar_out);
  std::copy_n(inputs, LEN, avx512_out);
  kernel_scalar<float, 3>(scalar_out, LEN);
  kernel_avx512<float, 3>(avx512_out, LEN);

  EXPECT_THAT(avx512_out, Pointwise(FloatEq(), scalar_out));
}

TEST(Stride3Int32, Ones) {
  constexpr int LEN = 47;
  uint32_t inputs[LEN];
  std::fill_n(inputs, LEN, 1);

  uint32_t scalar_out[LEN], avx512_out[LEN];
  std::copy_n(inputs, LEN, scalar_out);
  std::copy_n(inputs, LEN, avx512_out);
  kernel_scalar<uint32_t, 3>(scalar_out, LEN);
  kernel_avx512<uint32_t, 3>(avx512_out, LEN);

  EXPECT_THAT(avx512_out, ContainerEq(scalar_out));
}

TEST(Stride3Int32, Alternating2) {
  constexpr int LEN = 47;
  uint32_t inputs[LEN];
  for (int i = 0; i < LEN; i++)
    inputs[i] = i % 2 + 1;

  uint32_t scalar_out[LEN], avx512_out[LEN];
  std::copy_n(inputs, LEN, scalar_out);
  std::copy_n(inputs, LEN, avx512_out);
  kernel_scalar<uint32_t, 3>(scalar_out, LEN);
  kernel_avx512<uint32_t, 3>(avx512_out, LEN);

  EXPECT_THAT(avx512_out, ContainerEq(scalar_out));
}

TEST(Stride3Int32, Alternating3) {
  constexpr int LEN = 47;
  uint32_t inputs[LEN];
  for (int i = 0; i < LEN; i++)
    inputs[i] = i % 3 + 1;

  uint32_t scalar_out[LEN], avx512_out[LEN];
  std::copy_n(inputs, LEN, scalar_out);
  std::copy_n(inputs, LEN, avx512_out);
  kernel_scalar<uint32_t, 3>(scalar_out, LEN);
  kernel_avx512<uint32_t, 3>(avx512_out, LEN);

  EXPECT_THAT(avx512_out, ContainerEq(scalar_out));
}

TEST(Stride3Int32, Alternating5) {
  constexpr int LEN = 47;
  uint32_t inputs[LEN];
  for (int i = 0; i < LEN; i++)
    inputs[i] = i % 5 + 1;

  uint32_t scalar_out[LEN], avx512_out[LEN];
  std::copy_n(inputs, LEN, scalar_out);
  std::copy_n(inputs, LEN, avx512_out);
  kernel_scalar<uint32_t, 3>(scalar_out, LEN);
  kernel_avx512<uint32_t, 3>(avx512_out, LEN);

  EXPECT_THAT(avx512_out, ContainerEq(scalar_out));
}

TEST(Stride4FP32, Ones) {
  constexpr int LEN = 47;
  float inputs[LEN];
  std::fill_n(inputs, LEN, 1.0f);

  float scalar_out[LEN], avx512_out[LEN];
  std::copy_n(inputs, LEN, scalar_out);
  std::copy_n(inputs, LEN, avx512_out);
  kernel_scalar<float, 4>(scalar_out, LEN);
  kernel_avx512<float, 4>(avx512_out, LEN);

  EXPECT_THAT(avx512_out, Pointwise(FloatEq(), scalar_out));
}

TEST(Stride4FP32, Alternating2) {
  constexpr int LEN = 47;
  float inputs[LEN];
  for (int i = 0; i < LEN; i++)
    inputs[i] = i % 2 + 1;

  float scalar_out[LEN], avx512_out[LEN];
  std::copy_n(inputs, LEN, scalar_out);
  std::copy_n(inputs, LEN, avx512_out);
  kernel_scalar<float, 4>(scalar_out, LEN);
  kernel_avx512<float, 4>(avx512_out, LEN);

  EXPECT_THAT(avx512_out, Pointwise(FloatEq(), scalar_out));
}

TEST(Stride4FP32, Alternating3) {
  constexpr int LEN = 47;
  float inputs[LEN];
  for (int i = 0; i < LEN; i++)
    inputs[i] = i % 3 + 1;

  float scalar_out[LEN], avx512_out[LEN];
  std::copy_n(inputs, LEN, scalar_out);
  std::copy_n(inputs, LEN, avx512_out);
  kernel_scalar<float, 4>(scalar_out, LEN);
  kernel_avx512<float, 4>(avx512_out, LEN);

  EXPECT_THAT(avx512_out, Pointwise(FloatEq(), scalar_out));
}

TEST(Stride4FP32, Alternating5) {
  constexpr int LEN = 47;
  float inputs[LEN];
  for (int i = 0; i < LEN; i++)
    inputs[i] = i % 5 + 1;

  float scalar_out[LEN], avx512_out[LEN];
  std::copy_n(inputs, LEN, scalar_out);
  std::copy_n(inputs, LEN, avx512_out);
  kernel_scalar<float, 4>(scalar_out, LEN);
  kernel_avx512<float, 4>(avx512_out, LEN);

  EXPECT_THAT(avx512_out, Pointwise(FloatEq(), scalar_out));
}

TEST(Stride4Int32, Ones) {
  constexpr int LEN = 47;
  uint32_t inputs[LEN];
  std::fill_n(inputs, LEN, 1);

  uint32_t scalar_out[LEN], avx512_out[LEN];
  std::copy_n(inputs, LEN, scalar_out);
  std::copy_n(inputs, LEN, avx512_out);
  kernel_scalar<uint32_t, 4>(scalar_out, LEN);
  kernel_avx512<uint32_t, 4>(avx512_out, LEN);

  EXPECT_THAT(avx512_out, ContainerEq(scalar_out));
}

TEST(Stride4Int32, Alternating2) {
  constexpr int LEN = 47;
  uint32_t inputs[LEN];
  for (int i = 0; i < LEN; i++)
    inputs[i] = i % 2 + 1;

  uint32_t scalar_out[LEN], avx512_out[LEN];
  std::copy_n(inputs, LEN, scalar_out);
  std::copy_n(inputs, LEN, avx512_out);
  kernel_scalar<uint32_t, 4>(scalar_out, LEN);
  kernel_avx512<uint32_t, 4>(avx512_out, LEN);

  EXPECT_THAT(avx512_out, ContainerEq(scalar_out));
}

TEST(Stride4Int32, Alternating3) {
  constexpr int LEN = 47;
  uint32_t inputs[LEN];
  for (int i = 0; i < LEN; i++)
    inputs[i] = i % 3 + 1;

  uint32_t scalar_out[LEN], avx512_out[LEN];
  std::copy_n(inputs, LEN, scalar_out);
  std::copy_n(inputs, LEN, avx512_out);
  kernel_scalar<uint32_t, 4>(scalar_out, LEN);
  kernel_avx512<uint32_t, 4>(avx512_out, LEN);

  EXPECT_THAT(avx512_out, ContainerEq(scalar_out));
}

TEST(Stride4Int32, Alternating5) {
  constexpr int LEN = 47;
  uint32_t inputs[LEN];
  for (int i = 0; i < LEN; i++)
    inputs[i] = i % 5 + 1;

  uint32_t scalar_out[LEN], avx512_out[LEN];
  std::copy_n(inputs, LEN, scalar_out);
  std::copy_n(inputs, LEN, avx512_out);
  kernel_scalar<uint32_t, 4>(scalar_out, LEN);
  kernel_avx512<uint32_t, 4>(avx512_out, LEN);

  EXPECT_THAT(avx512_out, ContainerEq(scalar_out));
}
