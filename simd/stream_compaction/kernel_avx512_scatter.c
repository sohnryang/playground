#include "kernel.h"

#include <immintrin.h>

static inline __m512i prefix_sum_local(__m512i x) {
  const __m512i ZERO = _mm512_setzero_epi32();
  x = _mm512_add_epi32(x, _mm512_alignr_epi32(x, ZERO, 16 - 1));
  x = _mm512_add_epi32(x, _mm512_alignr_epi32(x, ZERO, 16 - 2));
  x = _mm512_add_epi32(x, _mm512_alignr_epi32(x, ZERO, 16 - 4));
  x = _mm512_add_epi32(x, _mm512_alignr_epi32(x, ZERO, 16 - 8));
  return x;
}

int stream_compaction(const float *restrict in, float *restrict out, int n) {
  const int tripcount = n / 16 * 16;
  const __m512 CMP_SPLAT = _mm512_set1_ps(0.5f);
  const __m512i ONE = _mm512_set1_epi32(1);
  unsigned int carry = 0;
  for (int i = 0; i < tripcount; i += 16) {
    const __m512 x = _mm512_load_ps(&in[i]);
    const __mmask16 cmp_mask = _mm512_cmplt_ps_mask(CMP_SPLAT, x);
    const __m512i cmp_mask_int =
        _mm512_and_epi32(_mm512_movm_epi32(cmp_mask), ONE);
    const __m512i psum_local = prefix_sum_local(cmp_mask_int);
    const __m512i indices =
        _mm512_add_epi32(psum_local, _mm512_set1_epi32(carry - 1));
    _mm512_mask_i32scatter_ps(out, cmp_mask, indices, x, 4);
    const __m128i part = _mm512_extracti32x4_epi32(psum_local, 3);
    carry += _mm_extract_epi32(part, 3);
  }
  for (int i = tripcount; i < n; i++) {
    if (in[i] >= 0.5f)
      out[carry++] = in[i];
  }
  return carry;
}
