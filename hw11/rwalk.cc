#include <iostream>
#include <fstream>
#include <random>
#include <cmath>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[])
{
   
   
   long int N=1;
   double x0,y0,x,y,dx,dy,L;
   double r2,r2sum,rms;
   const long int Nmax = 90000;
   
   ofstream fout;
   fout.open("rms.dat");
   
   //choose a random starting point and record it
   
   while (N<Nmax)
   {
		int k= round(sqrt(N));
		r2sum = 0.0;
		for (int i=0; i<k; i++)
		{
		   default_random_engine generator (i+1);
		   uniform_real_distribution<double> distribution(0.0,1.0);
		   x0 = distribution(generator);
		   y0 = distribution(generator);
		   x = x0;
		   y = y0;
		   for (int j=0; j<N; j++)              
		   {
			  dx = 2.0*distribution(generator) - 1.0; //generate step between -1, 1
			  dy = 2.0*distribution(generator) - 1.0;
			  L = sqrt(dx*dx + dy*dy);
			  dx = dx/L;
			  dy = dy/L;
			  x += dx;
			  y += dy;
			}
			r2 = (x-x0)*(x-x0) + (y-y0)*(y-y0);
			r2sum += r2;
		}
		rms = sqrt(r2sum/(double)k);
		fout << sqrt(N) << "\t" << rms << endl;
		N = N+1000;
	}
   fout.close();
   return 0;
}