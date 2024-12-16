#include "kernel.h"

int stream_compaction(const float *restrict in, float *restrict out, int n) {
  int j = 0;
  for (int i = 0; i < n; i++) {
    if (in[i] >= 0.5f)
      out[j++] = in[i];
  }
  return j;
}
