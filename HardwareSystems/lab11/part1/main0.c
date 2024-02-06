#include <stdio.h>
#include <immintrin.h>
#include "bmp0.c"
#include <sys/time.h>

#define HEIGHT 800
#define WIDTH 800
#define DIMS 3

#define R 0
#define G 1
#define B 2

typedef float IMAGE[DIMS][HEIGHT][WIDTH];

// compile: gcc -O3 -mavx2 -o main0 main0.c
// execute: ./main0

void greyscale(IMAGE *image, IMAGE *greyscale_image) {
    int i, j;
    float r,g,b,val;
    float den = 3;
    for (i=0; i<HEIGHT; i++) {
        for (j=0; j<WIDTH; j++) {
            r = (*image)[R][i][j]; //Line 1
            g = (*image)[G][i][j]; //Line 2
            b = (*image)[B][i][j]; //Line 3
            val = r+g; //Line 4
            val = val+b; //Line 5
            val = val/den; //Line 6
            (*greyscale_image)[R][i][j] = val; //Line 7
            (*greyscale_image)[G][i][j] = val; //Line 8
            (*greyscale_image)[B][i][j] = val; //Line 9
        }
    }
}

// TODO: finish the implementation of this vector function
void vec_greyscale(IMAGE *image, IMAGE *greyscale_image) {
    int i, j;
    __m256 r,g,b,val;
    const __m256 den = _mm256_set_ps(3, 3, 3, 3, 3, 3, 3, 3); //because ps has 8 elements

    for (i=0; i<HEIGHT; i++) {
        for (j=0; j<WIDTH; j=j+8) { // TODO: Correct the increment to match ps
            // TODO: Line 1: load r from image
            r = _mm256_load_ps(&(*image)[R][i][j]);
            // TODO: Line 2: load g from image
            g = _mm256_load_ps(&(*image)[G][i][j]);
            // TODO: Line 3: load b from image
            b = _mm256_load_ps(&(*image)[B][i][j]);
            // TODO: Line 4: add r and g and assign it to val
            val = _mm256_add_ps(r, g);
            // TODO: Line 5: add val and b and assign it to val
	    val = _mm256_add_ps(b, val);
            // TODO: Line 6: divide val by den using vector functions and assign it to val
            val = _mm256_div_ps(val, den);
	    // TODO: Line 7: store val in (*greyscale_image)[R]
	    _mm256_store_ps(&(*greyscale_image)[R][i][j], val);
            // TODO: Line 8: store val in (*greyscale_image)[G]
            _mm256_store_ps(&(*greyscale_image)[G][i][j], val);
            // TODO: Line 9: store val in (*greyscale_image)[B]
            _mm256_store_ps(&(*greyscale_image)[B][i][j], val);
        }
    }
}

int main ()
{
    char* inputImageFileName = (char*) "marquette.bmp";
    char* outputGreyscaledImageFileName = (char*) "marquette_grey.bmp";
    char* outputVecGreyscaledImageFileName = (char*) "marquette_vec_grey.bmp";

    IMAGE *image = (IMAGE *)_mm_malloc(sizeof(IMAGE), 32); // to store the input image
    IMAGE *greyscaled_image = (IMAGE *)_mm_malloc(sizeof(IMAGE), 32); // to store the greyscaled image
    IMAGE *greyscaled_vec_image = (IMAGE *)_mm_malloc(sizeof(IMAGE), 32); // to store the vec greyscaled image

    // function from bmp.c to read the input image
    readBitmapImage((float*) image, HEIGHT, WIDTH, inputImageFileName);

    struct timeval  tv1, tv2, tv3;

    gettimeofday(&tv1, NULL); 
    // function call for normal grayscale
    greyscale(image, greyscaled_image);
    gettimeofday(&tv2, NULL);
    // function call for vector grayscale
    vec_greyscale(image, greyscaled_vec_image);
    gettimeofday(&tv3, NULL);

    // caluculating time taken by each function
    double time1 = (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv2.tv_sec - tv1.tv_sec);
    double time2 = (double) (tv3.tv_usec - tv2.tv_usec) / 1000000 + (double) (tv3.tv_sec - tv2.tv_sec);

    // function from bmp.c to write the output image
    writeBitmapImage((float*) greyscaled_image, HEIGHT, WIDTH, outputGreyscaledImageFileName);
    writeBitmapImage((float*) greyscaled_vec_image, HEIGHT, WIDTH, outputVecGreyscaledImageFileName);

    // printing time taken by each function
    printf("Normal Greyscale: time is %f \n", time1);
    printf("Vector Greyscale: time is %f \n", time2);

    _mm_free(image);
    _mm_free(greyscaled_image);
    _mm_free(greyscaled_vec_image);

    return 0;

}
