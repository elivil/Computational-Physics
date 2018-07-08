/* 
************************************************************************
*  call.c: Creates pseudo-random numbers using drand48 or rand         *
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
*  UNIX (DEC OSF, IBM AIX): cc call.c -lm                              *
*    			                                               *
*  comment: If your compiler complains about drand48, srand48          *
*           uncomment the define statements further down.              *
************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* if you don't have drand48 uncomment the following two lines */
/*    #define drand48 1.0/RAND_MAX*rand 
      #define srand48 srand                */  
      
main()
{
   int i, seed;
   double x;
   
   printf("enter seed\n");                   	/* user plants seed */
   scanf("%i", &seed);
   
   srand48(seed);                           	/* seed drand 48 */
   
   for (i=1; i<=10; i++) 
   {
      x = drand48();              /* random number between 0 and 1 */
      printf("Your random number is: %f\n",x);
   }
}
