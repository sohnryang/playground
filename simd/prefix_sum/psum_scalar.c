#include "prefix_sum.h"

void prefix_sum(float *arr, int n) {
  for (int i = 1; i < n; i++)
    arr[i] += arr[i - 1];
}
