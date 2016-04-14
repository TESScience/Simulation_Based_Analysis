#include "cuda_utils.h"
#include <assert.h>

/**
 * Get the device count for CUDA boards.
 */
int cuda_device_count() {
   int nDevices;
   cudaGetDeviceCount(&nDevices);
   return nDevices;
}

int warp_size(const int i) {
   assert(i < cuda_device_count());
   cudaDeviceProp prop;
   cudaGetDeviceProperties(&prop, i);
   return prop.warpSize;
}
