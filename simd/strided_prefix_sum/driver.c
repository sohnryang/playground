#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <immintrin.h>

void kernel_scalar(float *arr, int n) {
#pragma loop vectorize(disable)
  for (int i = 2; i < n; i++)
    arr[i] += arr[i - 2];
}

void kernel_avx512(float *arr, int n) {
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

int main(int argc, char **argv) {
  int elem_count = 0;
  if (argc >= 2)
    elem_count = atoi(argv[1]);
  elem_count = elem_count ? elem_count : 1024;

  if (argc >= 3)
    srand(atoi(argv[2]));

  float *arr = calloc(elem_count, sizeof(float));
  for (int i = 0; i < elem_count; i++)
    arr[i] = (float)rand() / RAND_MAX;

  {
    float *buf = calloc(elem_count, sizeof(float));
    memcpy(buf, arr, elem_count * sizeof(float));
    clock_t start = clock();
    kernel_scalar(buf, elem_count);
    clock_t end = clock();
    printf("Scalar elapsed: %lf sec\n", (double)(end - start) / CLOCKS_PER_SEC);

    if (argc >= 4) {
      FILE *outfile = fopen(argv[3], "w");
      for (int i = 0; i < elem_count; i++)
        fprintf(outfile, "%f\n", buf[i]);
      fclose(outfile);
    }
    free(buf);
  }

  {
    float *buf = calloc(elem_count, sizeof(float));
    memcpy(buf, arr, elem_count * sizeof(float));
    clock_t start = clock();
    kernel_avx512(buf, elem_count);
    clock_t end = clock();
    printf("AVX512 elapsed: %lf sec\n", (double)(end - start) / CLOCKS_PER_SEC);

    if (argc >= 5) {
      FILE *outfile = fopen(argv[4], "w");
      for (int i = 0; i < elem_count; i++)
        fprintf(outfile, "%f\n", buf[i]);
      fclose(outfile);
    }
    free(buf);
  }

  free(arr);
  return 0;
}
