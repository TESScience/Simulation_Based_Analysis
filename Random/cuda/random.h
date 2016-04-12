#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

// CUDA kernel. Each thread takes care of one element of c
__global__ void warspeed_rand(uint32_t *random_numbers, int n, int rounds);
__global__ void vecAdd(double *a, double *b, double *c, int n);
int main( int argc, char* argv[] );
