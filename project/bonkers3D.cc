// Bonkers1.cc
//   bonkers bonking in a one-dimensional box
//   usage:
//      Bonkers1 [N [dt [tframe(ms) [filename]]]]
//
//   by default, writes to /tmp/1
//   movie can be made by gnuplot
//         load 'gnu10'

#include <iostream>
#include <fstream> 
#include <cmath>
#include<cstring>
#include<cstdlib>
using namespace std;
 
#define ranf() \
  ((double)rand()/(1.0+(double)RAND_MAX)) // Uniform from interval [0,1) */
#define D 3
struct particle {
  double x[D]    ; // (x,y) coordinates
  double p[D]    ; // momentum
  double im   ; // inverse mass
  double v[D]    ; // velocity
  double T    ; // kinetic energy
  double a    ; // radius of particle
} ; // Note the definition of a structure ends with a semicolon

struct control {
  int verbose    ; // program verbosity
  int printing   ; // period with which to print
  int commanding ; // period with which to issue commands
  int time_in_ms ; // time between frames (commands)
  clock_t latest_time;
  ofstream fout  ; 
};


// Implement     x += v dt for one particle
void PositionStep ( particle &a , double dt )
{ 
  for (int i=0; i<D; i++) 
  {
	a.x[i] += dt * a.v[i] ; 
  }
}

void v2p( particle &a )
  // propagate the changed velocity into the momentum vector
{
 for (int i=0; i<D; i++) 
  {
	a.p[i] =  a.v[i] / a.im ;
  }  

}

void p2v ( particle &a ) {
 for (int i=0; i<D; i++) 
  {
	a.v[i] =  a.p[i] * a.im ;
  } 
}

void pv2T ( particle &a ) {
for (int i=0; i<D; i++) 
  {
	a.T = 0.5*a.v[i] * a.p[i] ;
  }  
  
}

void normalize (double *d)
{
  double normsq=0.0;
  for (int i=0; i<D; i++) { normsq += d[i]*d[i]; }
  for (int i=0; i<D; i++) d[i]=d[i]/sqrt(normsq);
}



void collide ( particle & a, int whichn, particle & b)
  // two particles collide elastically
// their centres is in direction d, which should be normalized
{
  double d[D];
  double velocity_along_line = 0.0 ; 
  if (a.im == 0) 
  {
	velocity_along_line = b.v[whichn/2];
	for (int i=0; i<D; i++) {	if (i==whichn/2) { d[i] = -1.0; } else { d[i]=0.0; } }
  }
  else
  {
  for ( int i = 0 ; i < D ; i++ ) { d[i]= a.x[i] - b.x[i]; normalize(d); }
 // find the relative velocity 
  
  for ( int i = 0 ; i < D ; i++ ) {
    velocity_along_line += ( a.v[i] - b.v[i] ) * d[i] ;
  }
  if(velocity_along_line<0.0) {
    cerr << "warning: particle collided but velocity "
	 << "along alleged line joining centres "
	 << "is negative: " << velocity_along_line
	 << endl ;
  }
  }
  // find a's mass fraction
  double af = a.im / ( a.im + b.im ) ; 
  double bf = b.im / ( a.im + b.im ) ; 
  // reverse the c.o.m. velocity of each along the line of collision
  for ( int i = 0 ; i < D ; i++ ) {
    a.v[i] -= 2.0 * af * velocity_along_line * d[i] ;
    b.v[i] += 2.0 * bf * velocity_along_line * d[i] ;
  }
  v2p( a ) ; 
  v2p( b ) ; 
}




// find next collision time 
double nct( particle *a , int NN , int &whichn , int &whichj) {
  double dt = 1e100 ; 
  // examine all adjacent pairs from 0,1   to  NN-2,NN-1
  for ( int n = 0 ; n < NN; n ++ ) {
    for ( int j = n ; j < NN; j ++ ) {
    double d[D];	
    double velocity_along_line = 0.0 ; 
	
	if (n<=D*2-1 & j>2*D-1)
	{
		double distance=0.0;
		int l = n%2;
		if ((l==0 & a[j].v[n/2]<0.0) || (l!=0 & a[j].v[n/2]>0.0))
		{
			distance = abs(a[n].x[n/2] - (a[j].x[n/2] - pow(-1.0,l)*a[j].a));
			double collision_time = distance/abs(a[j].v[n/2]);
			if (collision_time < dt) { 
				dt = collision_time;
				whichn = n;
				whichj = j;
			}
		}
	}
	if (n>D*2-1 & j>2*D-1)
	{
  for ( int i = 0 ; i < D ; i++ ) {
	d[i]=(a[n].x[i]-a[n].a) - (a[j].x[i]+a[j].a); normalize(d);
    velocity_along_line += ( a[n].v[i] - a[j].v[i] ) * d[i] ;
  }
      if(velocity_along_line > 0.0) {
      double distance=0.0;
      for ( int i = 0 ; i < D ; i++ ) {
	distance += pow(((a[n].x[i]-a[n].a) - (a[j].x[i]+a[j].a)),2);
	 }
      double collision_time =  distance/velocity_along_line ;
      if ( collision_time < dt)  {
	dt = collision_time ;
	whichn = n;
	whichj = j;
      }
    }
	}
  }
} 
  return dt ;
}

void leapForward(  particle *a , int NN , double dt ) {
  for( int n = 0 ; n < NN ; n ++ ) 
    PositionStep( a[n] , dt ) ; 
}

void showState ( particle *a , int n0 ,  int NN, ostream &fout )
{
  for( int n = n0 ; n < NN ; n ++ ) {
    for ( int i = 0 ; i < D ; i++ ) {  
      fout << "\t"<<a[n].x[i];
      fout << "\t"<<a[n].v[i];
	}
  }
  fout << endl;
}

double kineticEnergy ( particle *a , int NN )
{
  double E = 0.0 ; 
  for( int n=0 ; n < NN ; n ++ ) {
      if ( a[n].im > 0.0 ) // avoid infinitely massive objects
	for ( int i = 0 ; i < D ; i++ ) {
	E+=0.5*a[n].v[i]*a[n].v[i]/a[n].im;
	}
  }
  return E ;
}

void  simulateBonkers( particle *a , int NN ,
		       double &t , double dt , double T ,
		       control &c ) {
  double next_print_dt = 0.0, next_collision_dt ;
  int whichn, whichj;
  int we_are_printing_this_time = 1 ; 
  for(;t<=T;) {
    if( we_are_printing_this_time ) {
      c.fout << t << "\t" << kineticEnergy(a,NN) ;
      showState ( a , 0 , NN , c.fout ) ;
      next_print_dt = dt ;
    }
    // find the next event
    next_collision_dt = nct( a , NN , whichn, whichj) ;
    // ^^ this returns the time, and sets 'whichn'
    if ( next_collision_dt < next_print_dt ) {
      // advance time to that event, have a collision
      leapForward( a ,  NN , next_collision_dt ) ;
      t += next_collision_dt ;
      next_print_dt -= next_collision_dt ;
      collide( a[whichn], whichn, a[whichj]) ;
      we_are_printing_this_time = 0 ; 
    } else {
      leapForward( a , NN , next_print_dt ) ;
      t += next_print_dt ;
      we_are_printing_this_time = 1 ; 
    }
  }
}

int main(int argc, char* argv[])
{
  int N = 20    ; // number of particles
  double T =100000.0  ; // target time
  particle   *a ;
  control    c ;
  char filename[256]="bonk.dat" ;
  // set defaults
  double dt = 0.01 ;
  double t = 0.0 ;
  c.verbose = 1 ;
  c.time_in_ms = 100; // real time between plots (in ms)

  // read in any command-line arguments
  if(argc>1)   {
    sscanf( argv[1], "%d", &N ) ; // put the first command-line argument in N
  }
  if(argc>2) {
    sscanf( argv[2], "%lf", &dt ) ; // put the 2nd argument in dt
  }
  if(argc>3) {
    sscanf( argv[3], "%d", &(c.time_in_ms) ) ;
  }
  if(argc>4) {
    strncpy(filename, argv[4], 256 );
  }

  // try to write output file
  c.fout.open(filename);
  if(c.fout.good()==false){
    cerr << "can't write to file " << filename << endl;
    exit(0);
  }
  
  a = new particle[N+2*D] ; // 0, 1, 2, 3, 4, 5,(6 walls), 6 ...N+5 (particles)
  
  for ( int n=0 ; n<= N+2*D-1; n++) {
	if (n<=2*D-1) {
	    a[n].im = 0.0 ; 
		for ( int i = 0 ; i < D ; i++ ) {  
			a[n].v[i]  = 0.0 ; 
			if (i != n/2) 
			{
				a[n].x[i]=100*N;
			}
			else 
			{
				if (n%2==0) a[n].x[i]=0;
				else a[n].x[i]=N;
			}
		}
		a[n].a  = 0.0   ; // radius
    }
	else
	{
    a[n].im    = 1.0/10.0  ; 
    for ( int i = 0 ; i < D ; i++ ) { 
		a[n].v[i]=ranf();
		a[n].x[i]=0.5*(n-5);
	} 
    a[n].a     = 0.1   ; // radius
    cerr<<"mass: "<<1.0/a[n].im<<endl;
	}
	v2p(a[n]);
  }
	cout << "kinetic energy in the beginning" << kineticEnergy(a,N+2*D) << endl;
  simulateBonkers( a , N+2*D , t , dt , T , c ) ; 
	cout << "kinetic energy in the end" << kineticEnergy(a,N+2*D) << endl;
	ofstream f;
	f.open("vel.dat");
	for (int i=2*D; i<N+2*D; i++)
	{
		double vel=0.0;
		for (int j=0; j<D; j++) vel+=(a[i].v[j]*a[i].v[j]);
		vel=sqrt(vel);
		f << i << "\t" << vel << endl;
	}
	f.close();
	c.fout.close();
  return 0;
}
