#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>

using namespace std;

int main(int argc, char* argv[])
{
   ofstream output;
   output.open("sumb.dat");
   const int Nmax = 1000000;
   double sup, sdown;
   double relerr;
   for (int N=1; N<=Nmax; N*=10)
   {
	   sup = 0.0;
	   sdown = 0.0;
	   for (int i=1; i<=N; i++)
	   {
			sup += 1.0/i;
			sdown += 1.0/(N+1-i);
	   }
		relerr = (double) abs((sup-sdown)/(sup+sdown));
		output << log10(N) << "\t" << log10(relerr) << endl;
	}
	output.close();
	
	return 0;
}