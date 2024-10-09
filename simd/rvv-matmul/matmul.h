#pragma once

#include <stdint.h>

void matmul(const uint32_t *__restrict__ a, const uint32_t *__restrict__ b,
            uint32_t *__restrict__ c, const int M, const int N, const int K);
