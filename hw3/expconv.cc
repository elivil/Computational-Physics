
#include <cstdio>
#include <cmath>

using namespace std;

int main(int argc, char* argv[])
{
   const double eps=1.0E-8;
   const double max=10000;
   const double mfactor=2;
   double x, sum, term, relerr;				 
   
   int n;					 

   FILE *output;		           
   output=fopen("expconv.dat", "w");      
   for (x=0.1; x<=max; x*=mfactor)
   {
      sum = term = 1.;                  /* reset variables  */
      n   = 0;
      do                                   /* sum terms until */
      {                                    /* accuracy is reached */
         n++; 
         term *= -x/n;                  /* calculate next element */
         sum += term;
      }while ((sum == 0) || (abs(term/sum) > eps));
      relerr = abs(sum-exp(-x))/exp(-x);
      fprintf(output, "%f\t%d\t%e\t%e\t%d\n", x, n, sum, relerr, (relerr>eps));
   }
   printf("results saved in expconv.dat\n");			
   fclose(output);
   return 0;
}			
