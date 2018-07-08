/* 
************************************************************************
*  walk.c: Random walk simulation                                      *
*								       *
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
*  UNIX (DEC OSF, IBM AIX): cc walk.c -lm                              *
*    			                                               *
*  comment: If your compiler complains about drand48, srand48          *
*           uncomment the define statements further down               *
*           Data is saved as sqrt(steps), distance                     *
************************************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* if you don't have drand48 uncomment the following two lines */
/*    #define drand48 1.0/RAND_MAX*rand 
      #define srand48 srand                */ 
                        
#define SQRT2 1.4142135623730950488E0
#define max 10000
#define seed 68111

main()
{
   int i, j;
   double x, y, r[max+1];
   
   FILE *output;			/* save data in walk.dat */
   output = fopen("walk.dat","w");
   
   srand48(seed);                       /* seed the number generator */
   
   for (i=0; i<=max; i++) r[i]=0.0;     /* clear array */
   
   for (j=1; j<=100; j++)               /* average over 100 trials */
   {
      x=y=0;                            /* starting point  */
      for (i=1; i<=max; i++)
      {
         x += (drand48()-0.5)*2*SQRT2;      /* dx and dy between */
         y += (drand48()-0.5)*2*SQRT2;      /* -sqrt(2) and sqrt(2) */
         r[i] += sqrt(x*x + y*y);           /* distance from origin */
      }
   }
   
   for (i=0; i<=max; i++)		/* write results into file */
   {            
      fprintf(output, "%f\t%f\n", sqrt(i), r[i]/100.);
   }
   printf("data stored in walk.dat.\n");
   fclose(output);
}
 
