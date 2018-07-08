#include <fstream>
#include <iostream>
#include <cmath>
#include <cstdlib>


using namespace std;
 
float f (float x)
{ 
   return (exp(-x));               
}

float trap (int nint, float min, float max)
{
   int j;				
   float h, sum=0.;		 
   float x;	
   h = (float) (max-min)/nint;
   for (j=2; j<=nint; j++)           	
   {
      x = min + h * (j-1);      
      sum += f(x)*h;
   }
   sum += 0.5 *(f(min) + f(max)) * h;	

   return (sum);
}      

float simpson (int nint, float min, float max)
{  
   int j;				 
   float h, sum=0., x;
   h = (float)(max-min)/nint;
   
   for (j=2; j<=nint; j+=2)                
   {
       x = min + h * (j-1);
       sum += 4*h*f(x);
   }
   for (j=3; j<nint; j+=2)               
   {
      x = min + h*(j-1);
      sum += 2*h*f(x);
   }   
   sum += h*(f(min) + f(max));	 	          
   sum = sum/3.;        		
   
   return (sum);
}  

float bode (int nint, float min, float max)
{
	int j,k;
	float x[5];
	float h, sum=0.;
	h = (float)(max-min)/nint;
	for (k=1; k<=nint/4; k++)
	{
		for (j=4*k-4; j<=4*k; j++)
		{
			if (j<4*k) x[j%4] = min + j*h;
			else x[4] = min + j*h;
		}
		sum += 7*f(x[0])+32*f(x[1])+12*f(x[2])+32*f(x[3])+7*f(x[4]);
	}
	sum = sum*2*h/45.;
	return (sum);
}


int main(int argc, char* argv[])
{
   int i;			 
   float result;
   float eps;
   const int nmax = 500;
   const float t0=0.0;
   const float t1=1.0;
   const double e=2.7182818284590452354;
   
   ofstream output;
   output.open("integ.dat");

   for (i=2; i<=nmax; i+=2)	    	
   { 					
      result = trap(i, t0, t1);
	  eps = abs((result-1.0+1.0/e)/(1.0-1.0/e));
      output <<  i << "\t" << result << "\t" << eps << "\t";
      
      result = simpson(i, t0, t1);
	  eps = abs((result-1.0+1.0/e)/(1.0-1.0/e));
      output << result << "\t" << eps << "\t";
      
      result = bode(i*2, t0, t1);
	  eps = abs((result-1.0+1.0/e)/(1.0-1.0/e));
      output << result << "\t" << eps << endl;
   }
   output.close();
   return 0;
}


