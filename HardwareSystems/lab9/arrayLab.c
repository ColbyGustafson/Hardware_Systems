#include <stdio.h>
#include <immintrin.h>
#include <stdlib.h>
#include <sys/time.h>

// Compile: gcc -mavx -o arrayLab arrayLab.c
// Execute: ./arrayLab

void vecAdd(int n, double *A, double *B, double *C)
{
  int i;
  for(i = 0; i<n; i++)
  {
    C[i] = C[i] + A[i] * B[i];
  }
}

// TODO: Implement vecAdd function using Intrinsic functions
void vecAddWithIntrinsics(int n, double *A, double *B, double *C)
{
	int i;
	for(i = 0; i<n; i=i+4)
	{
		__m256d a0 = _mm256_load_pd(&A[i]);
		__m256d b0 = _mm256_load_pd(&B[i]);
		__m256d c0 = _mm256_load_pd(&C[i]);
		a0 = _mm256_mul_pd(a0, b0);
		c0 = _mm256_add_pd(c0, a0);
		_mm256_store_pd(&C[i], c0);
	}  
}

// set a same value val to all the element of array arr
void set(double *arr, int length, double val)
{
    int i;
    for( i = 0; i<length; i++)
    {
       arr[i] = val;
    }
}

// TODO: Implement set function using Intrinsic functions
void setWithIntrinsics(double *arr, int length, double val)
{
	int i;
	for( i = 0; i<length; i=i+4)
	{
		__m256d arr0 = _mm256_set_pd(val, val, val, val);
		_mm256_store_pd(&arr[i], arr0);
	}
}

// initialize the array elements with different values
void initialize(double *arr, int length)
{
    int i;
    for( i = 0; i<length; i++)
    {
       arr[i] = i+1;
    }
}

void display(double *arr, int start, int end)
{
    int i;
    // printf few values to check output
    for( i = start; i < end; i++)
    {
       printf("%.2f ", arr[i]);
    }
    printf("\n");
}

int main()
{
   
   int NUM_ELEMENTS = 1024;
   
   printf("NUM_ELEMENTS: %d, sizeof(double): %lu \n ", NUM_ELEMENTS, sizeof(double));
   
   // TODO: allocate memory arrays A, B, C using _mm_malloc
   double *A = (double*)_mm_malloc(NUM_ELEMENTS * sizeof(double), 32);
   double *B = (double*)_mm_malloc(NUM_ELEMENTS * sizeof(double), 32);
   double *C = (double*)_mm_malloc(NUM_ELEMENTS * sizeof(double), 32);

   // initializing the arrays A, B and C
   initialize(A, NUM_ELEMENTS);
   setWithIntrinsics(B, NUM_ELEMENTS, 10);
   setWithIntrinsics(C, NUM_ELEMENTS, 15);

   // checking the first and last 16 values in the arrays
   display(A, 0, 16);
   display(B, 0, 16);
   display(C, 0, 16);
   display(A, NUM_ELEMENTS-16, NUM_ELEMENTS);
   display(B, NUM_ELEMENTS-16, NUM_ELEMENTS);
   display(C, NUM_ELEMENTS-16, NUM_ELEMENTS);

   // TODO: verify the results are same as with vecAdd(NUM_ELEMENTS, A, B, C);
   //vecAddWithIntrinsics(NUM_ELEMENTS, A, B, C);
   vecAdd(NUM_ELEMENTS, A, B, C);

   // TODO: use the display function to verify the results in C
   display(C, 0, 16);
   display(C, NUM_ELEMENTS-16, NUM_ELEMENTS);

   // TODO: de-allocate memory for A, B, C using _mm_free
   _mm_free(A);
   _mm_free(B);
   _mm_free(C);
   return 0;
}
