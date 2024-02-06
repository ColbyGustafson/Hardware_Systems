#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>
#include "bmp.c"

#define HEIGHT 800
#define WIDTH 800
#define DIMS 3

// compile: gcc -O3 -mavx2 -o main main.c
// execute: ./main

// TODO: Convert the following funtion blurMethod using vector intrinsics

void blurMethod(float *image_grey, float *image_output) {
    int i, j, k, l1, l2, margin = 8;
    //float val, den = 289;
    __m256d val0;
    const __m256d den0 = _mm256_set_pd(289, 289, 289, 289);
    for (i=margin; i<HEIGHT-margin; i+=8) {
        for (j=margin; j<WIDTH-margin; j+=8) {
                //val = 0;
                val0 = _mm256_set_pd(0,0,0,0);
                
                for(l1 = i-margin; l1<= i+margin; l1++) {
                    for(l2 = j-margin; l2<= j+margin; l2++) {
                        val0 = _mm256_add_pd(val0, _mm256_load_pd((double*)image_grey + l1*WIDTH + l2));
                        //val += image_grey[l1*WIDTH + l2];

                    }
                }
                //image_output[i*WIDTH + j] = val/den;
                _mm256_store_pd((double*)image_output + i*WIDTH + j, val0/den0);
        }
    }
}

/*
 converting a 3D array to 1D array for convenience
 changing the type from small int to float for convenience
 input is image 3D array, output is 1D floatImage array
 size of the output array = HEIGHT * WIDTH
 */
void convert3DTo1D( unsigned char image[HEIGHT][WIDTH][DIMS], float *image_grey)
{
    int i, j;    
    for (i=0; i<HEIGHT; i++) {
        for (j=0; j<WIDTH; j++) {
            image_grey[ i*WIDTH + j] = image[i][j][0];
        }
    }       
}

void writeToGreyScaleImage(float *output_image, unsigned char greyscale_image[HEIGHT][WIDTH][DIMS])
{
     int val;
     int i, j, k;
     
     for (i=0; i<HEIGHT; i++) {
        for (j=0; j<WIDTH; j++) {
           
           val = output_image[i*WIDTH + j];
           
           for (k=0; k<DIMS; k++) { 
                greyscale_image[i][j][k] = val;
            }
        }
    }
}


/* added simpler methods */
void blur(unsigned char image[HEIGHT][WIDTH][DIMS], 
                                      unsigned char greyscaled_image[HEIGHT][WIDTH][DIMS])
{
    // This is to store the input greyscale image output
    float *image_grey = (float *)_mm_malloc( sizeof (float) * HEIGHT * WIDTH, 32);
    // This is to store the blured greyscale image output
    float *image_output = (float *)_mm_malloc( sizeof (float) * HEIGHT * WIDTH, 32);
    
    /*
      Original image is read as 3D array of pixels with with redundant Red, Green and Blue components
      Method populates the 1D array removing redundant components
    */
    convert3DTo1D(image, image_grey);
    
    // main calculation to get greyscaling effect
    blurMethod(image_grey, image_output);
    
    // finally the 1D output is written to 3D matrix required to show bmp image
    writeToGreyScaleImage(image_output, greyscaled_image);

    _mm_free(image_grey);
    _mm_free(image_output);
}

int main()
{
    unsigned char image[HEIGHT][WIDTH][DIMS]; // to store the input image

    char* inputGreyscaledImageFileName = (char*) "marquette_grey.bmp";
    char* outputBluredImageFileName = (char*) "marquette_grey_blur.bmp";

    // function from bmp.c to read the input image
    readBitmapImage((unsigned char*) image, HEIGHT, WIDTH, inputGreyscaledImageFileName);

    unsigned char blured_image[HEIGHT][WIDTH][DIMS]; // to store the blured image

    blur(image, blured_image);
    
    // function from bmp.c to write the output image
    writeBitmapImage((unsigned char*) blured_image, HEIGHT, WIDTH, outputBluredImageFileName);

    return 0;

}
