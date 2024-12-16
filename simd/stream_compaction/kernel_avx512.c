#include "kernel.h"

#include <immintrin.h>

int stream_compaction(const float *restrict in, float *restrict out, int n) {
  const int tripcount = n / 16 * 16;
  const __m512 cmp_rhs_splat = _mm512_set1_ps(0.5f);
  int j = 0;
  for (int i = 0; i < tripcount; i += 16) {
    const __m512 x = _mm512_load_ps(&in[i]);
    const __mmask16 cmp_mask = _mm512_cmplt_ps_mask(cmp_rhs_splat, x);
    const __m512 compressed = _mm512_maskz_compress_ps(cmp_mask, x);
    const int count = __builtin_popcount(cmp_mask);
    const __mmask16 store_mask = (__mmask16)_bzhi_u32(0xFFFF, count);
    _mm512_mask_storeu_ps(&out[j], store_mask, compressed);
    j += count;
  }
  for (int i = tripcount; i < n; i++) {
    if (in[i] >= 0.5f)
      out[j++] = in[i];
  }
  return j;
}
