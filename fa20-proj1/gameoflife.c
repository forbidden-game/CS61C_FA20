/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[8] = {1, 0, -1, 1, -1, 1, 0, -1};

int ring(int n, int m) {
	return (n + m) % m;
}
//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	//YOUR CODE HERE
	Color *nextState = (Color*)malloc(sizeof(Color));
	int aliveNeighboursR = 0, aliveNeighboursG = 0, aliveNeighboursB = 0;
	int isAliveR, isAliveG, isAliveB;
	int idxR, idxG, idxB;

	isAliveR = (*(image->image + row * image->cols + col))->R == 255;
	isAliveG = (*(image->image + row * image->cols + col))->G == 255;
	isAliveB = (*(image->image + row * image->cols + col))->B == 255;

	for (int i = 0; i < 8; i++) {
		int newrow = ring(row + dx[i], image->rows);
		int newcol = ring(col + dy[i], image->cols);
		if ((*(image->image + newrow * image->cols + newcol))->R == 255) {
			aliveNeighboursR++;
		}
		if ((*(image->image + newrow * image->cols + newcol))->G == 255) {
			aliveNeighboursG++;
		}
		if ((*(image->image + newrow * image->cols + newcol))->B == 255) {
			aliveNeighboursB++;
		}
	}
	idxR = 9 * isAliveR + aliveNeighboursR;
	idxG = 9 * isAliveG + aliveNeighboursG;
	idxB = 9 * isAliveB + aliveNeighboursB;

	if (rule & (1<<idxR)) {
		nextState->R = 255;
	} else {
		nextState->R = 0;
	}

	if (rule & (1<<idxG)) {
		nextState->G = 255;
	} else {
		nextState->G = 0;
	}

	if (rule & (1<<idxB)) {
		nextState->B = 255;
	} else {
		nextState->B = 0;
	}

	return nextState;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
	//YOUR CODE HERE
	int totp = image->rows * image->cols;
	Image *nextLife = (Image*) malloc(sizeof(Image));
	nextLife->cols = image->cols;
	nextLife->rows = image->rows;
	nextLife->image = (Color **) malloc(sizeof(Color*) * totp);

	for (int i = 0; i < image->rows; ++i) {
		for (int j = 0; j < image->cols; ++j) {
			nextLife->image[i * image->cols + j] = evaluateOneCell(image, i, j, rule);
		}
	}
	return nextLife;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	if (argc != 3) {
		printf("usage: ./%s filename rule\n", argv[0]);
		printf("filename is an ASCII PPM file (type P3) with maximum value 255.\n");
		printf("rule is a hex number beginning with 0x; Life is 0x1808.\n");
	}
	Image *currentLife = readData(argv[1]);
	if (currentLife == NULL) {
		return -1;
	}
	uint32_t rule;
	char *ptr;
	rule = strtol(argv[2], &ptr, 16);
	Image *nextLife = life(currentLife, rule);
	writeData(nextLife);
	freeImage(currentLife);
	freeImage(nextLife);
	return 0;
}
