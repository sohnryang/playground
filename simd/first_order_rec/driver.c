#include <smmintrin.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <immintrin.h>

void kernel_scalar(const float *restrict arr_a, const float *restrict arr_b,
                   float *restrict out, int n) {
  float x = 0;
  for (int i = 0; i < n; i++) {
    x = arr_a[i] * x + arr_b[i];
    out[i] = x;
  }
}

void kernel_avx512(const float *restrict arr_a, const float *restrict arr_b,
                   float *restrict out, int n) {
  float x = 0;
  int i;
  const __m512 ZERO_PS = _mm512_setzero_ps();
  const __m512 ONE_PS = _mm512_set1_ps(1);
  for (i = 0; i + 16 <= n; i += 16) {
    __m512 a = _mm512_loadu_ps(&arr_a[i]);
    __m512 b = _mm512_loadu_ps(&arr_b[i]);

    b = _mm512_fmadd_ps(_mm512_alignr_epi32(b, ZERO_PS, 16 - 1), a, b);
    a = _mm512_mul_ps(a, _mm512_alignr_epi32(a, ONE_PS, 16 - 1));
    b = _mm512_fmadd_ps(_mm512_alignr_epi32(b, ZERO_PS, 16 - 2), a, b);
    a = _mm512_mul_ps(a, _mm512_alignr_epi32(a, ONE_PS, 16 - 2));
    b = _mm512_fmadd_ps(_mm512_alignr_epi32(b, ZERO_PS, 16 - 4), a, b);
    a = _mm512_mul_ps(a, _mm512_alignr_epi32(a, ONE_PS, 16 - 4));
    b = _mm512_fmadd_ps(_mm512_alignr_epi32(b, ZERO_PS, 16 - 8), a, b);
    a = _mm512_mul_ps(a, _mm512_alignr_epi32(a, ONE_PS, 16 - 8));
    b = _mm512_fmadd_ps(_mm512_set1_ps(x), a, b);
    _mm512_storeu_ps(&out[i], b);

    const __m128 last_part = _mm512_extractf32x4_ps(b, 3);
    _MM_EXTRACT_FLOAT(x, last_part, 3);
  }

  for (; i < n; i++) {
    x = arr_a[i] * x + arr_b[i];
    out[i] = x;
  }
}

int main(int argc, char **argv) {
  int elem_count = 0;
  if (argc >= 2)
    elem_count = atoi(argv[1]);
  elem_count = elem_count ? elem_count : 1024;

  if (argc >= 3)
    srand(atoi(argv[2]));

  float *arr_a = calloc(elem_count, sizeof(float));
  float *arr_b = calloc(elem_count, sizeof(float));
  for (int i = 0; i < elem_count; i++) {
    arr_a[i] = (float)rand() / RAND_MAX;
    arr_b[i] = (float)rand() / RAND_MAX;
  }

  {
    float *out = calloc(elem_count, sizeof(float));
    clock_t start = clock();
    kernel_scalar(arr_a, arr_b, out, elem_count);
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
    kernel_avx512(arr_a, arr_b, out, elem_count);
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

  free(arr_a);
  free(arr_b);
  return 0;
}
