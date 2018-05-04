#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

//Define The Matrix Multiplication Function
void Matrix_Multiplication_OptCache( double* Amat, double* Bmat, int Arow, int Acol, int Brow, int Bcol, double *Outmat)
{
	/*This Function Multiplies two Matricies Assuming the Dimensions Match*/
	
	double acc00,acc01,acc10,acc11;
	
	//Setting Up Cache Size
	int cache = 20;
	
	//Computing Matrix Product
	int l, i, j, k;
	for(l = 0;l<Arow;l+=cache){
		for (j=0;j<Brow;j+=2){
			for(i=l;i<l+cache;i+=2){
				acc00 = acc01 = acc10 = acc11 = 0;
				for(k=0;k<Acol;k++){
					acc00 += Amat[k+i*Acol]*Bmat[j+k*Bcol];
					acc01 += Amat[k+i*Acol]*Bmat[(j+1)+k*Bcol];
					acc10 += Amat[k+(i+1)*Acol]*Bmat[j+k*Bcol];
					acc11 += Amat[k+(i+1)*Acol]*Bmat[(j+1)+k*Bcol];
				}
				Outmat[j+i*Bcol] = acc00;
				Outmat[(j+1)+i*Bcol] = acc01;
				Outmat[j+(i+1)*Bcol] = acc10;
				Outmat[(j+1)+(i+1)*Bcol] = acc11;
			
			}
		}
	}
}

//Defining the Matrix Addition Function
void Matrix_Addition( double* Amat, double* Bmat, int Elements, int Sign, double *Outmat)
{
	/*This Function Adds or Subtracts two Matricies Assuming the Dimensions Match*/

	//Computing Matrix Addition or Subrraction
	for (int i = 0; i<Elements; i++){
		Outmat[i] = Amat[i]+Sign*Bmat[i];
	}

}

//BEGIN THE MAIN FUNCTION

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

	//The following code can be uncommented to output the A matrix.
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

	if (Acol != Brow || Bcol != Crow){//Check to see if this operation can be completed.
		printf("The matrix operation ABC cannot be computed\n");
		fprintf(File1,"This matrix operation could not be completed due to matrix dimension mismatch");
	}else{
		//Defining Output Matrix Size
		double *Outmat1,*Outmat2;
		Outmat1 = (double *)malloc(sizeof(double) * Bcol * Arow);
		Outmat2 = (double *)malloc(sizeof(double) * Ccol * Arow);
		
		//Computing Operation
		Matrix_Multiplication_OptCache(Amat,Bmat,Arow,Acol,Brow,Bcol,Outmat1);
		Matrix_Multiplication_OptCache(Outmat1,Cmat,Arow,Bcol,Crow,Ccol,Outmat2);

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

	if (Acol != Brow || (Arow != Crow && Bcol != Ccol)){//Check to see if this operation can be completed.
		printf("The matrix operation AB+C cannot be computed\n");
		fprintf(File2,"This matrix operation could not be completed due to matrix dimension mismatch");
	}else{
		//Defining Output Matrix Size
		double *Outmat1, *Outmat2;
		Outmat1 = (double *)malloc(sizeof(double) * Bcol * Arow);
		Outmat2 = (double *)malloc(sizeof(double) * Ccol * Crow);

		//Computing Operation
		
		int Elements = Crow*Ccol;
		int Sign = 1;
		Matrix_Multiplication_OptCache(Amat, Bmat, Arow, Acol, Brow, Bcol,Outmat1);
		Matrix_Addition(Outmat1, Cmat, Elements, Sign,Outmat2);

		//Output AB+C Result to a File
		for (i = 0;i<Arow;i++){
			for(j = 0;j<Bcol;j++){
				if (j == (Bcol-1)){				
					fprintf(File2,"%lf\n",Outmat2[j+i*Bcol]);
				}
				else{
					fprintf(File2,"%lf,",Outmat2[j+i*Bcol]);
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
		//Defining Matrix Output Size
		double *Outmat1,*Outmat2;
		Outmat1 = (double *)malloc(sizeof(double) * Acol * Arow);
		Outmat2 = (double *)malloc(sizeof(double) * Acol * Arow);
		
		//Computing Operation
		int Elements = Arow*Acol;
		int Sign = 1;
		Matrix_Multiplication_OptCache(Bmat, Cmat, Brow, Bcol, Crow, Ccol,Outmat1);
		Matrix_Addition(Outmat1, Amat, Elements, Sign,Outmat2);

		//Output A+BC Result to a File
		for (i = 0;i<Arow;i++){
			for(j = 0;j<Acol;j++){
				if (j == (Acol-1)){				
					fprintf(File3,"%lf\n",Outmat2[j+i*Acol]);
				}
				else{
					fprintf(File3,"%lf,",Outmat2[j+i*Acol]);
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
		//Defining the Output Matrix Size
		double *Outmat1,*Outmat2;
		Outmat1 = (double *)malloc(sizeof(double) * Ccol * Crow);
		Outmat2 = (double *)malloc(sizeof(double) * Ccol * Crow);

		//Computing Operation
		int Elements = Ccol*Crow, Sign = -1;
		Matrix_Multiplication_OptCache(Amat,Bmat,Arow,Acol,Brow,Bcol,Outmat1);
		Matrix_Addition(Outmat1,Cmat,Elements,Sign,Outmat2);

		//Output AB-C Result to a File
		for (i = 0;i<Crow;i++){
			for(j = 0;j<Ccol;j++){
				if (j == (Ccol-1)){				
					fprintf(File4,"%lf\n",Outmat2[j+i*Ccol]);
				}
				else{
					fprintf(File4,"%lf,",Outmat2[j+i*Ccol]);
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
		//Defingin Output Matrix Size
		double *Outmat1,*Outmat2;
		Outmat1 = (double *)malloc(sizeof(double) * Acol * Arow);
		Outmat2 = (double *)malloc(sizeof(double) * Acol * Arow);
		
		//Computing Matrix Operations
		int Elements = Acol*Arow, Sign = -1;
		Matrix_Multiplication_OptCache(Bmat,Cmat,Brow,Bcol,Crow,Ccol,Outmat1);
		Matrix_Addition(Amat,Outmat1,Elements, Sign,Outmat2);

		//Output A-BC Result to a File
		for (i = 0;i<Arow;i++){
			for(j = 0;j<Acol;j++){
				if (j == (Acol-1)){				
					fprintf(File5,"%lf\n",Outmat2[j+i*Acol]);
				}
				else{
					fprintf(File5,"%lf,",Outmat2[j+i*Acol]);
				}
				
			}
		}
		
		
	}
	fclose(File5);
	// Stop clock
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Time spent computing Original Code: %lf [sec]\n",time_spent);
}
