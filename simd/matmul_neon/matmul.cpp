#include <arm_neon.h>
#include <chrono>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <random>

void print_matrix(int32_t *A, int m, int n) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++)
      std::cout << A[n * i + j] << " ";
    std::cout << std::endl;
  }
}

void matmul_naive(int32_t *A, int32_t *B, int32_t *C, int m, int n, int k) {
  for (int i_idx = 0; i_idx < m; i_idx++)
    for (int j_idx = 0; j_idx < n; j_idx++)
      for (int k_idx = 0; k_idx < k; k_idx++)
        C[k * i_idx + k_idx] += A[n * i_idx + j_idx] * B[k * j_idx + k_idx];
}

void matmul_neon(int32_t *A, int32_t *B, int32_t *C, int m, int n, int k) {
  int a_idx, b_idx, c_idx;
  int32x4_t A0, A1, A2, A3, B0, B1, B2, B3, C0, C1, C2, C3;
  for (int i_idx = 0; i_idx < m; i_idx += 4) {
    for (int k_idx = 0; k_idx < k; k_idx += 4) {
      C0 = vmovq_n_s32(0);
      C1 = vmovq_n_s32(0);
      C2 = vmovq_n_s32(0);
      C3 = vmovq_n_s32(0);
      for (int j_idx = 0; j_idx < n; j_idx += 4) {
        a_idx = n * i_idx + j_idx;
        b_idx = k * j_idx + k_idx;

        B0 = vld1q_s32(B + b_idx + 0 * k);
        B1 = vld1q_s32(B + b_idx + 1 * k);
        B2 = vld1q_s32(B + b_idx + 2 * k);
        B3 = vld1q_s32(B + b_idx + 3 * k);

        A0 = vld1q_s32(A + a_idx + 0 * n);
        C0 = vmlaq_laneq_s32(C0, B0, A0, 0);
        C0 = vmlaq_laneq_s32(C0, B1, A0, 1);
        C0 = vmlaq_laneq_s32(C0, B2, A0, 2);
        C0 = vmlaq_laneq_s32(C0, B3, A0, 3);

        A1 = vld1q_s32(A + a_idx + 1 * n);
        C1 = vmlaq_laneq_s32(C1, B0, A1, 0);
        C1 = vmlaq_laneq_s32(C1, B1, A1, 1);
        C1 = vmlaq_laneq_s32(C1, B2, A1, 2);
        C1 = vmlaq_laneq_s32(C1, B3, A1, 3);

        A2 = vld1q_s32(A + a_idx + 2 * n);
        C2 = vmlaq_laneq_s32(C2, B0, A2, 0);
        C2 = vmlaq_laneq_s32(C2, B1, A2, 1);
        C2 = vmlaq_laneq_s32(C2, B2, A2, 2);
        C2 = vmlaq_laneq_s32(C2, B3, A2, 3);

        A3 = vld1q_s32(A + a_idx + 3 * n);
        C3 = vmlaq_laneq_s32(C3, B0, A3, 0);
        C3 = vmlaq_laneq_s32(C3, B1, A3, 1);
        C3 = vmlaq_laneq_s32(C3, B2, A3, 2);
        C3 = vmlaq_laneq_s32(C3, B3, A3, 3);
      }
      c_idx = k * i_idx + k_idx;
      vst1q_s32(C + c_idx + 0 * k, C0);
      vst1q_s32(C + c_idx + 1 * k, C1);
      vst1q_s32(C + c_idx + 2 * k, C2);
      vst1q_s32(C + c_idx + 3 * k, C3);
    }
  }
}

bool matrix_equal(int32_t *C0, int32_t *C1, int m, int n) {
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      if (C0[n * i + j] != C1[n * i + j])
        return false;
  return true;
}

int main() {
  std::random_device rdev;
  std::mt19937 rng(rdev());
  std::uniform_int_distribution<std::mt19937::result_type> dist(0, 255);

  int m, n, k;
  std::cout << "Enter matrix dimensions: ";
  std::cin >> m >> n >> k;
  int a[m * n], b[n * k];
  for (auto &v : a)
    v = dist(rng);
  for (auto &v : b)
    v = dist(rng);

  /*
  std::cout << "Matrix A:" << std::endl;
  print_matrix(a, m, n);
  std::cout << std::endl;
  std::cout << "Matrix B:" << std::endl;
  print_matrix(b, n, k);
  */
  std::cout << std::endl;

  int c_naive[m * k];
  memset(c_naive, 0, sizeof(int) * m * k);
  auto naive_start_time = std::chrono::high_resolution_clock::now();
  matmul_naive(a, b, c_naive, m, n, k);
  auto naive_finish_time = std::chrono::high_resolution_clock::now();
  auto naive_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(
      naive_finish_time - naive_start_time);
  std::cout << "Naive: " << naive_duration.count() << "ns elapsed" << std::endl;

  int c_neon[m * k];
  memset(c_neon, 0, sizeof(int) * m * k);
  auto neon_start_time = std::chrono::high_resolution_clock::now();
  matmul_neon(a, b, c_neon, m, n, k);
  auto neon_finish_time = std::chrono::high_resolution_clock::now();
  if (!matrix_equal(c_naive, c_neon, m, k)) {
    std::cerr << "ERR: matrix mismatch" << std::endl;
    return 1;
  }
  auto neon_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(
      neon_finish_time - neon_start_time);
  std::cout << "NEON:  " << neon_duration.count() << "ns elapsed" << std::endl;

  return 0;
}
