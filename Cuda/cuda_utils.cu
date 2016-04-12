/**
 * Get the device count for CUDA boards.
 */
int cuda_device_count() {
   int nDevices;
   cudaGetDeviceCount(&nDevices);
   return nDevices;
}
