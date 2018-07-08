/* 
************************************************************************
*  exp-good.c: A good algorithm for calculating exponential            *
*                                                                      *
*  taken from: "Projects in Computational Physics" by Landau and Paez  * 
*	       copyrighted by John Wiley and Sons, New York            *      
*                                                                      *
*  written by: students in PH465/565, Computational Physics,           *
*	       at Oregon State University                              *
*              code copyrighted by RH Landau                           *
*  supported by: US National Science Foundation, Northwest Alliance    *
*                for Computational Science and Engineering (NACSE),    *
*                US Department of Energy 	                       *
*								       *
*  UNIX (DEC OSF, IBM AIX): cc exp-good.c -lm			       *
*                                                                      *
*  related programs: exp-bad.c.c                                       *
************************************************************************
*/

#include <stdio.h>
#include <math.h>

#define min 1E-10                      	    /* limit for accuracy */
#define max 10.                             /* maximum for x */
#define step 0.1                            /* interval */

main ()
{
   double x, sum, element;				 
   int n;					 

   FILE *output;		           /* save results in */
   output=fopen("exp-good.dat", "w");      /* exp-good.dat */
   
   for (x=0.0; x<=max; x+=step)
   {
      sum = element = 1.;                  /* reset variables  */
      n   = 0;
      do                                   /* sum terms until */
      {                                    /* accuracy is reached */
         n++; 
         element *= -x/n;                  /* calculate next element */
         sum += element;
      }while ((sum == 0) || (fabs(element/sum) > min));
      
      fprintf(output, "%f\t%e\n", x, sum);
   }
   printf("results saved in exp-good.dat\n");			
   fclose(output);
}			
