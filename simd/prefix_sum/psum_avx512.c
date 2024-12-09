#include "prefix_sum.h"

#include <immintrin.h>

static inline __m512 prefix_sum_local(__m512 x) {
  const __m512 ZERO = _mm512_setzero_ps();
  x = _mm512_add_ps(x, _mm512_alignr_epi32(x, ZERO, 16 - 1));
  x = _mm512_add_ps(x, _mm512_alignr_epi32(x, ZERO, 16 - 2));
  x = _mm512_add_ps(x, _mm512_alignr_epi32(x, ZERO, 16 - 4));
  x = _mm512_add_ps(x, _mm512_alignr_epi32(x, ZERO, 16 - 8));
  return x;
}

void prefix_sum(float *arr, int n) {
  const int tripcount = n / 16 * 16;
  union {
    unsigned int u;
    float f;
  } carry;
  carry.f = 0;
  for (int i = 0; i < tripcount; i += 16) {
    const __m512 x = _mm512_load_ps(&arr[i]);
    const __m512 local_result = prefix_sum_local(x);
    const __m512 result = _mm512_add_ps(_mm512_set1_ps(carry.f), local_result);
    _mm512_store_ps(&arr[i], result);
    const __m128 part = _mm512_extractf32x4_ps(result, 3);
    carry.u = _mm_extract_ps(part, 3);
  }
  for (int i = tripcount ? tripcount : 1; i < n; i++)
    arr[i] += arr[i - 1];
}
