#include <stdio.h>
#include <stdlib.h>
#include "bmp.c"
#include <immintrin.h>

#define HEIGHT 800
#define WIDTH 800
#define DIMS 3

// compile: gcc -O3 -mavx2 -o main main.c
// execute: ./main

/*
 The following greyscale method is broken down into 3 functions:
  convert3DTo2D -> greyscaleInFloat -> writeToGreyScaleImage
*/
void greyscale(unsigned char image[HEIGHT][WIDTH][DIMS], 
              unsigned char greyscale_image[HEIGHT][WIDTH][DIMS]) {
    int i, j, k, val;
    for (i=0; i<HEIGHT; i++) {
        for (j=0; j<WIDTH; j++) {
            val = ((image[i][j][0] + image[i][j][1] + image[i][j][2])/3 ) %255;
            for (k=0; k<DIMS; k++) { 
                greyscale_image[i][j][k] = val;
            }
        }
    }
} 


/*
 converting a 3D array to 1D array for convenience
 changing the type from small int to float for convenience
 input is image 3D array, output is 1D floatImage array
 size of the output array = HEIGHT * WIDTH * DIMS
 */
void convert3DTo2D( unsigned char image[HEIGHT][WIDTH][DIMS], float *image_r,
                    float *image_g, float *image_b)
{
    int i, j;
    int outputCounter = 0;
    
    for (i=0; i<HEIGHT; i++) {
        for (j=0; j<WIDTH; j++) {
 
            image_r[ i*WIDTH + j] = image[i][j][0];
            image_g[ i*WIDTH + j] = image[i][j][1];
            image_b[ i*WIDTH + j] = image[i][j][2];
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


// TODO: Modify this function to vectorize with intrinsics
void greyscaleInFloat(float *image_r, float *image_g, float *image_b, 
                             float *image_output) 
{
    int i, j, k;
    __m256 r,g,b, val;
    const __m256 den = _mm256_set_ps(3, 3, 3, 3, 3, 3, 3, 3);
    
    for (i=0; i<HEIGHT; i++) {
        for (j=0; j<WIDTH; j=j+8) {
           r = _mm256_load_ps(&image_r[i * WIDTH + j]);
	   g = _mm256_load_ps(&image_g[i * WIDTH + j]);
	   b = _mm256_load_ps(&image_b[i * WIDTH + j]);

	   val = _mm256_add_ps(r, g);
	   val = _mm256_add_ps(val, b);
	   val = _mm256_div_ps(val, den);

	   _mm256_store_ps(&image_output[i * WIDTH + j],val );
               
           // image_output[i * WIDTH + j] = ((image_r[i * WIDTH + j] + image_g[i * WIDTH + j] 
           //                                   + image_b[i * WIDTH + j])/3 );
            
        }
    }
}


/* added simpler methods */
void greyscaleMethod(unsigned char image[HEIGHT][WIDTH][DIMS], 
                                      unsigned char greyscaled_image[HEIGHT][WIDTH][DIMS])
{
    float *image_r = (float *)_mm_malloc( sizeof (float) * HEIGHT * WIDTH, 32);
    float *image_g = (float *)_mm_malloc( sizeof (float) * HEIGHT * WIDTH, 32);
    float *image_b = (float *)_mm_malloc( sizeof (float) * HEIGHT * WIDTH, 32);
    
    /*
      Original image is read as 3D array of pixels with Red, Green and Blue components
      Method populates the 3 arrays for red (r), green (g) and blue (b) components
    */
    convert3DTo2D(image, image_r, image_g, image_b);
    
    // This is to store the greyscale image output
    float *image_output = (float *)_mm_malloc( sizeof (float) * HEIGHT * WIDTH, 32);
    
    // main calculation to get greyscaling effect
    greyscaleInFloat(image_r, image_g, image_b, image_output);
    
    // finally the 1D output is written to 3D matrix required to show bmp image
    writeToGreyScaleImage(image_output, greyscaled_image);

    _mm_free(image_r);
    _mm_free(image_g);
    _mm_free(image_b);
    _mm_free(image_output);
}

void blur(unsigned char image[HEIGHT][WIDTH][DIMS], unsigned char blur_image[HEIGHT][WIDTH][DIMS]) {
    int i, j, k, l1, l2, val, margin = 4;
    for (i=margin; i<HEIGHT-margin; i++) {
        for (j=margin; j<WIDTH-margin; j++) {
            for (k=0; k<DIMS; k++) {
                val = 0;
                for(l1 = i-margin; l1<= i+margin; l1++) {
                    for(l2 = j-margin; l2<= j+margin; l2++) {
                        val += image[l1][l2][k];
                    }
                }

                blur_image[i][j][k] = (val/81)%255;
            }
        }
    }
}

int main()
{
    unsigned char image[HEIGHT][WIDTH][DIMS]; // to store the input image

    char* inputImageFileName = (char*) "marquette.bmp";
    char* outputGreyscaledImageFileName = (char*) "marquette_grey.bmp";
    char* outputBluredImageFileName = (char*) "marquette_blur.bmp";

    // function from bmp.c to read the input image
    readBitmapImage((unsigned char*) image, HEIGHT, WIDTH, inputImageFileName);

    unsigned char greyscaled_image[HEIGHT][WIDTH][DIMS]; // to store the greyscaled image
    unsigned char blured_image[HEIGHT][WIDTH][DIMS]; // to store the blured image

    // Changed here
    greyscaleMethod(image, greyscaled_image);

    blur(image, blured_image);

    // function from bmp.c to write the output image
    writeBitmapImage((unsigned char*) greyscaled_image, HEIGHT, WIDTH, outputGreyscaledImageFileName);
    
    // function from bmp.c to write the output image
    writeBitmapImage((unsigned char*) blured_image, HEIGHT, WIDTH, outputBluredImageFileName);

    return 0;

}
