void Matrix_Multiplication( double* Amat, double* Bmat, int Arow, int Acol, int Brow, int Bcol, double *Outmat)
{
	/*This Function Multiplies two Matricies Assuming the Dimensions Match*/
	
	//Computing Matrix Product
	int i, j, k;
	for (i=0;i<Arow;i++){
		for(j=0;j<Bcol;j++){
			for(k=0;k<Acol;k++){
				Outmat[j+i*Bcol] += Amat[k+i*Acol]*Bmat[j+k*Bcol];
			}
			
		}
	}
}
