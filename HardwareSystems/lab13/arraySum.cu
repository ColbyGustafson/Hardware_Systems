#include <stdio.h>
#include "cuda_runtime.h"

// Compile: nvcc -o arraySum arraySum.cu
// Run: ./arraySum

// Note: Host: CPU+MainMemory & Device: GPU

__global__ void addKernel(int *device_memory_a, int *device_memory_b, int *device_memory_c)
{   
    int i = blockDim.x * blockIdx.x + threadIdx.x;
    device_memory_c[i] = device_memory_a[i] + device_memory_b[i];
}

// TODO: implement a kernel (like above) called squareKernel to square each element of an array
__global__ void squareKernel(int *device_memory_a)
{
	int i = blockDim.x * blockIdx.x + threadIdx.x;
	device_memory_a[i] = device_memory_a[i] * device_memory_a[i];
}


// function for using CUDA to add arrays in parallel
void addWithCuda(int *host_memory_a, int *host_memory_b, int *host_memory_c, size_t size)
{
	cudaSetDevice(0);

    int *device_memory_a;
    int *device_memory_b;
    int *device_memory_c;
    
    
 	// Allocate memory in the GPU for two inputs and one output
    cudaMalloc((void**)&device_memory_a, size * sizeof(int));
    cudaMalloc((void**)&device_memory_b, size * sizeof(int));
    cudaMalloc((void**)&device_memory_c, size * sizeof(int));


    // Copy input from CPU to GPU
    cudaMemcpy(device_memory_a, host_memory_a, size * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(device_memory_b, host_memory_b, size * sizeof(int), cudaMemcpyHostToDevice);

    // Launch a kernel on the GPU with one thread for each element.
    squareKernel<<<1, size>>>(device_memory_a);
    squareKernel<<<1, size>>>(device_memory_b);
    addKernel<<<1, size>>>(device_memory_a, device_memory_b, device_memory_c);
    cudaDeviceSynchronize();

    // Copy output from GPU to CPU.
    cudaMemcpy(host_memory_c, device_memory_c, size * sizeof(int), cudaMemcpyDeviceToHost);

    // Free memory in GPU
    cudaFree(device_memory_a);
    cudaFree(device_memory_b);
    cudaFree(device_memory_c);
}

void fillArray(int *array, size_t size, int multiple)
{	
	int i;
	for(i=0; i<size; i++)
	{
		array[i] = (i+1)*multiple;
	}
}

void printArray(int *array, size_t size)
{
	int i;
	for(i=0; i<size; i++)
	{
		printf("%d, ", array[i]);
	}
	printf("\n");
}

int main()
{
    int arraySize = 50;
    int array_a[arraySize];
    int array_b[arraySize];
    int array_c[arraySize];

    fillArray(array_a, arraySize, 5);
    fillArray(array_b, arraySize, 7);

    printArray(array_a, arraySize); //should print multiples of 5
    printArray(array_b, arraySize); //should print multiples of 7

    // Add arrays in parallel
	addWithCuda(array_a, array_b, array_c, arraySize);

	printArray(array_c, arraySize);
    return 0;
}
