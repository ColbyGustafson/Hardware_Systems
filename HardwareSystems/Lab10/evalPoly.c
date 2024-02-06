#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>
#include <math.h>
#include <sys/time.h>

#define MAX 256

// Compile: gcc -O3 -mavx -lm -o evalPoly evalPoly.c
// Run:     ./evalPoly

// pow function in C: x to the power y is given by function pow(double x, double y);

double evaluate(double x, double *coefficients)
{
     int degree;
     
     double *terms = (double *)_mm_malloc( MAX * sizeof(double), 32);
     
     for(degree = 0; degree < MAX; degree++)
     {
           double powerOfX = pow(x, degree);
           
           // evaluate each term
           terms[degree] = coefficients[degree] * powerOfX;
     }
     
     double answer = 0;

     // sum all the terms 
     for(degree = 0; degree < MAX; degree++)
     {
            answer = answer + terms[degree];    
     }
     
     _mm_free(terms);
     
     return answer;
}

// TODO: Convert the above evaluate functions using Intrinsics
double evaluateSIMD(double x, double *coefficients)
{
	int degree, i;
	
	double *terms = (double *)_mm_malloc( MAX * sizeof(double), 32);

	for(degree = 0; degree < MAX; degree=degree+4)
	{
		__m256d coeff = _mm256_load_pd(coefficients+degree);
		__m256d arr0 = _mm256_set_pd(pow(x, degree), pow(x, degree+1), pow(x, degree+2), pow(x, degree+3));
		__m256d multi = _mm256_mul_pd(coeff, arr0);
		_mm256_store_pd(terms + degree, multi);
		//double powerOfX = pow(x, degree);
		//terms[degree] = coefficients[degree] * powerOfX;
	}

	double answer = 0;
	
	double *sum = (double *)_mm_malloc( 4 * sizeof(double), 32);
	for(i = 0; i<4; i++)
	{
		sum[i] = 0;
	}
	for(degree = 0; degree < MAX; degree=degree+4)
	{
		__m256d a0 = _mm256_load_pd(&terms[degree]);
		__m256d b0 = _mm256_load_pd(&sum[0]);
		__m256d c0 = _mm256_add_pd(a0, b0);

		_mm256_store_pd(&sum[0], c0);
		//answer = answer + terms[degree];
	}
	for(i = 0; i<4; i++)
	{
		answer = answer + sum[i];
	}
	_mm_free(terms);
	
	return answer;
}

// initialize the coefficients with different values
void initialize(double *coeffArr, int length)
{
    int i;
    for( i = 0; i<length; i++)
    {
       coeffArr[i] = i+1;
    }
}

int main()
{
   double answer, answerSIMD,  x = 0.99999;
   
   size_t N_pd = (MAX * 8)/sizeof(double);

   double *coefficients = (double*)_mm_malloc(N_pd*sizeof(double), 32);

   struct timeval  tv1, tv2, tv3;

   initialize(coefficients, MAX);
   
   gettimeofday(&tv1, NULL); 
   answer = evaluate(x, coefficients);
   gettimeofday(&tv2, NULL); 
   answerSIMD = evaluateSIMD(x, coefficients);
   gettimeofday(&tv3, NULL);

   double time1 = (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv2.tv_sec - tv1.tv_sec);
   double time2 = (double) (tv3.tv_usec - tv2.tv_usec) / 1000000 + (double) (tv3.tv_sec - tv2.tv_sec);

   printf("#coefficients %lu \n", N_pd);
   printf("Without intrinsics: Answer is %f and time is %f \n", answer, time1);
   printf("With intrinsics: Answer is %f and time is %f \n", answerSIMD, time2);
   
   _mm_free(coefficients);
   return 0;
}
