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
Color *evaluateOnePixel(Image *image, int row, int col) {
	//YOUR CODE HERE
	Color *r = (Color*) malloc(sizeof(Color));
	int LSB = image->image[row * image->cols + col]->B & 1;
	r->R = r->B = r->G = LSB * 255;
	return r;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image) {
	//YOUR CODE HERE
	int totp = image->rows * image->cols;
	Image *decoded = (Image*) malloc(sizeof(Image));
	decoded->cols = image->cols;
	decoded->rows = image->rows;
	decoded->image = (Color **) malloc(sizeof(Color*) * totp);

	for (int i = 0; i < image->rows; ++i) {
		for (int j = 0; j < image->cols; ++j) {
			decoded->image[i * image->cols + j] = evaluateOnePixel(image, i, j);
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
	if (argc != 2) {
		printf("Usage: %s <colorfile>\n", argv[0]);
		return 1;
	}
	Image *origin = readData(argv[1]);
	if (origin == NULL) {
		return -1;
	}
	Image *decoded = steganography(origin);
	writeData(decoded);
	freeImage(origin);
	freeImage(decoded);
	return 0;
}