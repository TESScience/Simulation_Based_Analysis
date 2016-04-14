#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "random.h"
#include "cuda_utils.h"
 
int main( int argc, char* argv[] )
{
    // Size of vectors
    const int n = 100000;
    const size_t bytes = n*sizeof(double);
    // Number of threads in each thread block
    const int blockSize = 1024;
    // Number of thread blocks in grid
    const int gridSize = (int)ceil((float)n/blockSize);

    // Get the device count
    printf("Device Count: %i\n", cuda_device_count() );

    int i;
    for(i = 0; i < cuda_device_count(); i++ )
        printf("Warp Size for CUDA device %i: %i\n", i, warp_size(i));
 
    // Host input vectors
    double *h_a = (double*) alloca(bytes);
    double *h_b = (double*) alloca(bytes);
    //Host output vector
    double *h_c =  (double*) alloca(bytes);
 
    // Device input vectors
    double *d_a, *d_b;
    //Device output vector
    double *d_c;
 
 
    // Allocate memory for each vector on GPU
    cudaMalloc(&d_a, bytes);
    cudaMalloc(&d_b, bytes);
    cudaMalloc(&d_c, bytes);
 
    // Initialize vectors on host
    for(i = 0; i < n; i++ ) {
        h_a[i] = sin(i)*sin(i);
        h_b[i] = cos(i)*cos(i);
    }
 
    // Copy host vectors to device
    cudaMemcpy( d_a, h_a, bytes, cudaMemcpyHostToDevice);
    cudaMemcpy( d_b, h_b, bytes, cudaMemcpyHostToDevice);
 
 
    // Execute the kernel
    vecAdd<<<gridSize, blockSize>>>(d_a, d_b, d_c, n);
 
    // Copy array back to host
    cudaMemcpy( h_c, d_c, bytes, cudaMemcpyDeviceToHost );
 
    // Sum up vector c and print result divided by n, this should equal 1 within error
    double sum = 0;
    for(i=0; i<n; i++)
        sum += h_c[i];
    printf("final result: %f\n", sum/n);
 
    // Release device memory
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    return 0;
}
