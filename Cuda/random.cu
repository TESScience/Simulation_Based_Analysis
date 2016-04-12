#include "random.h"
#include "warpspeed.h"
 
__global__ void warpspeed_rand(uint32_t * random_data)
{
    // Get our global thread ID
    int id = threadIdx.x + 
              threadIdx.y * blockDim.x + 
              threadIdx.z * blockDim.x * blockDim.y;
    uint32_t temp;

    temp = random_data[id];
    temp += random_data[id + TAP1 - RANDOM_FRAME_SIZE];
    temp += random_data[id + TAP2 - RANDOM_FRAME_SIZE];
    temp += random_data[id + TAP3 - RANDOM_FRAME_SIZE];
    temp += random_data[id + LENGTH - RANDOM_FRAME_SIZE];
    random_data[id] = temp;
}

// CUDA kernel. Each thread takes care of one element of c
__global__ void vecAdd(double *a, double *b, double *c, int n)
{
    // int id = blockIdx.x*blockDim.x + threadIdx.x;

    // Get our global thread ID
    int id = threadIdx.x + 
             threadIdx.y * blockDim.x + 
             threadIdx.z * blockDim.x * blockDim.y;

    //int warpid = id / 32;
 
    // Make sure we do not go out of bounds
    if (id < n)
        c[id] = a[id] + b[id];
}
