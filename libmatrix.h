#ifndef MATRIXLIB_H
#define MATRIXLIB_H

struct Pixel
{
	unsigned char R;
	unsigned char G;
	unsigned char B;
	/* data */
};

extern int loadMatrix(const char* fname, struct Pixel ***matrix, int *_x, int *_y);

extern void noize_delete(struct Pixel **matrix, int x, int y);

extern void print_matrix(struct Pixel **matrix, int x, int y);

extern void center_of_mass (struct Pixel **matrix, int x, int y, int *xmass, int *ymass);

#endif