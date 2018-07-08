#include<stdio.h>
#define size 3                                /* dimension of matrix */

extern "C" { extern void sgesv_(int *, int *, float [], int *, 
			       int [], float [], int *, int *) ; }

int i, j , c1, c2, pivot[size], ok;
float A[size][size], b[size], AT[size*size];

main()
{

  /* Matrix A */
  
   A[0][0] = 3.1; A[0][1] =  1.3; A[0][2] = -5.7;
   A[1][0] = 1.0; A[1][1] = -6.9; A[1][2] =  5.8;        
   A[2][0] = 3.4; A[2][1] =  7.2; A[2][2] = -8.8;       

  /* vector b */
  
   b[0] = -1.3;
   b[1] = -0.1;
   b[2] =  1.8;
   
   for (i=0; i<size; i++)	     	/* transform the matrix so */ 
   {                                    /* we can pass it to Fortran */         
     for(j = 0 ; j < size ; j += 1) AT[j + size*i] = A[j][i];           
   }                                                  

   c1 = size; 		/* define variable so we can pass pointer */                       
   c2 = 1;              /* to these variables to the routine */    

   sgesv_(&c1, &c2, AT, &c1, pivot, b, &c1, &ok); 
   
      /* parameters in the order as they appear in the function call: */
      /* order of matrix A, number of right hand sides (b), matrix A, */
      /* leading dimension of A, array records pivoting, */
      /* result vector b on entry, x on exit, leading dimension of b */
      /* return value =0 for success*/ 
   
   if (!ok)
   {                                             
      for (j=0; j<size; j++) printf("%e\n", b[j]);	/* print x */
   }
   else printf("An error occurred\n");
}
