


#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0


struct Pixel
{
	unsigned char R;
	unsigned char G;
	unsigned char B;
	/* data */
};


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