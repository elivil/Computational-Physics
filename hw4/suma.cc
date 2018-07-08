#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>

using namespace std;

int main(int argc, char* argv[])
{
   ofstream output;
   output.open("suma.dat");
   const int Nmax = 1000000;
   float s1,s2p1,s2p2,s3,s2;
   double relerr;
   for (int N=1; N<=Nmax; N*=10)
   {
	   s1 = 0.0;
	   s2p1 = 0.0;
	   s2p2 = 0.0;
	   s3 = 0.0;
	   for (int i=1; i<=N; i++)
	   {
			if ((i%2) == 1) s1 += -(float) i/(i+1);
			else s1 += (float) i/(i+1);
			s2p1 += (float) (2*i-1)/(2*i);
			s2p2 += (float) 2*i/(2*i+1);
			s3 += 1.0/(2*i*(2*i+1));
	   }
		for (int i=N+1; i<=2*N; i++)
		{
			if (i % 2) s1 += - (float) i/(i+1);
			else s1+= (float) i/(i+1);
		}
		s2 = s2p2 - s2p1;
		relerr = (double) abs((s1-s3)/s3);
		output << log10(N) << "\t" << log10(relerr) << endl;
	}
	output.close();
	
	return 0;
}