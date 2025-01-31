#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <immintrin.h>

void kernel_scalar(const uint8_t *dist, int out[256], int n) {
  for (int i = 0; i < n; i++)
    out[dist[i]]++;
}

void kernel_avx512(const uint8_t *dist, int out[256], int n) {
  const __m512i ONES = _mm512_set1_epi32(1);
  int i;
  for (i = 0; i + 16 <= n; i += 16) {
    const __m128i x = _mm_load_epi32(&dist[i]);
    const __m512i x_epi32 = _mm512_cvtepu8_epi32(x);
    const __m512i conflicts = _mm512_conflict_epi32(x_epi32);
    const __m512i conflicts_popcnt = _mm512_popcnt_epi32(conflicts);
    const __m512i out_old = _mm512_i32gather_epi32(x_epi32, out, 4);
    const __m512i out_next =
        _mm512_add_epi32(out_old, _mm512_add_epi32(conflicts_popcnt, ONES));
    _mm512_i32scatter_epi32(out, x_epi32, out_next, 4);
  }
  for (; i < n; i++)
    out[dist[i]]++;
}

int main(int argc, char **argv) {
  int element_count = 0;
  if (argc >= 2)
    element_count = atoi(argv[1]);
  element_count = element_count ? element_count : 8192;

  int seed = 42;
  if (argc >= 3)
    seed = atoi(argv[2]);
  srand(seed);

  uint8_t *distribution = calloc(element_count, sizeof(uint8_t));
  for (int i = 0; i < element_count; i++)
    distribution[i] = rand();

  int *scalar_result = calloc(256, sizeof(int));
  clock_t start = clock();
  kernel_scalar(distribution, scalar_result, element_count);
  clock_t end = clock();
  printf("Scalar elapsed: %lf secs\n", (double)(end - start) / CLOCKS_PER_SEC);

  int *vector_result = calloc(256, sizeof(int));
  start = clock();
  kernel_avx512(distribution, vector_result, element_count);
  end = clock();
  printf("AVX512 elapsed: %lf secs\n", (double)(end - start) / CLOCKS_PER_SEC);

  if (argc >= 4) {
    FILE *outfile = fopen(argv[3], "w");
    for (int i = 0; i < 256; i++)
      fprintf(outfile, "%d\n", scalar_result[i]);
    fclose(outfile);
  }

  if (argc >= 5) {
    FILE *outfile = fopen(argv[4], "w");
    for (int i = 0; i < 256; i++)
      fprintf(outfile, "%d\n", vector_result[i]);
    fclose(outfile);
  }

  free(distribution);
  free(scalar_result);
  free(vector_result);
  return 0;
}
