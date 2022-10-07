#include <arm_neon.h>
#include <cstdint>
#include <iostream>

void dot_4(int32_t *A, int32_t *B, int32_t *C) {
  int32x4_t vec_A = vld1q_s32(A);
  int32x4_t vec_B = vld1q_s32(B);
  int32x4_t vec_C = vmovq_n_s32(0);
  vec_C = vmlaq_s32(vec_C, vec_A, vec_B);
  *C = vaddvq_s32(vec_C);
}

int main() {
  int32_t a[4];
  for (int32_t &v : a)
    std::cin >> v;
  int32_t b[4];
  for (int32_t &v : b)
    std::cin >> v;
  int32_t c;
  dot_4(a, b, &c);
  std::cout << c << std::endl;
  return 0;
}
