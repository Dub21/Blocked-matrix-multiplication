#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/time.h>
#include "limits.h"
#include "string.h"



void multiply_blockMatrix(double *a, double *b, double *c, int n, int block_size)
{
	int k, j, i, jj, kk;
	for (jj = 0; jj < n; jj += block_size)
	{
		for(kk = 0; kk < n; kk += block_size)
		{
			for (i = 0; i < n; ++i)
			{
				for (j= jj; j < jj + block_size; ++j)
				{
					for (k = kk; k < kk + block_size; ++k)
					{
						c[i*n + j] += a[i*n+k] * b[k*n+j];
					}
				}
			}
		}
	}
}

void multiply_naive(double *a, double *b, double *c, int n)
{
	int i, j, k;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			for (k = 0; k < n; k++)
			{
				c[i*n + j] += a[i*n + k]*b[k*n + j];
			}
		}
	}
}

void  initializeMatrixC(double* matrix, int n)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
	    for(j = 0; j < n; j++)
	    {
	    	matrix[i*n + j] = 0;
	    }
	}
}

void readMatrix(char* filename, double* matrix, int n)
{
	int i, j;
	double x;
	FILE* fp = fopen(filename, "r");

	for (i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			fscanf(fp, "%lf", &x);
			matrix[i*n + j] = x;
		}
	}

	fclose(fp);
}

int main(int arc, char** argv)
{
	char* method = argv[1];
	int n = atoi(argv[2]);
    char *filename = argv[3];     // Notice this change, i.e. *filename
    char *filename2 = argv[4];
    int block_size;
    if (strcmp(method,"blocked") == 0)
    {
    	block_size = atoi(argv[5]);
    }

    double* a = (double *) calloc(sizeof(double), n*n);
    double* b = (double *) calloc(sizeof(double), n*n);
    double* c = (double *) calloc(sizeof(double), n*n);

    readMatrix(filename, a, n);
    readMatrix(filename2, b, n);
    initializeMatrixC(c,n);

    clock_t begin, end;
    double time_spent;

    begin = clock();
    if (strcmp(method,"blocked") == 0)
    {
    	 multiply_blockMatrix(a,b,c,n,block_size);
    }
    else
    {
    	multiply_naive(a, b, c, n);
    }
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%lf", time_spent);

    return 0;
}


