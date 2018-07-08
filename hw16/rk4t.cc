#include<iostream>
#include<fstream>
#include <cstdio>
#include <cmath>
#include<sstream>
using namespace std;

#define N 2					/* number of equations */
#define dx 0.01					/* stepsize */
#define MIN 0.0					/* minimum x */
#define MAX 5.0					/* maximum x */
#define Pi 3.1415926535897932385E0		/* Pi */

string itostr(int i)
{
	stringstream ss;
	ss << i;
	return ss.str();
}

double energy(int p, double m, double k_spr, double y[])
{
	double Ekin = 0.5*m*y[1]*y[1];
	double Epot = (1.0/p)*k_spr*pow(abs(y[0]),p);
	return Ekin+Epot;
}

double  f(double x, double y[], int i, int p, double m, double k_spr)
{

  
   double rhs;

   if (i == 0) {
        rhs = y[1];
   }
   if (i == 1) {
	rhs = - k_spr/m * pow(abs(y[0]),p-1.0) * y[0]/abs(y[0]);
   }              

   return(rhs);					/* RHS of ith equation */
}



/* Runge-Kutta subroutine */
void runge4(double x, double y[], double step, int p, double m, double k_spr)
{
   double h=step/2.0, 					/* the midpoint */
          t1[N], t2[N], t3[N], 				/* temporary storage */
          k1[N], k2[N], k3[N],k4[N]; 			/* for Runge-Kutta  */
   int i;
 
   for (i=0; i<N; i++) t1[i] = y[i]+0.5*(k1[i]=step*f(x, y, i, p, m, k_spr));
   for (i=0; i<N; i++) t2[i] = y[i]+0.5*(k2[i]=step*f(x+h, t1, i, p, m, k_spr));
   for (i=0; i<N; i++) t3[i] = y[i]+    (k3[i]=step*f(x+h, t2, i, p, m, k_spr));
   for (i=0; i<N; i++) k4[i] =                 step*f(x + step, t3, i, p, m, k_spr);
      
   for (i=0; i<N; i++) y[i] += (k1[i]+2*k2[i]+2*k3[i]+k4[i])/6.0;
}
/*--------------------------------------------------------------------*/






 
int main()
{
   double Amax=2.0;
   double x, y[N], y_an;
   double m=1.0;
   double k_spr = 4.e0*Pi*Pi;
   double y0, y1, t[2];
   ofstream f;					
   string s="TE";
   int i=0;
   double A  = 1.0;					/* Amplitude  */
   int p=3;
    string s1 = s+itostr(p)+".dat";		    
   f.open(s1.c_str());
while (A<= Amax)
{
   y[0] = A;						/* initial position  */
   y[1] = 0.0;						/* initial velocity  */
   t[0]=0.0;
   t[1]=0.0;
   double E;
    
   E = energy(p, m, k_spr, y);
   //for (int p=2;p<=2;p++)
//{
  
   double sum=0.0;
   int count=0;
  
   x = MIN;
   while(x<=MAX)
   {
     
    //f << p << "\t" << x << "\t" << y[0] << endl;
	
	
	y0 = y[0];
    runge4(x, y, dx, p, m, k_spr);	
	x+=dx;
    //f << p << "\t" << x << "\t" << y[0] << endl;
	
	y1 = y[0];
	if (y1*y0<0) 
	{
		if (t[i]!=0) 
		{
			//f<< 2.0*abs(t[1]-t[0]) << endl;
			sum +=2.0*abs(t[1]-t[0]);
			count++;
			
		}
		t[i]=x-dx/2.0;
		i=(i+1)%2;
	}
	
	
   }
   //cout << sum << endl;
   //cout << count << endl;
   double avper=sum/count;
   f << E << "\t" << avper << endl;
 
 A+=0.1;
 //}
}
  f.close();
   return 0;
}



