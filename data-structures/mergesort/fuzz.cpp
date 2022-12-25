#include <cstddef>
#include <cstdint>
#include <vector>

#include "mergesort.h"

int fuzz(const uint8_t *data, size_t size) {
  if (size == 0)
    return 0;
  std::vector<uint8_t> arr;
  for (size_t i = 0; i < size; i++)
    arr.push_back(data[i]);
  merge_sort(arr);
  for (size_t i = 1; i < size; i++)
    if (arr[i - 1] > arr[i])
      return 1;
  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  if (fuzz(Data, Size))
    __builtin_trap();
  return 0;
}
