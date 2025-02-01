#include <benchmark/benchmark.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include <immintrin.h>

#include "kernels.h"

constexpr size_t MULTIPLIER = 4;
constexpr size_t RANGE_START = 1024;
constexpr size_t RANGE_END = 64 * 1024 * 1024;

template <typename T, int S> static void BM_scalar(benchmark::State &state) {
  T *arr = new T[state.range()];
  for (int i = 0; i < state.range(); i++)
    arr[i] = std::rand();

  for (auto _ : state) {
    kernel_scalar<T, S>(arr, state.range());
    benchmark::DoNotOptimize(arr);
    benchmark::ClobberMemory();
  }
  delete[] arr;
}
BENCHMARK(BM_scalar<float, 2>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM_scalar<float, 3>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM_scalar<float, 4>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM_scalar<uint32_t, 2>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM_scalar<uint32_t, 3>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM_scalar<uint32_t, 4>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);

template <typename T, int S> static void BM_autovec(benchmark::State &state) {
  T *arr = new T[state.range()];
  for (int i = 0; i < state.range(); i++)
    arr[i] = std::rand();

  for (auto _ : state) {
    kernel_autovec<T, S>(arr, state.range());
    benchmark::DoNotOptimize(arr);
    benchmark::ClobberMemory();
  }
  delete[] arr;
}
BENCHMARK(BM_autovec<float, 2>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM_autovec<float, 3>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM_autovec<float, 4>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM_autovec<uint32_t, 2>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM_autovec<uint32_t, 3>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM_autovec<uint32_t, 4>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);

template <typename T, int S> static void BM_avx512(benchmark::State &state) {
  T *arr = new T[state.range()];
  for (int i = 0; i < state.range(); i++)
    arr[i] = std::rand();

  for (auto _ : state) {
    kernel_avx512<T, S>(arr, state.range());
    benchmark::DoNotOptimize(arr);
    benchmark::ClobberMemory();
  }
  delete[] arr;
}
BENCHMARK(BM_avx512<float, 2>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM_avx512<float, 4>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM_avx512<uint32_t, 2>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);
BENCHMARK(BM_avx512<uint32_t, 4>)
    ->RangeMultiplier(MULTIPLIER)
    ->Range(RANGE_START, RANGE_END);

BENCHMARK_MAIN();
