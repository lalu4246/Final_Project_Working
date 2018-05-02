double* Matrix_Addition( double* Amat, double* Bmat, int Elements, int Sign)
{
	/*This Function Adds or Subtracts two Matricies Assuming the Dimensions Match*/

	//Defining the Output Matrix Size:
	double *Outmat;
	Outmat = (double *)malloc(sizeof(double) *Elements);

	//Computing Matrix Addition or Subrraction
	#pragma omp parallel for
	for (int i = 0; i<Elements; i++){
		Outmat[i] = Amat[i]+Sign*Bmat[i];
	}
	
	return Outmat;

}
