#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <random>


using namespace std;






void integrate (int a, double &integ, uniform_real_distribution<double> &distrib, default_random_engine &gen)
{
double sum=0.0;
double sumarg=0.0;
double V=1.0;
for (int i=0; i<=a-1; i++){
	sumarg=0.0;
	for (int j=1; j<=10;j++){
		sumarg=sumarg+distrib(gen);
	}
	//cout << sumarg << endl;
	sum=sumarg*sumarg + sum;
	
}
double fav=sum/a;

integ=fav*V;

}


int main (int argc, char* argv[])
{

	int N = 2;
	int num = 16;
	int seed = 0;
	default_random_engine generator (seed);
	uniform_real_distribution<double> distribution(0.0,1.0);
	ofstream f("mc.dat");
	double integ;
	
	
	while (N<=8192)
	{
		double sumint=0.0;
		double sumsqerr=0.0;
		double meanint=0.0;
		
		for (int k=0; k<num; k++)
		{
		   integrate(N, integ, distribution, generator);
		   sumint = integ+sumint;

		}
		
		meanint = sumint/num;
		f << 1.0/sqrt(N) << "\t" << abs(meanint-155.0/6) << endl;
		N*=2;
	}
	f.close();
	return 0;
}
