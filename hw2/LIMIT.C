/* 
************************************************************************
*  limit.c: Determine machine precision e                              *
*           i.e.  the smallest e for which 1 + e .ne. 1               *
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
*  UNIX (DEC OSF, IBM AIX): cc limit.c 			               *
*                                                                      *
*  related information: the float.h file			       *
*  comment: very crude program which produces lots of screen output    *
************************************************************************
*/

#include <stdio.h>

#define N 60			 
				
main()
{
   double eps=1.0, one;				/* starting values */
   int i;

   for(i=0; i<N; i++)
   {
      eps  /= 2.;				/* divide by two */
      one=1.0+eps;			
      printf("%.18f \t %.16e \n",one, eps);
   }
}
