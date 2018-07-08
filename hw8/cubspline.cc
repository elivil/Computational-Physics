#include <fstream>
#include <iostream>
#include <cmath>
#include "nr.h"
#include "nrutil.h"

using namespace std;

int main(int argc, char* argv[])
{
	ifstream input;
	ofstream output;
	input.open("expdata.dat");
	output.open("splinedata.dat");
	const int n = 9;
	int i;
	float dy,y;
	float x = 0.0;
	float xa[9],ya[9],err[9],y2a[9];
	for (i=0;i<n;i++) {
		input >> xa[i] >> ya[i] >> err[i];
		cout << xa[i] << "	" << ya[i] << endl;
	}
	spline(xa,ya,n,1.e30,1.e30, y2a);
	while (x<=200.0) {
		splint(xa,ya,y2a,n,x,&y);
		/*if (((int)round(x))%25==0) {
			x=xa[((int) round(x))/25];
			y=ya[((int) round(x))/25];
			dy = err[((int) round(x))/25];
		}*/
		output << x << "\t" << y << endl;
		x+=1.0;
	}
	input.close();
	output.close();
	return 0;
}
