/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				YOUR NAME HERE
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
	//YOUR CODE HERE
    Color *r = (Color*) malloc(sizeof(Color));
    if (image->image[(row - 1) * (col - 1)]->B) {
        r->R = 255;
        r->G = 255;
        r->B = 255;
    } else{
        r->R = 0;
        r->G = 0;
        r->B = 0;
    }
    return r;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	//YOUR CODE HERE
    int totp = image->rows * image->cols;
    Image *decoded = (Image*) malloc(sizeof(Image*));
    decoded->image = (Color **) malloc(sizeof(Image*) * totp);

    for (int i = 1; i < image->rows + 1; ++i) {
        for (int j = 1; j < image->cols + 1; ++j) {
           decoded->image[(i - 1) * (j - 1)] = (Color*) malloc(sizeof(Color));
           decoded->image[(i - 1) * (j - 1)] = evaluateOnePixel(image, i, j);
        }
    }
    return decoded;
}

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
    Image *origin = readData(argv[1]);
    if (origin == NULL) {
        return -1;
    }
    Image *decoded = steganography(origin);
    writeData(decoded);
    free(origin);
    free(decoded);
}
