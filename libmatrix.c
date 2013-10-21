#include "libmatrix.h"

#define true 1
#define false 0



int loadMatrix(const char* fname, struct Pixel ***matrix, int *_x, int *_y)
{
	FILE *f = fopen(fname, "r");
	if (f == NULL)
	{
		return -1;
	}
	//считывание двух несущественных строкеч

	char void_buf[100];
	fgets(void_buf,100,f);
	fgets(void_buf,100,f);

	int x,y;
	unsigned char data;
	fscanf(f,"%d", &x);
	fscanf(f, "%d", &y);
	*matrix = malloc(y*sizeof(struct Pixel*));
	for(int i = 0; i < y; i++)
	{
		(*matrix)[i] = malloc(x*sizeof(struct Pixel));
		for(int j = 0; j < x; j++)
		{
			fscanf(f,"%hhu", &data);
			(*matrix)[i][j].R = data;
			
			fscanf(f,"%hhu", &data);
			(*matrix)[i][j].G = data;

			fscanf(f,"%hhu", &data);
			(*matrix)[i][j].B = data;
		}
	}
	*_x = x;
	*_y = y;
	return 0;
}


//delete single black pixels
void noize_delete(struct Pixel **matrix, int x, int y)
{
	int is_Single = true;
	for(int i = 0; i < y; i++)
	{
		for(int j = 0; j < x; j++)
		{
			if(0 == matrix[i][j].B)
			{
				is_Single = true;
				if(i != 0)
				{
					if(0 == matrix[i-1][j].B)
						is_Single = false;
				}
				if(i != y - 1)
				{
					if(0 == matrix[i+1][j].B)
						is_Single = false;
				}
				if(j != 0)
				{
					if(0 == matrix[i][j-1].B)
						is_Single = false;
				}
				if(j != x - 1)
				{
					if(0 == matrix[i][j+1].B)
						is_Single = false;
				}
				if(is_Single)
				{
					printf("delete at %d %d",i,j);
					matrix[i][j].R =255;
					matrix[i][j].G =255;
					matrix[i][j].B =255;
				}	
			}
		}
	}
}


void print_matrix(struct Pixel **matrix, int x, int y)
{
	for(int i = 0; i < y; i++)
	{
		for(int j = 0; j < x; j++)
		{
			if(0 == matrix[i][j].B)
			{
				printf("0");
			}else{
				printf("1");
			}
		}
		printf("\n");
	}
}

void center_of_mass (struct Pixel **matrix, int x, int y, int *xmass, int *ymass)
{

	double Xsum = 0;
	double Ysum = 0;
	double TotalMass = 0;


	for(int i = 0; i < y; i++)
	{
		for(int j = 0; j < x; j++)
		{
			if(0 == matrix[i][j].B)
			{
				//printf("%a\n", TotalMass);
				TotalMass = TotalMass + 1;
				Xsum += i;
				Ysum += j;
			}
		}
	}
	
	if(TotalMass >= 1)
	{
		*xmass = Xsum/TotalMass;
		*ymass = Ysum/TotalMass;
	}else{
		*xmass = 0;
		*ymass = 0;
	}
}

void * noize_delete_parallel(void *ptr)
{
	struct TMatrix *matrix  = (struct TMatrix *) ptr;
	int is_Single = true;
	for(int i = matrix->y_from; i < matrix->y_to; i++)
	{
		for(int j = matrix->x_from; j < matrix->x_to; j++)
		{
			if(0 == matrix->matrix[i][j].B)
			{
				is_Single = true;
				if(i != matrix->y_from)
				{
					if(0 == matrix->matrix[i-1][j].B)
						is_Single = false;
				}
				if(i != matrix->y_to - 1)
				{
					if(0 == matrix->matrix[i+1][j].B)
						is_Single = false;
				}
				if(j != matrix->x_from)
				{
					if(0 == matrix->matrix[i][j-1].B)
						is_Single = false;
				}
				if(j != matrix->x_to - 1)
				{
					if(0 == matrix->matrix[i][j+1].B)
						is_Single = false;
				}
				if(is_Single)
				{
					printf("delete at %d %d\n",i,j);
					matrix->matrix[i][j].R =255;
					matrix->matrix[i][j].G =255;
					matrix->matrix[i][j].B =255;
				}	
			}
		}
	}
}

void start_noize_delete(struct Pixel **m, int x, int y)
{

	pthread_t thread1, thread2;

	struct TMatrix m1, m2;
	m1.matrix = m;
	m1.x_from=0;
	m1.x_to=x/2;
	m1.y_from=0;
	m1.y_to=y/2;

	m2.matrix = m;
	m2.x_from=x/2+1;
	m2.x_to=x;
	m2.y_from=y/2+1;
	m2.y_to=y;

	struct TMatrix * pm1, *pm2;
	pm1 = &m1;
	pm2 = &m2;

	int iret1, iret2;
	iret1 = pthread_create( &thread1, NULL, noize_delete_parallel, (void*) pm1);
	iret2 = pthread_create( &thread2, NULL, noize_delete_parallel, (void*) pm2);
	pthread_join( thread1, NULL);
	pthread_join( thread2, NULL);
}