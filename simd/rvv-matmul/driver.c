#include "matmul.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
  if (argc != 4) {
    fprintf(stderr, "Dimension parameter not found\n");
    return 1;
  }

  int M = atoi(argv[1]), N = atoi(argv[2]), K = atoi(argv[3]);
  if (M <= 0 || N <= 0 || K <= 0) {
    fprintf(stderr, "Invalid dimension: %s %s %s\n", argv[1], argv[2], argv[3]);
    return 1;
  }

  srand(42);
  uint32_t *a = calloc(M * N, sizeof(uint32_t)),
           *b = calloc(N * K, sizeof(uint32_t)),
           *c = calloc(M * K, sizeof(uint32_t));
  for (int i = 0; i < M * N; i++)
    a[i] = rand();
  for (int i = 0; i < N * K; i++)
    b[i] = rand();

  clock_t start, end;
  start = clock();
  matmul(a, b, c, M, N, K);
  end = clock();

  double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Elapsed: %lf\n", elapsed);

  FILE *outfile_a = fopen("a.mat.txt", "w");
  for (int i = 0; i < M * N; i++)
    fprintf(outfile_a, "%u ", a[i]);
  fclose(outfile_a);
  FILE *outfile_b = fopen("b.mat.txt", "w");
  for (int i = 0; i < N * K; i++)
    fprintf(outfile_b, "%u ", b[i]);
  fclose(outfile_b);
  FILE *outfile_c = fopen("c.mat.txt", "w");
  for (int i = 0; i < M * K; i++)
    fprintf(outfile_c, "%u ", c[i]);
  fclose(outfile_c);
  return 0;
}
