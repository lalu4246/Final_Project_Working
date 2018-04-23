#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

#define n 1000

double A[n][n];
double B[n][n];
double C[n][n];

void rand_matrix();

int main(int argc, char * argv[])
{
	// Update progress
	printf("Initializing matrices...\n");
	
	// Iterators
	int i, j, k, ii, kk;

	// Create random matrices
	rand_matrix();

	// Update progress
	printf("Computing matrix product...\n");
	
	// Begin clock
	double begin, end;
	double time_spent;
	begin = omp_get_wtime();

	// Compute matrix product

	double acc00, acc01, acc10, acc11;
	int ib = 20;
	int kb = 50;

#pragma omp parallel for private(i,j,k,ii,kk,acc00,acc01,acc10,acc11) shared(A,B,C)	
	for (ii = 0; ii < n; ii += ib)
	{
		for (kk = 0; kk < n; kk += kb)
		{
			for (j = 0; j < n; j += 2)
			{
				for (i = ii; i < ii + ib; i += 2)
				{
					if (kk == 0)
						acc00 = acc01 = acc10 = acc11 = 0;
					else
					{
						acc00 = C[i][j];
						acc01 = C[i][j+1];
						acc10 = C[i+1][j];
						acc11 = C[i+1][j+1];
					}	
					for (k = kk; k < kk + kb; k++)
					{
						acc00 += A[i][k]*B[k][j];
						acc01 += A[i][k]*B[k][j+1];
						acc10 += A[i+1][k]*B[k][j];
						acc11 += A[i+1][k]*B[k][j+1];
					}
					C[i][j] = acc00;
					C[i][j+1] = acc01;
					C[i+1][j] = acc10;
					C[i+1][j+1] = acc11;
				}
			}
		}
	}

	// Stop clock
	end = omp_get_wtime();
	time_spent = end - begin;
	printf("Time spent computing matrix product: %lf\n",time_spent);
	
	return 0;
}

void rand_matrix()
{
	int i, j;
	srand ( time(NULL) );
	
	for (i = 0; i < n; i++)
	{		
		for (j = 0; j < n; j++)
		{
			A[i][j] = (double) rand() / RAND_MAX;
			B[i][j] = (double) rand() / RAND_MAX;
		}
	}
}
