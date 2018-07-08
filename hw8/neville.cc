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
	output.open("intdata.dat");
	const int n = 9;
	int i;
	float dy,y;
	float x = 0.0;
	float xa[9],ya[9],err[9];
	for (i=0;i<n;i++) {
		input >> xa[i] >> ya[i] >> err[i];
		cout << xa[i] << "	" << ya[i] << endl;
	}
	while (x<=200.0) {
		polint(xa,ya,n,x,&y,&dy);
		/*if (((int)round(x))%25==0) {
			x=xa[((int) round(x))/25];
			y=ya[((int) round(x))/25];
			dy = err[((int) round(x))/25];
		}*/
		output << x << "\t" << y << "\t" << dy << endl;
		x+=1.0;
	}
	input.close();
	output.close();
	return 0;
}
