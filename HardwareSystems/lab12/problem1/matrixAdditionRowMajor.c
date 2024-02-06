#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

// compile: gcc -o matrixAdditionRowMajor matrixAdditionRowMajor.c
// execute: ./matrixAdditionRowMajor
// L1 cache info: perf stat -e L1-dcache-loads,L1-dcache-load-misses ./matrixAdditionRowMajor
// L3 cache info: perf stat -e LLC-loads,LLC-load-misses ./matrixAdditionRowMajor

#define SIZE 4096
//TODO: change SIZE for different experiments to tabulate results

long int rowMajorMatrixSum(int n, int *src )
{
   int i,j;
   long int matrixTotal = 0;
   for(i = 0; i < n; i++)
   {
      long int rowSum = 0;
      for(j = 0; j < n; j++)
      {
         rowSum = rowSum + src[ n*i + j];
      }
      //printf("Row %d Sum = %d \n", i, rowSum);
      matrixTotal = matrixTotal + rowSum;
   }
   return matrixTotal;
}

int main( int argc, char **argv ) {
    int n = SIZE, i,j;

    /* allocate an n*n block of integers for the matrices */
    int *A = (int*)malloc( n*n*sizeof(int) );

    /* initialize A,B to random integers */
    for( i = 0; i < n*n; i++ )
       A[i] = i;

    /* measure performance */
    struct timeval start, end;

    gettimeofday( &start, NULL );   
    long int sum = rowMajorMatrixSum(n, A);
    gettimeofday( &end, NULL );
    
    double seconds = (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);
    
    double numOps = SIZE * SIZE;
    double gflops = 1.0e-9 * numOps / seconds;

    printf("row-major %g milliseconds\n", seconds*1e3 );
    printf("Number of Operations = %.2f and GFLOPS %f \n", numOps, gflops);
  
    /* release resources */
    free( A );
    return 0;
}
