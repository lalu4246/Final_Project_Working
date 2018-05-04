Allfiles:
	gcc -o NoOptimization mat_ops_Origonal.c
	gcc -o Opt_Ext_Lib mat_ops_ExtLib.c -lblas -lgfortran
	gcc -o Opt_Cache mat_ops_OptCache.c 
	gcc -o Opt_Parallel -fopenmp mat_ops_Parallel.c
	export OMP_NUM_THREADS=4
