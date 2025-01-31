#include <smmintrin.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <immintrin.h>

void kernel_scalar(const float *restrict arr, const int *restrict flags,
                   float *restrict out, int n) {
  float sum = 0;
  for (int i = 0; i < n; i++) {
    if (flags[i])
      sum = 0;
    sum += arr[i];
    out[i] = sum;
  }
}

static inline __mmask16 slide_mask(__mmask16 mask, unsigned amount) {
  return (mask << amount) | ((1 << amount) - 1);
}

void kernel_avx512(const float *restrict arr, const int *restrict flags,
                   float *restrict out, int n) {
  float sum = 0;
  int i;
  const __m512i ZERO_EPI32 = _mm512_setzero_epi32();
  const __m512 ZERO_PS = _mm512_setzero_ps();
  for (i = 0; i + 16 <= n; i += 16) {
    const __m512i flag = _mm512_loadu_epi32(&flags[i]);
    uint16_t mask = _mm512_cmpeq_epi32_mask(flag, ZERO_EPI32);
    __m512 x = _mm512_loadu_ps(&arr[i]);

    x = _mm512_mask_add_ps(x, mask, x, _mm512_alignr_epi32(x, ZERO_PS, 16 - 1));
    mask &= slide_mask(mask, 1);
    x = _mm512_mask_add_ps(x, mask, x, _mm512_alignr_epi32(x, ZERO_PS, 16 - 2));
    mask &= slide_mask(mask, 2);
    x = _mm512_mask_add_ps(x, mask, x, _mm512_alignr_epi32(x, ZERO_PS, 16 - 4));
    mask &= slide_mask(mask, 4);
    x = _mm512_mask_add_ps(x, mask, x, _mm512_alignr_epi32(x, ZERO_PS, 16 - 8));
    mask &= slide_mask(mask, 8);

    x = _mm512_mask_add_ps(x, mask, _mm512_set1_ps(sum), x);
    _mm512_storeu_ps(&out[i], x);

    const __m128 last_part = _mm512_extractf32x4_ps(x, 3);
    _MM_EXTRACT_FLOAT(sum, last_part, 3);
  }

  for (; i < n; i++) {
    if (flags[i])
      sum = 0;
    sum += arr[i];
    out[i] = sum;
  }
}

int main(int argc, char **argv) {
  int elem_count = 0;
  if (argc >= 2)
    elem_count = atoi(argv[1]);
  elem_count = elem_count ? elem_count : 1024;

  if (argc >= 3)
    srand(atoi(argv[2]));

  float *arr = calloc(elem_count, sizeof(float));
  int *flags = calloc(elem_count, sizeof(int));
  for (int i = 0; i < elem_count; i++) {
    arr[i] = (float)rand() / RAND_MAX;
    flags[i] = rand() >= RAND_MAX / 2;
  }

  {
    float *out = calloc(elem_count, sizeof(float));
    clock_t start = clock();
    kernel_scalar(arr, flags, out, elem_count);
    clock_t end = clock();
    printf("Scalar elapsed: %lf sec\n", (double)(end - start) / CLOCKS_PER_SEC);

    if (argc >= 4) {
      FILE *outfile = fopen(argv[3], "w");
      for (int i = 0; i < elem_count; i++)
        fprintf(outfile, "%f\n", out[i]);
      fclose(outfile);
    }
    free(out);
  }

  {
    float *out = calloc(elem_count, sizeof(float));
    clock_t start = clock();
    kernel_avx512(arr, flags, out, elem_count);
    clock_t end = clock();
    printf("AVX512 elapsed: %lf sec\n", (double)(end - start) / CLOCKS_PER_SEC);

    if (argc >= 5) {
      FILE *outfile = fopen(argv[4], "w");
      for (int i = 0; i < elem_count; i++)
        fprintf(outfile, "%f\n", out[i]);
      fclose(outfile);
    }
    free(out);
  }

  free(arr);
  free(flags);
  return 0;
}
