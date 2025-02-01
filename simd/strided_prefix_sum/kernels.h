#pragma once

template <typename T, int S> void kernel_scalar(T *arr, int n);

template <typename T, int S> void kernel_autovec(T *arr, int n);

template <typename T, int S> void kernel_avx512(T *arr, int n);
