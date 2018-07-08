#include <iostream>
#include <fstream>
#include <cmath>


using namespace std;

double power(double x, int k, double p)
{
	if ((x==0)&(k==0)) return NAN;
	if ((x==0)&(k!=0)) return 0;
	if (x==1) return 1;
	if (k==0) return p;
	else if (k%2==0) return power(x*x, k/2, p);
	else return power(x, k-1, x*p);
}

int main(int argc, char* argv[])
{
   int i, k;
   cin >> k;
   for (i=0; i<10; i++)
   {
	cout << "i= " << i << "  " << power(i,k,1) << endl;
   }
   return 0;
}