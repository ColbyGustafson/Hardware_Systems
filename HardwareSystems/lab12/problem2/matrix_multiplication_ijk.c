#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

// compile: gcc -O3 -o matrix_multiplication_ijk matrix_multiplication_ijk.c
// execute: ./matrix_multiplication_ijk
// L1 cache info: perf stat -e L1-dcache-loads,L1-dcache-load-misses ./matrix_multiplication_ijk
// L3 cache info: perf stat -e LLC-loads,LLC-load-misses ./matrix_multiplication_ijk

#define SIZE 4096
//TODO: change SIZE for different experiments to tabulate results

void matmul_ijk(int n, double *A, double *B, double *C)
{
   int i, j, k;
   
   for( i = 0; i<n; i++)
   {
     for( j = 0; j < n; j++)
     {
         double cij = C[i*n + j];
         for( k = 0; k<n; k++)
         {
            cij = cij + A[i*n + k] * B[k*n + j];
         }
         C[i*n + j] = cij;
     }
   }
}

void initialize(double *arr, int length, double val)
{
    int i;
    for( i = 0; i<length; i++)
    {
       arr[i] = val;
    }
}

void initializeMM(double *arr, int length)
{
    int i;
    for( i = 0; i<length; i++)
    {
       arr[i] = i;
    }
}

void printMatrix(double *arr, int numElements, int dimension)
{
   int i;
   
   for( i = 0; i < numElements; i++)
   {
      if(i % dimension == 0)
        printf("\n");
        
      printf("%f ", arr[i]);
   }
}

int matmul()
{
   double *A, *B, *C;
   int dimension = SIZE;
   int numElements = SIZE * SIZE;
   printf("dimension = %d & numElements %d \n", dimension, numElements);
   
   A = (double *)malloc(sizeof(double) * numElements );
   initialize(A, numElements, 1.0);

   B = (double *)malloc(sizeof(double) * numElements );
   initializeMM(B, numElements);
   
   C = (double *)malloc(sizeof(double) * numElements );
   initialize(C, numElements, 0.0);
   
   struct timeval  tv1, tv2;
   
   gettimeofday(&tv1, NULL);
   matmul_ijk(dimension, A, B, C);   
   gettimeofday(&tv2, NULL);

   double time_spent = (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
                                     (double) (tv2.tv_sec - tv1.tv_sec);
  
   double numOps = 2.0 * SIZE * SIZE * SIZE;
   double gflops = 1.0e-9 * numOps / time_spent;

   printf("ijk: \n");
   printf("%g milliseconds\n", time_spent * 1e3);
   printf("Number of Operations = %.2f and GFLOPS %f \n", numOps, gflops);
    
   free(A);
   free(B);
   free(C);
   
   return 0;
}

int main()
{
   printf("Matrix multiplication Program \n");

   matmul();
   
   return 0;
}
