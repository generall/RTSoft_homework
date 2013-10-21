#ifndef MATRIXLIB_H
#define MATRIXLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct Pixel
{
	unsigned char R;
	unsigned char G;
	unsigned char B;
	/* data */
};

struct TMatrix
{
	struct Pixel **matrix;
	int x_from;
	int y_from;
	int x_to;
	int y_to;
	/* data */
};

extern int loadMatrix(const char* fname, struct Pixel ***matrix, int *_x, int *_y);

extern void noize_delete(struct Pixel **matrix, int x, int y);

extern void print_matrix(struct Pixel **matrix, int x, int y);

extern void center_of_mass (struct Pixel **matrix, int x, int y, int *xmass, int *ymass);

extern void * noize_delete_parallel(void *ptr);

extern void start_noize_delete(struct Pixel **m, int x, int y);

#endif