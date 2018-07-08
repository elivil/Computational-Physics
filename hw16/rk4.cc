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

double  f(double x, double y[], int i, int p)
{

   double k_spring = 4.e0*Pi*Pi, m = 1.0;
   double rhs;

   if (i == 0) {
        rhs = y[1];
   }
   if (i == 1) {
	rhs = - k_spring/m * pow(abs(y[0]),p-1.0) * y[0]/abs(y[0]);
   }              

   return(rhs);					/* RHS of ith equation */
}



/* Runge-Kutta subroutine */
void runge4(double x, double y[], double step, int p)
{
   double h=step/2.0, 					/* the midpoint */
          t1[N], t2[N], t3[N], 				/* temporary storage */
          k1[N], k2[N], k3[N],k4[N]; 			/* for Runge-Kutta  */
   int i;
 
   for (i=0; i<N; i++) t1[i] = y[i]+0.5*(k1[i]=step*f(x, y, i, p));
   for (i=0; i<N; i++) t2[i] = y[i]+0.5*(k2[i]=step*f(x+h, t1, i, p));
   for (i=0; i<N; i++) t3[i] = y[i]+    (k3[i]=step*f(x+h, t2, i, p));
   for (i=0; i<N; i++) k4[i] =                 step*f(x + step, t3, i, p);
      
   for (i=0; i<N; i++) y[i] += (k1[i]+2*k2[i]+2*k3[i]+k4[i])/6.0;
}
/*--------------------------------------------------------------------*/






 
int main()
{
     
   double x, y[N], y_an;
   
   
   ofstream f;					
   string s="rk4p";
   
   double A  = 1.0;					/* Amplitude  */
   double w0 = 2.e0*Pi;				 	/* ang. velocity  */
   y[0] = A;						/* initial position  */
   y[1] = 0.0;						/* initial velocity  */
   for (int p=2;p<=12;p++)
{
   string s1 = s+itostr(p)+".dat";		    
	f.open(s1.c_str());
   for(x = MIN; x <= MAX ; x += dx)
   {
     
      y_an = A*sin(w0*x+Pi/2.0);			/* analytical answer */
      f << p << "\t" << x << "\t" << y[0];
	  if (p==2) f << "\t" << y_an << endl;
	  else f << endl;
      runge4(x, y, dx, p);	
     
   }
 f.close();
}
  
   return 0;
}



