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
	sum=sumarg*sumarg + sum;

}
double fav=sum/a;

integ=fav*V;


}


int main (int argc, char* argv[])
{

	int N = 1000000;
	int num = 16;
	int seed = 0;
	default_random_engine generator (seed);
	uniform_real_distribution<double> distribution(0.0,1.0);

	double integ;
	double sumint=0.0;
	double meanint;

	for (int k=0; k<num; k++)
	{
	   integrate(N, integ, distribution, generator);
	   sumint = integ+sumint;
	 	 }
	meanint = sumint/num;
	cout << N << endl;
	cout << meanint << endl;
	return 0;
}
