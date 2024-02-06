#include <stdio.h>

// For the CUDA runtime routines (prefixed with "cuda_")
#include <cuda_runtime.h>

// Compile: nvcc -o warmup warmup.cu
// Run: ./warmup

__global__ void HelloCuda()
{
    int i = blockDim.x * blockIdx.x + threadIdx.x;

    printf("Local thread Id = %d Block id = %d Global thread Id = ( %d )\n", threadIdx.x, blockIdx.x, i);
}


int main()
{

   int num_blocks = 6;
   int num_threads = 4;
   HelloCuda<<<num_blocks,num_threads>>>();
   cudaDeviceSynchronize();
   
   printf("main done \n");

   return 0;
}
