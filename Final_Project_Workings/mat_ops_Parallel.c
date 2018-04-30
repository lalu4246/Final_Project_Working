#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "Matrix_Multiplication.h"
#include "Matrix_Addition.h"
#include "mpi.h"

int main(int argc, char * argv[])
{

	// Begin clock
	clock_t begin, end;
	double time_spent;
	begin = clock();

	FILE *AFile;
	FILE *BFile;
	FILE *CFile;
	AFile = fopen(argv[1],"r");
	BFile = fopen(argv[2],"r");
	CFile = fopen(argv[3],"r");
	
	/*Reading in the Matrix Inputs*/
	int Arow, Acol, Brow, Bcol, Crow, Ccol;
	fscanf(AFile,"%d %d", &Arow, &Acol);
	fscanf(BFile,"%d %d", &Brow, &Bcol);
	fscanf(CFile,"%d %d", &Crow, &Ccol);
	printf("Arow is: %d\nAcol is: %d\nBrow is: %d\nBcol is: %d\nCrow is: %d\nCcol is: %d\n",Arow,Acol,Brow,Bcol,Crow,Ccol);

	/*Read in the Matrix Values*/
	int i, j;
	double *Amat,*Bmat,*Cmat;


