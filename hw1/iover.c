/* 
************************************************************************
*  over.c: Determine overflow and underflow limits                     *
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
*  UNIX (DEC OSF, IBM AIX): cc over.c 			               *
*                                                                      *
*  related information: the float.h file			       *
*  comment: very crude program which produces lots of screen output    *
************************************************************************
*/

#include <stdio.h>

#define N 1080			/* might not be big enough to cause */ 
				/* over and underflow */
main()
{
   int under=-1, over=1;			/* starting values */
   int i;

   for(i=0; i<N; i++)
   {
      under = under*2;				/* divide by two */
      over  = over*2;				/* multiply by two */
      printf("%d. under: %d over: %d \n",i+1,under,over);
   }
}