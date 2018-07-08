#include <iostream>
#include <fstream>
#include <random>
#include <cmath>
#include <cstdlib>

using namespace std;



double power(double x, int k, double p)
{
	if ((x==0)&(k!=0)) return 0;
	if (x==1) return 1;
	if (k==0) return p;
	else if (k%2==0) return power(x*x, k/2, p);
	else return power(x, k-1, x*p);
}

int main(int argc, char* argv[])
{
   int seed = 10;
   default_random_engine generator (seed);
   int i,j;
   double x;
   double sum1,sum2,sum3;
   double s1,s2,s3;
   const int nmin = 100;
   const int nmax = 100000;
   uniform_real_distribution<double> distribution(0.0,1.0);
   ofstream fout1, fout2, fout3;
   fout1.open("test1.dat");
   fout2.open("test2.dat");
   fout3.open("test3.dat");
   int k1=1;
   int k2=3;
   int k3=7;
   sum1=0;
   sum2=0;
   sum3=0;
   for (i=nmin; i<=nmax; i+=100)              
   {
      for (j=1; j<=i; j++)
	  {
	  	  x=distribution(generator);
		  //x = drand48();
		  sum1 += power(x,k1,1.0);
		  sum2 += power(x,k2,1.0);
		  sum3 += power(x,k3,1.0);
	  }
	  //cout << i << endl;
	  //cout << sum1 << endl;
	  s1 = sqrt(i)*(sum1/(double)i - 1.0/(k1+1));
	  //cout << s1 << endl;
	  s2 = sqrt(i)*(sum2/(double)i - 1.0/(k2+1));
	  s3 = sqrt(i)*(sum3/(double)i - 1.0/(k3+1));
	  fout1 << i << "\t" << s1 << endl;
	  fout2 << i << "\t" << s2 << endl;
	  fout3 << i << "\t" << s3 << endl;
	  sum1=0;
	  sum2=0;
	  sum3=0;
	  
   }
   fout1.close();
   fout2.close();
   fout3.close();
   return 0;
}