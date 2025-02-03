#include <benchmark/benchmark.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include <immintrin.h>

#include "kernels.h"

constexpr size_t MULTIPLIER = 4;
constexpr size_t RANGE_START = 1024;
constexpr size_t RANGE_END = 64 * 1024 * 1024;

template <typename T, void (*F)(T *, int)>
static void BM(benchmark::State &state) {
  T *arr = new T[state.range()];
  for (int i = 0; i < state.range(); i++)
    arr[i] = std::rand();

  for (auto _ : state) {
    F(arr, state.range());
    benchmark::DoNotOptimize(arr);
    benchmark::ClobberMemory();
  }
  delete[] arr;
}
BENCHMARK(BM<float, kernel_scalar<float, 2>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<float, kernel_scalar<float, 3>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<float, kernel_scalar<float, 4>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<float, kernel_scalar<float, 5>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<float, kernel_scalar<float, 6>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<float, kernel_scalar<float, 7>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<float, kernel_scalar<float, 8>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<float, kernel_scalar<float, 9>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<float, kernel_scalar<float, 10>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<float, kernel_scalar<float, 11>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<float, kernel_scalar<float, 12>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<float, kernel_scalar<float, 13>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<float, kernel_scalar<float, 14>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<float, kernel_scalar<float, 15>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<uint32_t, kernel_scalar<uint32_t, 2>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<uint32_t, kernel_scalar<uint32_t, 3>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<uint32_t, kernel_scalar<uint32_t, 4>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<uint32_t, kernel_scalar<uint32_t, 5>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<uint32_t, kernel_scalar<uint32_t, 6>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<uint32_t, kernel_scalar<uint32_t, 7>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<uint32_t, kernel_scalar<uint32_t, 8>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<uint32_t, kernel_scalar<uint32_t, 9>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<uint32_t, kernel_scalar<uint32_t, 10>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<uint32_t, kernel_scalar<uint32_t, 11>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<uint32_t, kernel_scalar<uint32_t, 12>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<uint32_t, kernel_scalar<uint32_t, 13>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<uint32_t, kernel_scalar<uint32_t, 14>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<uint32_t, kernel_scalar<uint32_t, 15>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<float, kernel_autovec<float, 2>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<float, kernel_autovec<float, 4>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<float, kernel_autovec<float, 6>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<float, kernel_autovec<float, 8>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<float, kernel_autovec<float, 10>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<float, kernel_autovec<float, 12>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<float, kernel_autovec<float, 14>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<uint32_t, kernel_autovec<uint32_t, 2>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<uint32_t, kernel_autovec<uint32_t, 4>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<uint32_t, kernel_autovec<uint32_t, 6>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<uint32_t, kernel_autovec<uint32_t, 8>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<uint32_t, kernel_autovec<uint32_t, 10>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<uint32_t, kernel_autovec<uint32_t, 12>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<uint32_t, kernel_autovec<uint32_t, 14>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<float, kernel_avx512<float, 2>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<float, kernel_avx512<float, 3>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<float, kernel_avx512<float, 4>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<float, kernel_avx512<float, 5>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<float, kernel_avx512<float, 6>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<float, kernel_avx512<float, 7>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<float, kernel_avx512<float, 8>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<float, kernel_avx512<float, 9>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<float, kernel_avx512<float, 10>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<float, kernel_avx512<float, 11>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<float, kernel_avx512<float, 12>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<float, kernel_avx512<float, 13>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<float, kernel_avx512<float, 14>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<float, kernel_avx512<float, 15>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<uint32_t, kernel_avx512<uint32_t, 2>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<uint32_t, kernel_avx512<uint32_t, 3>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<uint32_t, kernel_avx512<uint32_t, 4>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<uint32_t, kernel_avx512<uint32_t, 5>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<uint32_t, kernel_avx512<uint32_t, 6>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<uint32_t, kernel_avx512<uint32_t, 7>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<uint32_t, kernel_avx512<uint32_t, 8>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<uint32_t, kernel_avx512<uint32_t, 9>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<uint32_t, kernel_avx512<uint32_t, 10>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<uint32_t, kernel_avx512<uint32_t, 11>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<uint32_t, kernel_avx512<uint32_t, 12>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<uint32_t, kernel_avx512<uint32_t, 13>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<uint32_t, kernel_avx512<uint32_t, 14>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM<uint32_t, kernel_avx512<uint32_t, 15>>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);

BENCHMARK_MAIN();
