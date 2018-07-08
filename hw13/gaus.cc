#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

using namespace std;

#define drand48 1.0/RAND_MAX*rand 
#define srand48 srand 

float gasdev()
{
	static int iset=0;
	static float gset;
	float fac,rsq,v1,v2;

	if  (iset == 0) {
		do {
			v1=2.0*drand48()-1.0;
			v2=2.0*drand48()-1.0;
			rsq=v1*v1+v2*v2;
		} while (rsq >= 1.0 || rsq == 0.0);
		fac=sqrt(-2.0*log(rsq)/rsq);
		gset=v1*fac;
		iset=1;
		return v2*fac;
	} else {
		iset=0;
		return gset;
	}
}

/*
double power(double x, int k, double p)
{
	if ((x==0)&(k!=0)) return 0;
	if (x==1) return 1;
	if (k==0) return p;
	else if (k%2==0) return power(x*x, k/2, p);
	else return power(x, k-1, x*p);
}
*/

float w(float x)
{
	const float pi = 3.1415926536;
	return 1/(sqrt(2*pi))*exp(-x*x/2.0);
}

float neumann()
{
	float x = 0;
	float y =1;
	while (y > w(x))
	{
		x = 12*drand48() - 6.0;
		y = drand48();
	} 
	return x;
}



int main(int argc, char* argv[])
{
   int seed;
   cin >> seed;
   srand48(seed);
   ofstream f1, f2;
   f1.open("randn.dat");
   f2.open("randbm.dat");
   for (int i=0; i<10000; i++)
   {
	f1 << neumann() << endl;
	f2 << gasdev()<< endl;
   }
   f1.close();
   f2.close();
   return 0;
}