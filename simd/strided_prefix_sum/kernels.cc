#include "kernels.h"

#include <cstdint>

#include <immintrin.h>

template <typename T, int S> void kernel_scalar(T *arr, int n) {
#pragma clang loop vectorize(disable)
  for (int i = S; i < n; i++)
    arr[i] += arr[i - S];
}

template void kernel_scalar<float, 2>(float *arr, int n);
template void kernel_scalar<float, 3>(float *arr, int n);
template void kernel_scalar<float, 4>(float *arr, int n);
template void kernel_scalar<float, 5>(float *arr, int n);
template void kernel_scalar<uint32_t, 2>(uint32_t *arr, int n);
template void kernel_scalar<uint32_t, 3>(uint32_t *arr, int n);
template void kernel_scalar<uint32_t, 4>(uint32_t *arr, int n);
template void kernel_scalar<uint32_t, 5>(uint32_t *arr, int n);

template <typename T, int S> void kernel_autovec(T *arr, int n) {
#pragma clang loop vectorize(enable)
  for (int i = S; i < n; i++)
    arr[i] += arr[i - S];
}

template void kernel_autovec<float, 2>(float *arr, int n);
template void kernel_autovec<float, 4>(float *arr, int n);
template void kernel_autovec<uint32_t, 2>(uint32_t *arr, int n);
template void kernel_autovec<uint32_t, 4>(uint32_t *arr, int n);

template <> void kernel_avx512<float, 2>(float *arr, int n) {
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

template <> void kernel_avx512<float, 3>(float *arr, int n) {
  __m128 last_part = _mm_setzero_ps();
  int i;
  const __m512 ZERO_PS = _mm512_setzero_ps();
  const __m128i IDX0 = _mm_set_epi32(1, 3, 2, 1);
  const __m128i IDX1 = _mm_set_epi32(2, 1, 3, 2);
  const __m128i IDX2 = _mm_set_epi32(3, 2, 1, 3);
  for (i = 0; i + 16 <= n; i += 16) {
    __m512 x = _mm512_loadu_ps(&arr[i]);
    x = _mm512_add_ps(x, _mm512_alignr_epi32(x, ZERO_PS, 16 - 3));
    x = _mm512_add_ps(x, _mm512_alignr_epi32(x, ZERO_PS, 16 - 6));
    x = _mm512_add_ps(x, _mm512_alignr_epi32(x, ZERO_PS, 16 - 12));

    const __m128 carry_low0 = _mm_permutevar_ps(last_part, IDX0);
    const __m128 carry_low1 = _mm_permutevar_ps(last_part, IDX1);
    const __m128 carry_high0 = _mm_permutevar_ps(last_part, IDX2);
    const __m128 carry_high1 = carry_low0;
    const __m256 carry_low =
        _mm256_insertf32x4(_mm256_castps128_ps256(carry_low0), carry_low1, 1);
    const __m256 carry_high =
        _mm256_insertf32x4(_mm256_castps128_ps256(carry_high0), carry_high1, 1);
    const __m512 carry =
        _mm512_insertf32x8(_mm512_castps256_ps512(carry_low), carry_high, 1);
    x = _mm512_add_ps(carry, x);
    _mm512_storeu_ps(&arr[i], x);
    last_part = _mm512_extractf32x4_ps(x, 3);
  }

  for (i = i ? i : 3; i < n; i++)
    arr[i] += arr[i - 3];
}

template <> void kernel_avx512<float, 4>(float *arr, int n) {
  __m128 last_part = _mm_setzero_ps();
  int i;
  const __m512 ZERO_PS = _mm512_setzero_ps();
  for (i = 0; i + 16 <= n; i += 16) {
    __m512 x = _mm512_loadu_ps(&arr[i]);
    x = _mm512_add_ps(x, _mm512_alignr_epi32(x, ZERO_PS, 16 - 4));
    x = _mm512_add_ps(x, _mm512_alignr_epi32(x, ZERO_PS, 16 - 8));

    x = _mm512_add_ps(_mm512_broadcast_f32x4(last_part), x);
    _mm512_storeu_ps(&arr[i], x);
    last_part = _mm512_extractf32x4_ps(x, 3);
  }

  for (i = i ? i : 4; i < n; i++)
    arr[i] += arr[i - 4];
}

template <> void kernel_avx512<float, 5>(float *arr, int n) {
  __m256 last_part = _mm256_setzero_ps();
  int i;
  const __m512 ZERO_PS = _mm512_setzero_ps();
  const __m512i IDX =
      _mm512_set_epi32(3, 7, 6, 5, 4, 3, 7, 6, 5, 4, 3, 7, 6, 5, 4, 3);
  for (i = 0; i + 16 <= n; i += 16) {
    __m512 x = _mm512_loadu_ps(&arr[i]);
    x = _mm512_add_ps(x, _mm512_alignr_epi32(x, ZERO_PS, 16 - 5));
    x = _mm512_add_ps(x, _mm512_alignr_epi32(x, ZERO_PS, 16 - 10));
    const __m512 carry =
        _mm512_permutexvar_ps(IDX, _mm512_castps256_ps512(last_part));
    x = _mm512_add_ps(carry, x);
    _mm512_storeu_ps(&arr[i], x);
    last_part = _mm512_extractf32x8_ps(x, 1);
  }

  for (i = i ? i : 5; i < n; i++)
    arr[i] += arr[i - 5];
}

template <> void kernel_avx512<uint32_t, 2>(uint32_t *arr, int n) {
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

template <> void kernel_avx512<uint32_t, 3>(uint32_t *arr, int n) {
  __m128i last_part = _mm_setzero_ps();
  int i;
  const __m512i ZERO_EPI32 = _mm512_setzero_epi32();
  const __m128i IDX0 = _mm_set_epi32(1, 3, 2, 1);
  const __m128i IDX1 = _mm_set_epi32(2, 1, 3, 2);
  const __m128i IDX2 = _mm_set_epi32(3, 2, 1, 3);
  for (i = 0; i + 16 <= n; i += 16) {
    __m512i x = _mm512_loadu_epi32(&arr[i]);
    x = _mm512_add_epi32(x, _mm512_alignr_epi32(x, ZERO_EPI32, 16 - 3));
    x = _mm512_add_epi32(x, _mm512_alignr_epi32(x, ZERO_EPI32, 16 - 6));
    x = _mm512_add_epi32(x, _mm512_alignr_epi32(x, ZERO_EPI32, 16 - 12));

    const __m128i carry_low0 = _mm_permutevar_ps(last_part, IDX0);
    const __m128i carry_low1 = _mm_permutevar_ps(last_part, IDX1);
    const __m128i carry_high0 = _mm_permutevar_ps(last_part, IDX2);
    const __m128i carry_high1 = carry_low0;
    const __m256i carry_low =
        _mm256_inserti32x4(_mm256_castsi128_si256(carry_low0), carry_low1, 1);
    const __m256i carry_high =
        _mm256_inserti32x4(_mm256_castsi128_si256(carry_high0), carry_high1, 1);
    const __m512i carry =
        _mm512_inserti32x8(_mm512_castsi256_si512(carry_low), carry_high, 1);
    x = _mm512_add_epi32(carry, x);
    _mm512_storeu_epi32(&arr[i], x);
    last_part = _mm512_extracti32x4_epi32(x, 3);
  }

  for (i = i ? i : 3; i < n; i++)
    arr[i] += arr[i - 3];
}

template <> void kernel_avx512<uint32_t, 4>(uint32_t *arr, int n) {
  __m128i last_part = _mm_setzero_ps();
  int i;
  const __m512i ZERO_EPI32 = _mm512_setzero_epi32();
  for (i = 0; i + 16 <= n; i += 16) {
    __m512i x = _mm512_loadu_epi32(&arr[i]);
    x = _mm512_add_epi32(x, _mm512_alignr_epi32(x, ZERO_EPI32, 16 - 4));
    x = _mm512_add_epi32(x, _mm512_alignr_epi32(x, ZERO_EPI32, 16 - 8));

    x = _mm512_add_epi32(_mm512_broadcast_f32x4(last_part), x);
    _mm512_storeu_epi32(&arr[i], x);
    last_part = _mm512_extracti32x4_epi32(x, 3);
  }

  for (i = i ? i : 4; i < n; i++)
    arr[i] += arr[i - 4];
}

template <> void kernel_avx512<uint32_t, 5>(uint32_t *arr, int n) {
  __m256i last_part = _mm256_setzero_si256();
  int i;
  const __m512i ZERO_EPI32 = _mm512_setzero_epi32();
  const __m512i IDX =
      _mm512_set_epi32(3, 7, 6, 5, 4, 3, 7, 6, 5, 4, 3, 7, 6, 5, 4, 3);
  for (i = 0; i + 16 <= n; i += 16) {
    __m512i x = _mm512_loadu_epi32(&arr[i]);
    x = _mm512_add_epi32(x, _mm512_alignr_epi32(x, ZERO_EPI32, 16 - 5));
    x = _mm512_add_epi32(x, _mm512_alignr_epi32(x, ZERO_EPI32, 16 - 10));
    const __m512i carry =
        _mm512_permutexvar_epi32(IDX, _mm512_castsi256_si512(last_part));
    x = _mm512_add_epi32(carry, x);
    _mm512_storeu_epi32(&arr[i], x);
    last_part = _mm512_extracti32x8_epi32(x, 1);
  }

  for (i = i ? i : 5; i < n; i++)
    arr[i] += arr[i - 5];
}
