#include "matmul.h"

#include <stddef.h>
#include <stdint.h>

#include <riscv_vector.h>

void matmul(const uint32_t *__restrict__ a, const uint32_t *__restrict__ b,
            uint32_t *__restrict__ c, const int M, const int N, const int K) {
  const size_t vlmax = __riscv_vsetvlmax_e32m1();
  for (int i = 0; i < M; i++)
    for (int j = 0; j < K; j++) {
      const uint32_t *ptr_a = &a[N * i], *ptr_b = &b[j];
      int leftover = N;
      vuint32m1_t vec_s = __riscv_vmv_v_x_u32m1(0, vlmax),
                  vec_zero = __riscv_vmv_v_x_u32m1(0, vlmax);
      while (leftover > 0) {
        const size_t vl = __riscv_vsetvl_e32m1(leftover);
        vuint32m1_t vec_a = __riscv_vle32_v_u32m1(ptr_a, vl),
                    vec_b =
                        __riscv_vlse32_v_u32m1(ptr_b, sizeof(uint32_t) * K, vl);
        vec_s = __riscv_vmacc_vv_u32m1(vec_s, vec_a, vec_b, vl);
        leftover -= vl;
        ptr_a += vl;
        ptr_b += vl * K;
      }
      vuint32m1_t vec_sum =
          __riscv_vredsum_vs_u32m1_u32m1(vec_s, vec_zero, vlmax);
      uint32_t sum = __riscv_vmv_x_s_u32m1_u32(vec_sum);
      c[K * i + j] = sum;
    }
}
