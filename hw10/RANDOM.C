/* 
************************************************************************
*  random.c:    A simple random number generator, not for serious work *
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
*  UNIX (DEC OSF, IBM AIX): cc random.c                                *
*        							       *  
*  comment: plot without connecting datapoints with lines              *
************************************************************************
*/
#include <stdio.h>

#define max 1000                      /* number of numbers generated */
#define seed 11                       /* seed for number generator */

main ()
{
   int i, old, newx, newy;
   
   FILE *output;		      /* save data in badrand.dat */
   output = fopen("badrand.dat","w");
   
   old = seed;                        /* the seed */

   for (i=0; i<max; i++)              /* generating #max numbers */
   {
      newx = (57*old+1) % 256;        /* x-coordinate */
      newy = (57*newx+1) % 256;       /* y-coordinate */
      fprintf (output, "%i\t%i\n", newx, newy);
      old  = newy;
   }
   printf("data stored in badrand.dat.\n");
   fclose(output);
}
 
