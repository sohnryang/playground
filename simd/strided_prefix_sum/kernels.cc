#include "kernels.h"

#include <array>
#include <cstdint>
#include <type_traits>

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
template void kernel_scalar<float, 6>(float *arr, int n);
template void kernel_scalar<float, 7>(float *arr, int n);
template void kernel_scalar<float, 8>(float *arr, int n);
template void kernel_scalar<float, 9>(float *arr, int n);
template void kernel_scalar<float, 10>(float *arr, int n);
template void kernel_scalar<float, 11>(float *arr, int n);
template void kernel_scalar<float, 12>(float *arr, int n);
template void kernel_scalar<float, 13>(float *arr, int n);
template void kernel_scalar<float, 14>(float *arr, int n);
template void kernel_scalar<float, 15>(float *arr, int n);
template void kernel_scalar<uint32_t, 2>(uint32_t *arr, int n);
template void kernel_scalar<uint32_t, 3>(uint32_t *arr, int n);
template void kernel_scalar<uint32_t, 4>(uint32_t *arr, int n);
template void kernel_scalar<uint32_t, 5>(uint32_t *arr, int n);
template void kernel_scalar<uint32_t, 6>(uint32_t *arr, int n);
template void kernel_scalar<uint32_t, 7>(uint32_t *arr, int n);
template void kernel_scalar<uint32_t, 8>(uint32_t *arr, int n);
template void kernel_scalar<uint32_t, 9>(uint32_t *arr, int n);
template void kernel_scalar<uint32_t, 10>(uint32_t *arr, int n);
template void kernel_scalar<uint32_t, 11>(uint32_t *arr, int n);
template void kernel_scalar<uint32_t, 12>(uint32_t *arr, int n);
template void kernel_scalar<uint32_t, 13>(uint32_t *arr, int n);
template void kernel_scalar<uint32_t, 14>(uint32_t *arr, int n);
template void kernel_scalar<uint32_t, 15>(uint32_t *arr, int n);

template <typename T, int S> void kernel_autovec(T *arr, int n) {
#pragma clang loop vectorize(enable)
  for (int i = S; i < n; i++)
    arr[i] += arr[i - S];
}

template void kernel_autovec<float, 2>(float *arr, int n);
template void kernel_autovec<float, 4>(float *arr, int n);
template void kernel_autovec<float, 6>(float *arr, int n);
template void kernel_autovec<float, 8>(float *arr, int n);
template void kernel_autovec<float, 10>(float *arr, int n);
template void kernel_autovec<float, 12>(float *arr, int n);
template void kernel_autovec<float, 14>(float *arr, int n);
template void kernel_autovec<uint32_t, 2>(uint32_t *arr, int n);
template void kernel_autovec<uint32_t, 4>(uint32_t *arr, int n);
template void kernel_autovec<uint32_t, 6>(uint32_t *arr, int n);
template void kernel_autovec<uint32_t, 8>(uint32_t *arr, int n);
template void kernel_autovec<uint32_t, 10>(uint32_t *arr, int n);
template void kernel_autovec<uint32_t, 12>(uint32_t *arr, int n);
template void kernel_autovec<uint32_t, 14>(uint32_t *arr, int n);

alignas(64) constexpr std::array<int, 16 * 14> INDEX_TABLE = []() {
  std::array<int, 16 * 14> arr{};
  for (int i = 0; i < 14; i++)
    for (int j = 0; j < 16; j++) {
      int stride = i + 2;
      arr[16 * i + j] = j % stride + 16 - stride;
    }
  return arr;
}();

template <typename T, int S> void kernel_avx512(T *arr, int n) {
  int i = 0;
  const __m512i IDX = _mm512_load_epi32(INDEX_TABLE.data() + (S - 2) * 16);
  if constexpr (std::is_same<T, float>::value) {
    __m512 last_x = _mm512_setzero_ps();
    const __m512 ZERO_PS = _mm512_setzero_ps();
    for (; i + 16 <= n; i += 16) {
      __m512 x = _mm512_loadu_ps(&arr[i]);
      if constexpr (S < 4) {
        x = _mm512_add_ps(x, _mm512_alignr_epi32(x, ZERO_PS, 16 - S));
        x = _mm512_add_ps(x, _mm512_alignr_epi32(x, ZERO_PS, 16 - 2 * S));
        x = _mm512_add_ps(x, _mm512_alignr_epi32(x, ZERO_PS, 16 - 4 * S));
      } else if constexpr (S < 8) {
        x = _mm512_add_ps(x, _mm512_alignr_epi32(x, ZERO_PS, 16 - S));
        x = _mm512_add_ps(x, _mm512_alignr_epi32(x, ZERO_PS, 16 - 2 * S));
      } else {
        x = _mm512_add_ps(x, _mm512_alignr_epi32(x, ZERO_PS, 16 - S));
      }
      const __m512 carry = _mm512_permutexvar_ps(IDX, last_x);
      x = _mm512_add_ps(carry, x);
      _mm512_storeu_ps(&arr[i], x);
      last_x = x;
    }
  } else if constexpr (std::is_same<T, uint32_t>::value) {
    __m512i last_x = _mm512_setzero_epi32();
    const __m512i ZERO_EPI32 = _mm512_setzero_epi32();
    for (; i + 16 <= n; i += 16) {
      __m512i x = _mm512_loadu_epi32(&arr[i]);
      if constexpr (S < 4) {
        x = _mm512_add_epi32(x, _mm512_alignr_epi32(x, ZERO_EPI32, 16 - S));
        x = _mm512_add_epi32(x, _mm512_alignr_epi32(x, ZERO_EPI32, 16 - 2 * S));
        x = _mm512_add_epi32(x, _mm512_alignr_epi32(x, ZERO_EPI32, 16 - 4 * S));
      } else if constexpr (S < 8) {
        x = _mm512_add_epi32(x, _mm512_alignr_epi32(x, ZERO_EPI32, 16 - S));
        x = _mm512_add_epi32(x, _mm512_alignr_epi32(x, ZERO_EPI32, 16 - 2 * S));
      } else {
        x = _mm512_add_epi32(x, _mm512_alignr_epi32(x, ZERO_EPI32, 16 - S));
      }
      const __m512i carry = _mm512_permutexvar_epi32(IDX, last_x);
      x = _mm512_add_epi32(carry, x);
      _mm512_storeu_epi32(&arr[i], x);
      last_x = x;
    }
  }

  for (i = i ? i : S; i < n; i++)
    arr[i] += arr[i - S];
}

template void kernel_avx512<float, 2>(float *arr, int n);
template void kernel_avx512<float, 3>(float *arr, int n);
template void kernel_avx512<float, 4>(float *arr, int n);
template void kernel_avx512<float, 5>(float *arr, int n);
template void kernel_avx512<float, 6>(float *arr, int n);
template void kernel_avx512<float, 7>(float *arr, int n);
template void kernel_avx512<float, 8>(float *arr, int n);
template void kernel_avx512<float, 9>(float *arr, int n);
template void kernel_avx512<float, 10>(float *arr, int n);
template void kernel_avx512<float, 11>(float *arr, int n);
template void kernel_avx512<float, 12>(float *arr, int n);
template void kernel_avx512<float, 13>(float *arr, int n);
template void kernel_avx512<float, 14>(float *arr, int n);
template void kernel_avx512<float, 15>(float *arr, int n);
template void kernel_avx512<uint32_t, 2>(uint32_t *arr, int n);
template void kernel_avx512<uint32_t, 3>(uint32_t *arr, int n);
template void kernel_avx512<uint32_t, 4>(uint32_t *arr, int n);
template void kernel_avx512<uint32_t, 5>(uint32_t *arr, int n);
template void kernel_avx512<uint32_t, 6>(uint32_t *arr, int n);
template void kernel_avx512<uint32_t, 7>(uint32_t *arr, int n);
template void kernel_avx512<uint32_t, 8>(uint32_t *arr, int n);
template void kernel_avx512<uint32_t, 9>(uint32_t *arr, int n);
template void kernel_avx512<uint32_t, 10>(uint32_t *arr, int n);
template void kernel_avx512<uint32_t, 11>(uint32_t *arr, int n);
template void kernel_avx512<uint32_t, 12>(uint32_t *arr, int n);
template void kernel_avx512<uint32_t, 13>(uint32_t *arr, int n);
template void kernel_avx512<uint32_t, 14>(uint32_t *arr, int n);
template void kernel_avx512<uint32_t, 15>(uint32_t *arr, int n);
