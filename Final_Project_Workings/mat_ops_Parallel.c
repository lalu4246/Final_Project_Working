#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "Matrix_Multiplication.h"
#include "Matrix_Addition.h"
#include <omp.h>

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

//Reading in Matrix A
    	Amat = (double *)malloc(sizeof(double) * Acol * Arow);
	for (i = 0; i < Arow; i++){
        	for (j = 0; j < Acol; j++){
			fscanf(AFile, "%lf", &Amat[j+i*Acol]);
		}
	}
	/*for (i = 0; i <  Arow; i++){
        	for (j = 0; j < Acol; j++){
            		printf("%lf ", Amat[j+i*Acol]);
		}
	}*/

//Reading in Matrix B
    	Bmat = (double *)malloc(sizeof(double) * Bcol * Brow);
	for (i = 0; i < Brow; i++){
        	for (j = 0; j < Bcol; j++){
			fscanf(BFile, "%lf", &Bmat[j+i*Bcol]);
		}
	}
	
//Reading in Matrix C
    	Cmat = (double *)malloc(sizeof(double) * Ccol * Crow);
	for (i = 0; i < Crow; i++){
        	for (j = 0; j < Ccol; j++){
			fscanf(CFile, "%lf", &Cmat[j+i*Ccol]);
		}
	}

// Performing the Operation ABC
			
	//Setup Output File Name
	char String1[15];
	strcpy(String1,argv[1]);
	strcat(String1,"_mult_");
	strcat(String1,argv[2]);
	strcat(String1,"_mult_");
	strcat(String1,argv[3]);
	FILE *File1 = fopen(String1,"w");

	if (Acol != Brow || Bcol != Crow){
		printf("The matrix operation ABC cannot be computed\n");
		fprintf(File1,"This matrix operation could not be completed due to matrix dimension mismatch");
	}else{
		double *Outmat1,*Outmat2;
		Outmat1 = (double *)malloc(sizeof(double) * Bcol * Arow);
		Outmat2 = (double *)malloc(sizeof(double) * Ccol * Arow);
		cblas_dgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,Arow,Bcol,Acol,1,Amat,Acol,Bmat,Bcol,0.0,Outmat1,Bcol);
		cblas_dgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,Arow,Ccol,Bcol,1,Outmat1,Bcol,Cmat,Ccol,0.0,Outmat2,Ccol);

		//Output ABC Result to a File
		for (i = 0;i<Arow;i++){
			for(j = 0;j<Ccol;j++){
				if (j == (Ccol-1)){				
					fprintf(File1,"%lf\n",Outmat2[j+i*Ccol]);
				}
				else{
					fprintf(File1,"%lf,",Outmat2[j+i*Ccol]);
				}
				
			}
		}
		fclose(File1);
	}

// Performing the Operation AB+C

	//Setup Output File Name
	char String2[15];
	strcpy(String2,argv[1]);
	strcat(String2,"_mult_");
	strcat(String2,argv[2]);
	strcat(String2,"_plus_");
	strcat(String2,argv[3]);
	FILE *File2 = fopen(String2,"w");

	if (Acol != Brow || (Arow != Crow && Bcol != Ccol)){
		printf("The matrix operation AB+C cannot be computed\n");
		fprintf(File2,"This matrix operation could not be completed due to matrix dimension mismatch");
	}else{
		double *Outmat1;
		Outmat1 = (double *)malloc(sizeof(double) * Bcol * Arow);
		Outmat1 = Cmat;
		cblas_dgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,Arow,Bcol,Acol,1,Amat,Acol,Bmat,Bcol,1,Outmat1,Ccol);

		//Output AB+C Result to a File
		for (i = 0;i<Arow;i++){
			for(j = 0;j<Bcol;j++){
				if (j == (Bcol-1)){				
					fprintf(File2,"%lf\n",Outmat1[j+i*Bcol]);
				}
				else{
					fprintf(File2,"%lf,",Outmat1[j+i*Bcol]);
				}
				
			}
		}
		fclose(File2);
	}
// Performing the Operation A+BC

	//Setup Output File Name
	char String3[15];
	strcpy(String3,argv[1]);
	strcat(String3,"_plus_");
	strcat(String3,argv[2]);
	strcat(String3,"_mult_");
	strcat(String3,argv[3]);
	FILE *File3 = fopen(String3,"w");

	if (Bcol != Crow || (Arow != Brow && Acol != Ccol)){
		printf("The matrix operation A+BC cannot be computed\n");
		fprintf(File3,"This matrix operation could not be completed due to matrix dimension mismatch");
	}else{
		double *Outmat1;
		Outmat1 = (double *)malloc(sizeof(double) * Acol * Arow);
		Outmat1 = Amat;
		cblas_dgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,Brow,Ccol,Bcol,1,Bmat,Bcol,Cmat,Ccol,1,Outmat1,Acol);

		//Output A+BC Result to a File
		for (i = 0;i<Arow;i++){
			for(j = 0;j<Acol;j++){
				if (j == (Acol-1)){				
					fprintf(File3,"%lf\n",Outmat1[j+i*Acol]);
				}
				else{
					fprintf(File3,"%lf,",Outmat1[j+i*Acol]);
				}
				
			}
		}
		fclose(File3);
		
	}

// Performing the Operation AB-C

	//Setup Output File Name
	char String4[15];
	strcpy(String4,argv[1]);
	strcat(String4,"_mult_");
	strcat(String4,argv[2]);
	strcat(String4,"_minus_");
	strcat(String4,argv[3]);
	FILE *File4 = fopen(String4,"w");

	if (Acol != Brow || (Arow != Crow && Bcol != Ccol)){
		printf("The matrix operation AB-C cannot be computed\n");
		fprintf(File4,"This matrix operation could not be completed due to matrix dimension mismatch");
	}else{
		double *Outmat1;
		Outmat1 = (double *)malloc(sizeof(double) * Ccol * Crow);
		Outmat1 = Cmat;
		cblas_dgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,Arow,Bcol,Acol,1,Amat,Acol,Bmat,Bcol,-1,Outmat1,Ccol);

		//Output AB-C Result to a File
		for (i = 0;i<Crow;i++){
			for(j = 0;j<Ccol;j++){
				if (j == (Ccol-1)){				
					fprintf(File4,"%lf\n",Outmat1[j+i*Ccol]);
				}
				else{
					fprintf(File4,"%lf,",Outmat1[j+i*Ccol]);
				}
				
			}
		}
		fclose(File4);

	}

// Performing the Operation A-BC

	//Setup Output File Name
	char String5[15];
	strcpy(String5,argv[1]);
	strcat(String5,"_minus_");
	strcat(String5,argv[2]);
	strcat(String5,"_mult_");
	strcat(String5,argv[3]);
	FILE *File5 = fopen(String5,"w");

	if (Bcol != Crow || (Arow != Brow && Acol != Ccol)){
		printf("The matrix operation A-BC cannot be computed\n");
		fprintf(File5,"This matrix operation could not be completed due to matrix dimension mismatch");
	}else{
		double *Outmat1;
		Outmat1 = (double *)malloc(sizeof(double) * Acol * Arow);
		Outmat1 = Amat;
		cblas_dgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,Brow,Ccol,Bcol,1,Bmat,Bcol,Cmat,Ccol,-1,Outmat1,Acol);

		//Output A-BC Result to a File
		for (i = 0;i<Arow;i++){
			for(j = 0;j<Acol;j++){
				if (j == (Acol-1)){				
					fprintf(File5,"%lf\n",Outmat1[j+i*Acol]);
				}
				else{
					fprintf(File5,"%lf,",Outmat1[j+i*Acol]);
				}
				
			}
		}
		fclose(File5);
		// Stop clock
		end = clock();
		time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		printf("Time spent computing External Library Code: %lf [sec]\n",time_spent);
		
	}
}
