#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <immintrin.h>

#define ITER 50000
#define LEN_1D 32000

__attribute__((aligned(64))) float a[LEN_1D], b[LEN_1D], c[LEN_1D], d[LEN_1D],
    e[LEN_1D];
__attribute__((aligned(64))) float a_init[LEN_1D], b_init[LEN_1D],
    c_init[LEN_1D], d_init[LEN_1D], e_init[LEN_1D];

void init_rand() {
  for (int i = 0; i < LEN_1D; i++)
    a_init[i] = (float)rand() / (float)RAND_MAX;
  for (int i = 0; i < LEN_1D; i++)
    b_init[i] = (float)rand() / (float)RAND_MAX;
  for (int i = 0; i < LEN_1D; i++)
    c_init[i] = (float)rand() / (float)RAND_MAX;
  for (int i = 0; i < LEN_1D; i++)
    d_init[i] = (float)rand() / (float)RAND_MAX;
  for (int i = 0; i < LEN_1D; i++)
    e_init[i] = (float)rand() / (float)RAND_MAX;
}

void init_determinstic() {
  memset(a, 0, LEN_1D * sizeof(float));
  for (int i = 0; i < LEN_1D; i++)
    b_init[i] = 1.0f;
  for (int i = 0; i < LEN_1D; i++) {
    float val = 1. / (float)(i + 1);
    c_init[i] = val;
    d_init[i] = val;
    e_init[i] = val;
  }
}

void reset() {
  memcpy(a, a_init, LEN_1D * sizeof(float));
  memcpy(b, b_init, LEN_1D * sizeof(float));
  memcpy(c, c_init, LEN_1D * sizeof(float));
  memcpy(d, d_init, LEN_1D * sizeof(float));
  memcpy(e, e_init, LEN_1D * sizeof(float));
}

int dummy(float[LEN_1D], float[LEN_1D], float[LEN_1D], float[LEN_1D],
          float[LEN_1D]);

float checksum() {
  float sum = 0.0f;
  for (int i = 0; i < LEN_1D; i++)
    sum += a[i];
  for (int i = 0; i < LEN_1D; i++)
    sum += b[i];
  return sum;
}

void scalar_kernel() {
  for (int nl = 0; nl < ITER; nl++) {
    for (int i = 1; i < LEN_1D - 1; i++) {
      a[i] = b[i - 1] + c[i] * d[i];
      b[i] = b[i + 1] - e[i] * d[i];
    }
    dummy(a, b, c, d, e);
  }
}

void vector_kernel() {
  for (int nl = 0; nl < ITER; nl++) {
    float b_carry = b[0];
    union {
      unsigned u;
      float f;
    } carry;
    for (int i = 1; i <= LEN_1D + 1 - 16 * 2; i += 16) {
      const __m512 b_lookahead_vec = _mm512_loadu_ps(&b[i + 1]);
      const __m512 c_vec = _mm512_loadu_ps(&c[i]);
      const __m512 d_vec = _mm512_loadu_ps(&d[i]);
      const __m512 e_vec = _mm512_loadu_ps(&e[i]);
      const __m512 b_next =
          _mm512_sub_ps(b_lookahead_vec, _mm512_mul_ps(e_vec, d_vec));
      const __m512 b_permuted =
          _mm512_alignr_epi32(b_next, _mm512_set1_ps(b_carry), 16 - 1);
      const __m512 a_next =
          _mm512_add_ps(b_permuted, _mm512_mul_ps(c_vec, d_vec));
      _mm512_storeu_ps(&a[i], a_next);
      _mm512_storeu_ps(&b[i], b_next);
      const __m128 b_next_last_part = _mm512_extractf32x4_ps(b_next, 3);
      _MM_EXTRACT_FLOAT(b_carry, b_next_last_part, 3);
    }
    for (int i = LEN_1D - 16; i < LEN_1D - 1; i++) {
      a[i] = b[i - 1] + c[i] * d[i];
      b[i] = b[i + 1] - e[i] * d[i];
    }
    dummy(a, b, c, d, e);
  }
}

int main(int argc, char **argv) {
  int seed = argc >= 2 ? atoi(argv[1]) : 0;
  if (seed) {
    srand(atoi(argv[1]));
    init_rand();
  } else
    init_determinstic();

  reset();
  clock_t start = clock();
  scalar_kernel();
  clock_t end = clock();
  float scalar_checksum = checksum();
  printf("Scalar elapsed time: %lf, checksum: %f\n",
         (double)(end - start) / CLOCKS_PER_SEC, scalar_checksum);
  if (argc >= 3) {
    FILE *outfile = fopen(argv[2], "w");
    for (int i = 0; i < LEN_1D; i++)
      fprintf(outfile, "%f %f\n", a[i], b[i]);
  }

  reset();
  start = clock();
  vector_kernel();
  end = clock();
  float vector_checksum = checksum();
  printf("Vector elapsed time: %lf, checksum: %f\n",
         (double)(end - start) / CLOCKS_PER_SEC, vector_checksum);
  if (argc >= 4) {
    FILE *outfile = fopen(argv[3], "w");
    for (int i = 0; i < LEN_1D; i++)
      fprintf(outfile, "%f %f\n", a[i], b[i]);
  }

  return 0;
}
