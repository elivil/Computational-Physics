/* 
************************************************************************
*  fit.c:    Least square fit to decay spectrum                        *
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
*  UNIX (DEC OSF, IBM AIX): cc fit.c -lm                               *
*    			                                               *
************************************************************************
*/
#include <stdio.h>
#include <math.h>

#define data 12				/* number of data points */

main()
{
   int i, j;
   double s, sx, sy, sxx, sxy, delta, inter, slope;
   double x[data], y[data], d[data];

   for (i=0; i<data; i++) x[i]=i*10+5;		/* input data x */

   y[0]=32; y[1]=17;  y[2]=21; y[3]=7; 	        /* input data y */ 
   y[4]=8;  y[5]=6;   y[6]=5;  y[7]=2;          /* y[9] set to 0.1 */
   y[8]=2;  y[9]=0.1; y[10]=4; y[11]=1;         /* so that log exists */

   for (i=0; i<data; i++) d[i]=1.;		/* input data delta y */
  						/* estimate */
   
   for (i=0;i<data;i++) y[i]=log(y[i]);	  	/* log(y[i]) for */ 
						/* exponential fit */		
   s=sx=sy=sxx=sxy=0;				/* reset sums */		

   for (i=0;i<data;i++)				/* calculating sums */
   {
      s   +=         1 / (d[i]*d[i]);
      sx  +=      x[i] / (d[i]*d[i]);
      sy  +=      y[i] / (d[i]*d[i]); 
      sxx += x[i]*x[i] / (d[i]*d[i]); 
      sxy += x[i]*y[i] / (d[i]*d[i]);
   } 

   delta = s*sxx-sx*sx;
   slope=  (s*sxy-sx*sy) / delta;		  /* calculating all */
   inter=(sxx*sy-sx*sxy) / delta;		  /* coefficients*/ 
   
   printf("intercept=%f\t +/- %f\n", inter, sqrt(sxx/delta) );
   printf("slope=%f\t +/- %f\n", slope, sqrt(s/delta) );
   printf("correlation=%f\n", -sx/sqrt(sxx*s));
}
