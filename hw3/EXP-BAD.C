/* 
************************************************************************
*  exp-bad.c: A bad algorithm for calculating exponential              *
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
*  UNIX (DEC OSF, IBM AIX): cc exp-bad.c -lm			       *
*                                                                      *
*  related programs: exp-good.c                                        *
************************************************************************
*/
#include <stdio.h>		 
#include <math.h>               

#define min 1E-10                               /* limit for accuracy */
#define max 10                                  /* maximum for x */
#define step 0.1                                /* intervals */

main ()
{
   double sum, x, up, down; 				 
   int i,j;
   
   FILE *output;			 /* save results in */
   output=fopen("exp-bad.dat", "w");	 /* exp-bad.dat */
   
   for (x=0.0; x<=max; x+=step)		 /* step through x */
   {
      sum = 1.;				 /* reset variables */
      i   = 0;
      
      do                                 /* sum terms until accuracy */
      {					 /* is reached */
         i++;
         up = down = 1;                  /* reset variables */
         for(j=1; j<=i; j++)
         {
            up   *= -x;                  /* numerator */
            down *= j;                   /* denominator */
         }
      sum += up/down;
      }while( (sum == 0) || ((fabs ((up/down)/sum)) > min) );
      
      fprintf(output, "%f\t%e\n", x, sum);   
   }
   printf("results saved in exp-bad.dat\n");		 
   fclose(output);
}			 
