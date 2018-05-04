#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char * argv[])
{
	FILE *AFile;
	FILE *BFile;
	FILE *CFile;
	AFile = fopen(argv[1],"w");
	BFile = fopen(argv[2],"w");
	CFile = fopen(argv[3],"w");

	int n = 1000;

	//Preallocate Mats
	double *A,*B,*C;
	A = (double *)malloc(sizeof(double) * n * n);
	B = (double *)malloc(sizeof(double) * n * n);
	C = (double *)malloc(sizeof(double) * n * n);
		
	for (int i = 0; i < n; i++)
	{		
		for (int j = 0; j < n; j++)
		{
			A[j+i*n] = (double) 100*rand() / RAND_MAX;
			B[j+i*n] = (double) 100*rand() / RAND_MAX;
			C[j+i*n] = (double) 100*rand() / RAND_MAX;
		}
	}
	
	fprintf(AFile, "%d %d\n",n,n);
	fprintf(BFile, "%d %d\n",n,n);
	fprintf(CFile, "%d %d\n",n,n);
	
	for (int i = 0;i<n;i++){
		for(int j = 0;j<n;j++){				
			fprintf(AFile,"%lf ",A[j+i*n]);
			fprintf(BFile,"%lf ",B[j+i*n]);
			fprintf(CFile,"%lf ",C[j+i*n]);

				
		}
		fprintf(AFile, "\n");
		fprintf(BFile, "\n");
		fprintf(CFile, "\n");
	}
	fclose(AFile);
	fclose(BFile);
	fclose(CFile);

	

}
