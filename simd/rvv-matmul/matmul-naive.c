#include "matmul.h"

#include <stdint.h>

void matmul(const uint32_t *__restrict__ a, const uint32_t *__restrict__ b,
            uint32_t *__restrict__ c, const int M, const int N, const int K) {
  for (int i = 0; i < M; i++)
    for (int j = 0; j < K; j++) {
      uint32_t res = 0.0f;
      for (int k = 0; k < N; k++)
        res += a[N * i + k] * b[K * k + j];
      c[K * i + j] = res;
    }
}
