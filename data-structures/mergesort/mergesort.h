#pragma once

#include <algorithm>
#include <vector>

template <typename T>
void merge_arr(std::vector<T> &arr, int lo, int mid, int hi) {
  std::vector<T> left_arr(mid - lo), right_arr(hi - mid);
  for (int i = 0; i < mid - lo; i++)
    left_arr[i] = arr[lo + i];
  for (int i = 0; i < hi - mid; i++)
    right_arr[i] = arr[mid + i];
  int left_idx = 0, right_idx = 0, arr_idx = lo;
  while (left_idx < mid - lo && right_idx < hi - mid) {
    if (left_arr[left_idx] <= right_arr[right_idx])
      arr[arr_idx++] = left_arr[left_idx++];
    else
      arr[arr_idx++] = right_arr[right_idx++];
  }
  while (left_idx < mid - lo)
    arr[arr_idx++] = left_arr[left_idx++];
  while (right_idx < hi - mid)
    arr[arr_idx++] = right_arr[right_idx++];
}

template <typename T> void merge_sort(std::vector<T> &arr) {
  for (int subarr_size = 1; subarr_size < arr.size(); subarr_size *= 2) {
    for (int lo = 0; lo < arr.size(); lo += 2 * subarr_size) {
      int mid = std::min(lo + subarr_size, (int)arr.size()),
          hi = std::min(mid + subarr_size, (int)arr.size());
      merge_arr(arr, lo, mid, hi);
    }
  }
}
