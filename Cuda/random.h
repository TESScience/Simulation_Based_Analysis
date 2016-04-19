#pragma once
#include <stdint.h>

__global__ void warspeed_rand(uint32_t *random_numbers, int n, int rounds);
__global__ void vectorAdd(const float *a, const float *b, float *c);
