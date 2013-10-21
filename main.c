/*
export LD_LIBRARY_PATH = $PWD
*/



#include <stdio.h>
#include <stdlib.h>
#include "libmatrix.h"

int main(int argc, char* argv[])
{
	struct Pixel **matrix;
	int x,y, xmass, ymass;
	loadMatrix("matrix.ppm", &matrix, &x, &y);
	//print_matrix(matrix,x,y);
	start_noize_delete(matrix, x, y);
	center_of_mass(matrix, x, y, &xmass, &ymass);
	printf("Img x size:%d\n", x);
	printf("Img y size:%d\n", y);
	printf("Img x mass xenter:%d\n", ymass);
	printf("Img y mass xenter:%d\n", xmass);
	return 0;
}