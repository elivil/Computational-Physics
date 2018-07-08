

#include <cstdio>


int main(int argc, char* argv[])
{
   const int N=60;
   int i;
   double eps=1.0, one;				
   

   for(i=0; i<N; i++)
   {
      eps  /= 2.;				/* divide by two */
      one=1.0+eps;			
      printf("%d. \t %.18f \t %.17e \n",i+1,one, eps);
   }
   return 0;
}