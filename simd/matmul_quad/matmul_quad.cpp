#include <arm_neon.h>
#include <chrono>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <random>

void print_matrix_4x4(int32_t *A) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++)
      std::cout << A[4 * i + j] << " ";
    std::cout << std::endl;
  }
}

void matmul_4x4_naive(int32_t *A, int32_t *B, int32_t *C) {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      for (int k = 0; k < 4; k++)
        C[4 * i + k] += A[4 * i + j] * B[4 * j + k];
}

void matmul_4x4_neon(int32_t *A, int32_t *B, int32_t *C) {
  int32x4_t B0 = vld1q_s32(B);
  int32x4_t B1 = vld1q_s32(B + 4);
  int32x4_t B2 = vld1q_s32(B + 8);
  int32x4_t B3 = vld1q_s32(B + 12);
  int32x4_t C0 = vmovq_n_s32(0);
  int32x4_t C1 = vmovq_n_s32(0);
  int32x4_t C2 = vmovq_n_s32(0);
  int32x4_t C3 = vmovq_n_s32(0);

  int32x4_t A0 = vld1q_s32(A);
  C0 = vmlaq_laneq_s32(C0, B0, A0, 0);
  C0 = vmlaq_laneq_s32(C0, B1, A0, 1);
  C0 = vmlaq_laneq_s32(C0, B2, A0, 2);
  C0 = vmlaq_laneq_s32(C0, B3, A0, 3);
  vst1q_s32(C, C0);

  int32x4_t A1 = vld1q_s32(A + 4);
  C1 = vmlaq_laneq_s32(C1, B0, A1, 0);
  C1 = vmlaq_laneq_s32(C1, B1, A1, 1);
  C1 = vmlaq_laneq_s32(C1, B2, A1, 2);
  C1 = vmlaq_laneq_s32(C1, B3, A1, 3);
  vst1q_s32(C + 4, C1);

  int32x4_t A2 = vld1q_s32(A + 8);
  C2 = vmlaq_laneq_s32(C2, B0, A2, 0);
  C2 = vmlaq_laneq_s32(C2, B1, A2, 1);
  C2 = vmlaq_laneq_s32(C2, B2, A2, 2);
  C2 = vmlaq_laneq_s32(C2, B3, A2, 3);
  vst1q_s32(C + 8, C2);

  int32x4_t A3 = vld1q_s32(A + 12);
  C3 = vmlaq_laneq_s32(C3, B0, A3, 0);
  C3 = vmlaq_laneq_s32(C3, B1, A3, 1);
  C3 = vmlaq_laneq_s32(C3, B2, A3, 2);
  C3 = vmlaq_laneq_s32(C3, B3, A3, 3);
  vst1q_s32(C + 12, C3);
}

int main() {
  std::random_device rdev;
  std::mt19937 rng(rdev());
  std::uniform_int_distribution<std::mt19937::result_type> dist(0, 255);
  int a[16], b[16];
  for (auto &v : a)
    v = dist(rng);
  for (auto &v : b)
    v = dist(rng);

  std::cout << "Matrix A:" << std::endl;
  print_matrix_4x4(a);
  std::cout << std::endl;
  std::cout << "Matrix B:" << std::endl;
  print_matrix_4x4(b);
  std::cout << std::endl;

  int c[16];
  memset(c, 0, sizeof(int) * 16);
  auto naive_start_time = std::chrono::high_resolution_clock::now();
  matmul_4x4_naive(a, b, c);
  auto naive_finish_time = std::chrono::high_resolution_clock::now();
  std::cout << "Result of A @ B (naive):" << std::endl;
  print_matrix_4x4(c);
  auto naive_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(
      naive_finish_time - naive_start_time);
  std::cout << naive_duration.count() << "ns elapsed" << std::endl << std::endl;

  memset(c, 0, sizeof(int) * 16);
  auto neon_start_time = std::chrono::high_resolution_clock::now();
  matmul_4x4_neon(a, b, c);
  auto neon_finish_time = std::chrono::high_resolution_clock::now();
  std::cout << "Result of A @ B (NEON):" << std::endl;
  print_matrix_4x4(c);
  auto neon_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(
      neon_finish_time - neon_start_time);
  std::cout << neon_duration.count() << "ns elapsed" << std::endl;
  return 0;
}
