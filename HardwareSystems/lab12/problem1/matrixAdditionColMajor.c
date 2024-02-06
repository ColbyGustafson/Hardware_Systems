#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

// compile: gcc -o matrixAdditionColMajor matrixAdditionColMajor.c
// execute: ./matrixAdditionColMajor
// L1 cache info: perf stat -e L1-dcache-loads,L1-dcache-load-misses ./matrixAdditionColMajor
// L3 cache info: perf stat -e LLC-loads,LLC-load-misses ./matrixAdditionColMajor

#define SIZE 4096
//TODO: change SIZE for different experiments to tabulate results

// TODO for Lab: implement this method
long int columnMajorMatrixSum(int n, int *src )
{
	int i,j;
	long int matrixTotal = 0;
	for(j=0; j<n; j++)
	{
		long int colSum = 0;
		for(i=0; i<n; i++)
		{
			colSum = colSum + src[n*i + j];
		}
		matrixTotal = matrixTotal + colSum;
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
    long int sum = columnMajorMatrixSum(n, A);
    gettimeofday( &end, NULL );
    
    double seconds = (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);
    
    double numOps = SIZE * SIZE;
    double gflops = 1.0e-9 * numOps / seconds;

    printf("column-major %g milliseconds\n", seconds*1e3 );
    printf("Number of Operations = %.2f and GFLOPS %f \n", numOps, gflops);
  
    /* release resources */
    free( A );
    return 0;
}
