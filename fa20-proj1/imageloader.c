/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	//YOUR CODE HERE
	FILE *ptr = fopen(filename, "r");
	if (ptr == NULL) {
		printf("no such file.\n");
		return 0;
	}
	Image *p = (Image*)malloc(sizeof(Image));
	char p_x[3];
	int x;
	fscanf(ptr, "%s %u %u %u", p_x, &x, &p->cols, &p->rows);
	p->image = (Color**)malloc(sizeof(Color*) * p->rows * p->cols);

	int totp = p->rows * p->cols;
	
	for (int i = 0; i < totp; ++i) {
		p->image[i] = (Color*)malloc(sizeof(Color));
		fscanf(ptr, "%hhu %hhu %hhu", &p->image[i]->R, &p->image[i]->G, &p->image[i]->B);
	}
	fclose(ptr);
	return p;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE
    printf("P3\n%d %d\n255\n", image->cols, image->rows);
    Color** p = image->image;
    for (int i = 0; i < image->rows; i++) {
        for (int j = 0; j < image->cols - 1; j++) {
            printf("%3hhu %3hhu %3hhu   ", (*p)->R, (*p)->G, (*p)->B);
            p++;
        }
        printf("%3hhu %3hhu %3hhu\n", (*p)->R, (*p)->G, (*p)->B);
        p++;
    }
}

//Frees an image
void freeImage(Image *image)
{
	//YOUR CODE HERE
}