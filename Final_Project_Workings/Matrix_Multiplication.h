double* Matrix_Multiplication( double* Amat, double* Bmat, int Arow, int Acol, int Brow, int Bcol)
{
	/*This Function Multiplies two Matricies Assuming the Dimensions Match*/

	//Defining the Output Matrix Size
	double *Outmat;
	Outmat = (double *)malloc(sizeof(double) * Arow * Bcol);
	
	//Computing Matrix Produce
	for (int i=0;i<Arow;i++){
		for(int j=0;j<Bcol;j++){
			for(int k=0;k<Acol;k++){
				Outmat[j+i*Bcol] += Amat[k+i*Acol]*Bmat[j+k*Bcol];
			}
			
		}
	}
	return Outmat;
}
