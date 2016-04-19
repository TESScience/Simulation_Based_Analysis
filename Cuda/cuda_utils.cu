#include "cuda_utils.h"
#include <assert.h>
#include <cuda_runtime.h>

/**
 * Get the device count for CUDA boards.
 */
int cuda_device_count() {
   int nDevices;
   cudaGetDeviceCount(&nDevices);
   return nDevices;
}

/** 
 * Get the maximum number of threads per block
 */
int max_threads_per_block(const int device_idx) {
   assert(device_idx < cuda_device_count());
   cudaDeviceProp prop;
   cudaGetDeviceProperties(&prop, device_idx);
   return prop.maxThreadsPerBlock;
}
