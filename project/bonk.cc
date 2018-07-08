// Bonk.cc -- demonstrates a structure called 'particle'
//            and a function called 'collide', which collides two particles
//            in D dimensions.

#include <iostream>
#include <cmath>
using namespace std;

#define D  2  // number of dimensions
struct particle {
  double x[D] ; // (x,y) coordinates
  double p[D] ; // momentum
  double im   ; // inverse mass
  double v[D] ; // velocity
  double T    ; // kinetic energy
} ; // Note the definition of a structure ends with a semicolon


// Here's a different way passing a structure by reference
void showVelocityC ( particle & a ) { // the "&" indicates 'this is a pass by
                                      //  reference. 
  for ( int i = 0 ; i < D ; i++ ) { 
    cout << "v["<<i<<"] = "<<a.v[i]<<endl; 
  }
  //  cout << "Kinetic energy = " << a.T << endl ; 
}

void makeVelocityC ( particle & a ) {
  a.T=0.0;
  for ( int i = 0 ; i < D ; i++ ) { 
    a.v[i]  = a.p[i] * a.im ;
    a.T    += 0.5*a.v[i] * a.p[i] ; 
  }
}

void v2p( particle & a )
  // propagate a change in velocity into the momentum vector
{
  for ( int i = 0 ; i < D ; i++ ) {
    a.p[i] = (1.0/a.im) * a.v[i] ;
  }
}


void collide ( particle & a , particle & b , double d[D] )
  // two particles collide elastically; the line joining
  // their centres is in direction d, which should be normalized
{
  // find the relative velocity 
  double velocity_along_line = 0.0 ; 
  for ( int i = 0 ; i < D ; i++ ) {
    velocity_along_line += ( a.v[i] - b.v[i] ) * d[i] ;
  }
  if(velocity_along_line<0.0) {
    cerr << "warning: particle collided but velocity "
	 << "along alleged line joining centres "
	 << "is negative: " << velocity_along_line
	 << endl ;
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

void checkCollide(  particle & a , particle & b , double d[D] )
{
  // check normalization of d
  double mag = 0.0;
  for ( int i = 0 ; i < D ; i++ ) {
    mag += d[i] * d[i] ;
  }
  if ( mag < 0.99 || mag > 1.01 ) {
    cerr << "Warning, collision direction not normalized\n" ;
    if (mag>0.0) {
      mag = 1.0 / sqrt(mag) ;
      for ( int i = 0 ; i < D ; i++ ) {
	d[i] *= mag ;
      }
    } else {
      cerr << "WARNING, collision direction too small for progress\n" ; 
    }
  }
  // assume v is right and make sure p is consistent
  v2p( a ) ; 
  v2p( b ) ; 

  // check energy and momentum before
  double momentum_before[D], momentum_after[D] , diff[D] ;
  double energy_before=0.0 , energy_after =0.0; 
  for ( int i = 0 ; i < D ; i++ ) {
    momentum_before[i] = a.p[i]+b.p[i] ;
    energy_before += 0.5*a.p[i]*a.v[i] +  0.5*b.p[i]*b.v[i] ; 
  }
  
  collide( a , b , d );

  for ( int i = 0 ; i < D ; i++ ) {
    momentum_after[i] =  a.p[i]+b.p[i] ;
    energy_after += 0.5*a.p[i]*a.v[i] +  0.5*b.p[i]*b.v[i] ;
  }
  if( fabs(energy_after-energy_before) > 1e-4 ) {
    cerr << "Warning - energy mismatch?\n" ; 
  }
  cerr << "\tBefore\tAfter\n" ;
  cerr << "Energy\t" << energy_before 
       << "\t" << energy_after << endl;
  int  mismatch = 0 ;
  cerr << "\tBefore\t\tAfter\n" ;
  for ( int i = 0 ; i < D ; i++ ) {
    diff[i] = momentum_before[i] - momentum_after[i] ;
    if (( diff[i]*diff[i] / ( momentum_before[i] + momentum_after[i] + 1e-5 )
	  / ( momentum_before[i] + momentum_after[i] + 1e-5 ) )>1e-10 ) {
      mismatch ++ ; 
    }
    cerr << "Mom["<<i<<"]\t"<< momentum_before[i] << "\t\t"
	 << momentum_after[i]  << endl ; 
  }
  if ( mismatch ) 
    cerr << "WARNING -  momentum mismatch?\n" ; 
  
}
  

int main()
{
  particle   a ;
  particle   b ; 

  a.im    = 1.0/10 ;
  a.v[0] = 1.0;
  a.v[1] = 0.0;

  b.im    = 1  ;
  b.v[0] = 0.0;
  b.v[1] = 0.0;

   double d[2] = { 0.7 , 0.7 } ;
  //    double d[2] = { 1 , 0 } ;
  cout << "a's velocity before\n" ; 
  showVelocityC( a ) ; 
  cout << "b's velocity before\n" ; 
  showVelocityC( b ) ; 
  checkCollide( a , b , d ) ;
  cout << "a's velocity after\n" ; 
  showVelocityC( a ) ; 
  cout << "b's velocity after\n" ; 
  showVelocityC( b ) ; 

  a.im    = 1.0/10 ;
  a.v[0] = 1.0;
  a.v[1] = 0.0;

  b.im    = 1.0/10 ;
  b.v[0] = 0.0;
  b.v[1] = 0.0;

  cout << "a's velocity before\n" ; 
  showVelocityC( a ) ; 
  cout << "b's velocity before\n" ; 
  showVelocityC( b ) ; 
  checkCollide( a , b , d ) ;
  cout << "a's velocity after\n" ; 
  showVelocityC( a ) ; 
  cout << "b's velocity after\n" ; 
  showVelocityC( b ) ; 
  
  return 0;
}
