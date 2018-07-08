/* 
************************************************************************
*  integ.c:  Integration using trapezoid, Simpson and Gauss rules      *
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
*  UNIX (DEC OSF, IBM AIX): cc integ.c -lm                             *
*    			                                               *
*  comment: The derivation from the theoretical result for each method *
*           is saved in x y1 y2 y3 format.			       *
*           Program needs gauss.c in the same directory.               *
************************************************************************
*/

#include <stdio.h>
#include <math.h>
#include "gauss.c"       /* routine returns Legendre points, weights */
 
#define max_in  501                     /* max number of intervals */
#define vmin 0.0                        /* ranges of integration */
#define vmax 1.0			
#define ME 2.7182818284590452354E0      /* Euler's number */

main()
{
   int i;			 
   float result;
   float f(float);		        /* subroutine containing */   
                             		/* function to integrate */
   float trapez  (int no, float min, float max);    /* trapezoid rule */
   float simpson (int no, float min, float max);    /* Simpson's rule */
   float gaussint(int no, float min, float max);    /* Gauss' rule */
   
   FILE *output;		        /* save data in integ.dat */
   output = fopen("integ.dat","w");

   for (i=3; i<=max_in; i+=2)	    	/* Simpson's rule requires */
   { 					/* odd number of intervals */
      result = trapez(i, vmin, vmax);
      fprintf(output, "%i\t%e\t", i, fabs(result-1+1/ME));
      
      result = simpson(i, vmin, vmax);
      fprintf(output, "%e\t", fabs(result-1+1/ME));
      
      result = gaussint(i, vmin, vmax);
      fprintf(output, "%e\n", fabs(result-1+1/ME));
   }
   printf("data stored in integ.dat\n");
   fclose(output);
}
/*------------------------end of main program-------------------------*/

/* the function we want to integrate */
float f (float x)
{ 
   return (exp(-x));               
}

/* Integration using trapezoid rule */
float trapez (int no, float min, float max)
{
   int n;				
   float interval, sum=0., x;		 

   interval = ((max-min) / (no-1));
   for (n=2; n<no; n++)           	/* sum the midpoints */
   {
      x    = interval * (n-1);      
      sum += f(x)*interval;
   }
   sum += 0.5 *(f(min) + f(max)) * interval;	/* add the endpoints */

   return (sum);
}      

/* Integration using Simpson's rule */ 
float simpson (int no, float min, float max)
{  
   int n;				 
   float interval, sum=0., x;
   interval = ((max -min) /(no-1));
   
   for (n=2; n<no; n+=2)                /* loop for odd points  */
   {
       x = interval * (n-1);
       sum += 4 * f(x);
   }
   for (n=3; n<no; n+=2)                /* loop for even points  */
   {
      x = interval * (n-1);
      sum += 2 * f(x);
   }   
   sum +=  f(min) + f(max);	 	/* add first and last value */          
   sum *= interval/3.;        		/* then multilpy by interval*/
   
   return (sum);
}  

/* Integration using Gauss' rule */ 
float gaussint (int no, float min, float max)
{
   int n; 			 
   float quadra = 0.;
   double w[1000], x[1000];             /* for points and weights */
   
   gauss (no, 0, min, max, x, w);       /* returns Legendre */
   					/* points and weights */
   for (n=0; n< no; n++)
   {                               
      quadra += f(x[n])*w[n];            /* calculating the integral */
   }   
   return (quadra);                  
}
