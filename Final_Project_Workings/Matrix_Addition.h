void Matrix_Addition( double* Amat, double* Bmat, int Elements, int Sign, double *Outmat)
{
	/*This Function Adds or Subtracts two Matricies Assuming the Dimensions Match*/

	//Computing Matrix Addition or Subrraction
	for (int i = 0; i<Elements; i++){
		Outmat[i] = Amat[i]+Sign*Bmat[i];
	}

}
