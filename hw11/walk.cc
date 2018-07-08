#include <iostream>
#include <fstream>
#include <random>
#include <cmath>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[])
{
   int seed;
   cin >> seed;
   default_random_engine generator (seed);
   int i;
   double x,y,dx,dy,L;
   const int imax = 1000;
   uniform_real_distribution<double> distribution(0.0,1.0);
   ofstream fout;
   fout.open("walk.dat");
   
   //choose a random starting point and record it
   x = distribution(generator);
   y = distribution(generator);
   fout << x << "\t" << y << endl;
   
   for (i=0; i<imax; i++)              
   {
      dx = 2.0*distribution(generator) - 1.0; //generate step between -1, 1
	  dy = 2.0*distribution(generator) - 1.0;
	  L = sqrt(dx*dx + dy*dy);
	  dx = dx/L;
	  dy = dy/L;
	  x += dx;
	  y += dy;
	  fout << x << "\t" << y << endl;
   }
   fout.close();
   return 0;
}