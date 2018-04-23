#include <stdio.h>
#include <omp.h>

int main(int argc, char * argv[])
{
	#pragma omp parallel
   {
     int NCPU,tid,NPR,NTHR;
	 
     /// Get the total number of virtual cores available for OpenMP!
     NCPU = omp_get_num_procs();
	 
     // Get the current thread ID in this parallel region!
     tid = omp_get_thread_num();
	 
     // Get the total number of threads available in this parallel region!
     NPR = omp_get_num_threads();
	 
     // Get the total number of threads requested at loading!
     NTHR = omp_get_max_threads();
	 
	 // Print a greeting!
     printf("%i : Hello multicore user! I am thread %i out of %i.\n",tid,tid,NPR);

	 // Only execute this on the master thread!
     if (tid == 0) {
       printf("%i : Number of Logical Cores on this Machine \t= %i\n",tid,NCPU);
       printf("%i : Number of Threads Requested in this Run \t= %i\n",tid,NTHR);
       printf("%i : Number of Threads Available in this Region \t= %i\n",tid,NPR);
	 }
			   
   }
	
	return 0;
}
