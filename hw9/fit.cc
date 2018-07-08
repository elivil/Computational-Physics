#include <fstream>
#include <iostream>
#include <cmath>


using namespace std;

int main(int argc, char* argv[])
{
	ifstream input;
	ofstream output;
	input.open("expdata.dat");
	output.open("fitdata.dat");
	const int n = 9;
	int i;
	double x[9],y[9], d[9], yp[9];
	double s, sx, sy, sxx, sxy, delta, inter, slope, sqerr;
	s=sx=sy=sxx=sxy=0;	
	for (i=0;i<n;i++) {
		input >> x[i] >> y[i];
		d[i] = 0.05;
		s   += 1 / (d[i]*d[i]);
		sx  += x[i] / (d[i]*d[i]);
		sy  += y[i] / (d[i]*d[i]); 
		sxx += x[i]*x[i] / (d[i]*d[i]); 
		sxy += x[i]*y[i] / (d[i]*d[i]);
		cout << x[i] << "	" << y[i] << endl;
	}

	delta = s*sxx-sx*sx;
	slope=  (s*sxy-sx*sy) / delta;		  
	inter= (sxx*sy-sx*sxy) / delta;		  
	sqerr=0.0;
	for (i=0; i<n; i++)
	{
		yp[i] = slope*x[i]+inter;
		sqerr += (y[i]-yp[i])*(y[i]-yp[i]);
	}
	double fiterr = sqrt(sqerr/7);
	for (i=0; i<n; i++)
	{
			output << x[i] << "\t" << yp[i] << "\t" << yp[i]+fiterr << "\t" << yp[i]-fiterr << endl;
	}
	double chi2 = sqerr; //normalize chi2 to unit std at all pts
	double sb = s/delta;
	double sa = sxx/delta;
	cout << "Parameters of the fit:" << endl;
	cout << "Slope = " << slope << " +- " << sb << endl;
	cout << "Intercept = " << inter << " +- " << sa << endl;
	cout << "chi2 = " << chi2 << endl;
	input.close();
	output.close();
	return 0;
}