#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "prefix_sum.h"

int main(int argc, char **argv) {
  int element_count;
  if (argc >= 2)
    element_count = atoi(argv[1]);
  else
    element_count = 1024;

  int iter_count;
  if (argc >= 3)
    iter_count = atoi(argv[2]);
  else
    iter_count = 1;

  float *arr = aligned_alloc(64, element_count * sizeof(float));
  srand(42);
  for (int i = 0; i < element_count; i++)
    arr[i] = ((float)rand()) / (float)RAND_MAX;

  float *buf = aligned_alloc(64, element_count * sizeof(float));
  memcpy(buf, arr, element_count * sizeof(float));
  clock_t start = clock();
  for (int i = 0; i < iter_count; i++)
    prefix_sum(buf, element_count);
  clock_t end = clock();
  printf("Elapsed time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

  if (argc >= 4) {
    FILE *outfile = fopen(argv[3], "w");
    for (int i = 0; i < element_count; i++)
      fprintf(outfile, "%f %f\n", arr[i], buf[i]);
    fclose(outfile);
  }

  free(arr);
  free(buf);
  return 0;
}
