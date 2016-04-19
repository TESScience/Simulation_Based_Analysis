#include "random.h"
#include "warpspeed.h"

__global__ void vectorAdd(const float *A, const float *B, float *C)
{
    const int id = threadIdx.x + 
                   threadIdx.y * blockDim.x + 
                   threadIdx.z * blockDim.x * blockDim.y;

    C[id] = A[id] + B[id];
}
 
__global__ void warpspeed_rand(uint32_t * random_data)
{
    const int id = threadIdx.x + 
                   threadIdx.y * blockDim.x + 
                   threadIdx.z * blockDim.x * blockDim.y;
    //const int warpid = id / warpSize;
    uint32_t temp;

    temp = random_data[id];
    temp += random_data[id + TAP1 - RANDOM_FRAME_SIZE];
    temp += random_data[id + TAP2 - RANDOM_FRAME_SIZE];
    temp += random_data[id + TAP3 - RANDOM_FRAME_SIZE];
    temp += random_data[id + LENGTH - RANDOM_FRAME_SIZE];
    random_data[id] = temp;
}
