#include <benchmark/benchmark.h>

#include <cstdint>
#include <cstdlib>

#include <immintrin.h>

void kernel_scalar_fp(float *arr, int n) {
#pragma loop vectorize(disable)
  for (int i = 2; i < n; i++)
    arr[i] += arr[i - 2];
}

static void BM_scalar_fp(benchmark::State &state) {
  float *arr = new float[state.range()];
  for (int i = 0; i < state.range(); i++)
    arr[i] = std::rand();

  for (auto _ : state) {
    kernel_scalar_fp(arr, state.range());
    benchmark::DoNotOptimize(arr);
    benchmark::ClobberMemory();
  }
  delete[] arr;
}
BENCHMARK(BM_scalar_fp)->RangeMultiplier(2)->Range(1024, 32 * 1024 * 1024);

void kernel_avx512_fp(float *arr, int n) {
  float sum0 = 0, sum1 = 0;
  int i;
  const __m512 ZERO_PS = _mm512_setzero_ps();
  for (i = 0; i + 16 <= n; i += 16) {
    __m512 x = _mm512_loadu_ps(&arr[i]);
    x = _mm512_add_ps(x, _mm512_alignr_epi32(x, ZERO_PS, 16 - 2));
    x = _mm512_add_ps(x, _mm512_alignr_epi32(x, ZERO_PS, 16 - 4));
    x = _mm512_add_ps(x, _mm512_alignr_epi32(x, ZERO_PS, 16 - 8));

    const __m512 sum0_broadcasted = _mm512_set1_ps(sum0);
    const __m512 sum1_broadcasted = _mm512_set1_ps(sum1);
    x = _mm512_add_ps(
        _mm512_mask_blend_ps(0xAAAA, sum0_broadcasted, sum1_broadcasted), x);
    _mm512_storeu_ps(&arr[i], x);

    const __m128 last_part = _mm512_extractf32x4_ps(x, 3);
    _MM_EXTRACT_FLOAT(sum0, last_part, 2);
    _MM_EXTRACT_FLOAT(sum1, last_part, 3);
  }

  for (i = i ? i : 2; i < n; i++)
    arr[i] += arr[i - 2];
}

static void BM_avx512_fp(benchmark::State &state) {
  float *arr = new float[state.range()];
  for (int i = 0; i < state.range(); i++)
    arr[i] = std::rand();

  for (auto _ : state) {
    kernel_avx512_fp(arr, state.range());
    benchmark::DoNotOptimize(arr);
    benchmark::ClobberMemory();
  }
  delete[] arr;
}
BENCHMARK(BM_avx512_fp)->RangeMultiplier(2)->Range(1024, 32 * 1024 * 1024);

void kernel_scalar_int(uint32_t *arr, int n) {
#pragma loop vectorize(disable)
  for (int i = 2; i < n; i++)
    arr[i] += arr[i - 2];
}

static void BM_scalar_int(benchmark::State &state) {
  uint32_t *arr = new uint32_t[state.range()];
  for (int i = 0; i < state.range(); i++)
    arr[i] = std::rand();

  for (auto _ : state) {
    kernel_scalar_int(arr, state.range());
    benchmark::DoNotOptimize(arr);
    benchmark::ClobberMemory();
  }
  delete[] arr;
}
BENCHMARK(BM_scalar_int)->RangeMultiplier(2)->Range(1024, 32 * 1024 * 1024);

void kernel_avx512_int(uint32_t *arr, int n) {
  uint32_t sum0 = 0, sum1 = 0;
  int i;
  const __m512i ZERO_EPI32 = _mm512_setzero_epi32();
  for (i = 0; i + 16 <= n; i += 16) {
    __m512i x = _mm512_loadu_epi32(&arr[i]);
    x = _mm512_add_epi32(x, _mm512_alignr_epi32(x, ZERO_EPI32, 16 - 2));
    x = _mm512_add_epi32(x, _mm512_alignr_epi32(x, ZERO_EPI32, 16 - 4));
    x = _mm512_add_epi32(x, _mm512_alignr_epi32(x, ZERO_EPI32, 16 - 8));

    const __m512i sum0_broadcasted = _mm512_set1_epi32(sum0);
    const __m512i sum1_broadcasted = _mm512_set1_epi32(sum1);
    x = _mm512_add_epi32(
        _mm512_mask_blend_epi32(0xAAAA, sum0_broadcasted, sum1_broadcasted), x);
    _mm512_storeu_epi32(&arr[i], x);

    const __m128i last_part = _mm512_extracti32x4_epi32(x, 3);
    sum0 = _mm_extract_epi32(last_part, 2);
    sum1 = _mm_extract_epi32(last_part, 3);
  }

  for (i = i ? i : 2; i < n; i++)
    arr[i] += arr[i - 2];
}

static void BM_avx512_int(benchmark::State &state) {
  uint32_t *arr = new uint32_t[state.range()];
  for (int i = 0; i < state.range(); i++)
    arr[i] = std::rand();

  for (auto _ : state) {
    kernel_avx512_int(arr, state.range());
    benchmark::DoNotOptimize(arr);
    benchmark::ClobberMemory();
  }
  delete[] arr;
}
BENCHMARK(BM_avx512_int)->RangeMultiplier(2)->Range(1024, 32 * 1024 * 1024);

BENCHMARK_MAIN();
