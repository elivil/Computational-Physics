#include<iostream>
#include<fstream>
#include <cstdio>
#include <cmath>
#include<sstream>

using namespace std;

#define steps 1000	 	     /* half width of potential well */
#define V -0.001		     /* depth of potential well */
#define eps 1E-6		     /* accuracy for eigenvalues */
//#define Emin -0.00010		     /* set to find the third */
//#define Emax -0.00098		     /* eigenfunction */

string itostr(int i)
{
	stringstream ss;
	ss << i;
	return ss.str();
}

/* function returns k-vector at depending on position i */
double k2(int i, double E)		
{
   if (i<500) return(E);		/* outside the well */
   if (i>=500) return (E-(V));		/* inside the well */
}

/* function returns difference between left and right wavefunction */
double diff(double E, int parity)
{
   double one, two, three, plus, minus;
   int i;
   
   one=0.0;
   two=0.00001;
   for (i=1; i<=1500; i++)		/* left side first */
   {
      three=(2*two*(1-5./12.*k2(i,E))-
      		(1.+1./12.*k2(i-1,E))*one)/(1.+1./12.*k2(i+1,E));
      one=two;
      two=three;
   }
   minus=two;				/* value at matching point */ 

   if (parity == 1)
   {
     one= 0.0;				/* reset starting conditions */
     two= 0.00001;
   } else {
     one=-0.00001;			/* reset starting conditions */
     two=-0.00002;
   }
   
   for (i=1; i<500; i++)		/* now the right side */
   {
      three=(2*two*(1.-5./12.*k2(i,E))-
      		(1.+1./12.*k2(i+1,E))*one)/(1.+1./12.*k2(i-1,E));
      one=two;
      two=three;
/*   printf("%d \t %e \n", i,three); */
   }
   plus=two;			        /* value at matching point */
   
   return(minus-plus);
     
}
/*--------------------------------------------------------------------*/

/* function returns difference between left and right wavefunction */
int validate(double E, int parity)
{
   double one, two, three, plus, El, Em, Er;
   int i, val, par = 0;
   
   one=0.0;
   two=0.00001;
   for (i=1; i<=1500; i++)		/* left side first */
   {
      three=(2*two*(1-5./12.*k2(i,E))-
      		(1.+1./12.*k2(i-1,E))*one)/(1.+1./12.*k2(i+1,E));
		
      if (two*three < 0.0) par += 1;	/* count zero crossings */ 
      one=two;
      two=three;
   }
   El=one;				/* value before matching point */ 
   Em=two;				/* value at matching point */ 

   if (parity == 1)
   {
     one= 0.0;				/* reset starting conditions */
     two= 0.00001;
   } else {
     one=-0.00001;			/* reset starting conditions */
     two=-0.00002;
   }
   
   for (i=1; i<500; i++)		/* now the right side */
   {
      three=(2*two*(1.-5./12.*k2(i,E))-
      		(1.+1./12.*k2(i+1,E))*one)/(1.+1./12.*k2(i-1,E));
      one=two;
      two=three;
   }
   Er=one;			        /* value after matching point */

   if ((El-Em)*(Em-Er) > 0) 
   {
     return( 1);
   } else {
     return(-1);
   }
   
   return(val);
   
}
/*--------------------------------------------------------------------*/


/*--------------------------------------------------------------------*/

/* write data for eigenfuntion into files left.dat, right.dat */
void plot(double E,int parity, int c)			
{					
   double one, two, three;
   int i;
   
   ofstream fr, fl;
   string sr = "right";
   string sl = "left";
   string sl1, sr1;
   if (parity == 1)
   {
     sr1 = sr+itostr(c)+"_even.dat";
	 sl1 = sl+itostr(c)+"_even.dat";
	 fr.open(sr1.c_str());
	 fl.open(sl1.c_str());
   } else {
     sr1 = sr+itostr(c)+"_odd.dat";
	 sl1 = sl+itostr(c)+"_odd.dat";
	 fr.open(sr1.c_str());
	 fl.open(sl1.c_str());
   } 
   
   one=0.0;
   two=0.00001;
   for (i=1; i<=1500; i++)		/* left side first */
   {
      three=(2*two*(1-5./12.*k2(i,E))-
      		(1+1./12.*k2(i-1,E))*one)/(1+1./12.*k2(i+1,E));
      fl << i-1000 << "\t" << three/2.8 << endl;
	  
      
      one=two;				
      two=three;
   }
   
   if (parity == 1)
   {
     one= 0.0;				/* reset starting conditions */
     two= 0.00001;
   } else {
     one=-0.00001;			/* reset starting conditions */
     two=-0.00002;
   }
   
   for (i=1; i<500; i++)		/* now the right side */
   {
      three=(2*two*(1.-5./12.*k2(i,E))-
      		(1+1./12.*k2(i+1,E))*one)/(1.+1./12.*k2(i-1,E));
	  fr << 1000-i << "\t" << three/2.8 << endl;
      
      
      one=two;
      two=three;
   }
   fl.close();
   fr.close();
   cout << "data saved in " << sl1 << " and " << sr1 << endl;
   
}
   



int main()
{
   double E, min, max, Emax;
   int c=7;			     /* counter for iterations */
   double dE = 0.000005;
   double Emin= -0.00046;
   ofstream f;
   f.open("eigenv.dat");
  while (c>=1)
  {
   int i=0, parity =1;
   Emax = Emin-dE;
   min=Emin;				
   max=Emax;
   if (diff(Emin,parity)*diff(Emax,parity) > 0 ) 
   {
      //printf("\n No even wavefunction in this energy bracket\n \n");
   } else {
      
     do
     {
        i++;  
        E=(max+min)/2.0;		                /* divide energy range */
        if (diff(max,parity)*diff(E,parity)>0) max=E;   /* the bisection algorithm */
        else min=E;
	
      }while(fabs(diff(E,parity))>eps);
   
      if (validate(E,parity) == 1)			/* Validate the eigenfunction */
      {
        printf("Even eigenvalue E=%.10f\n", E);
        printf("after %d iterations\n", i);
		c--;
		if (c!=6) f << "E" << c << "\t" << E << endl;
		plot(E,parity, c);
		
      } else {
	//printf("\n No even wavefunction in this energy bracket\n \n");
      }
      
    }			
   
   min=Emin;				
   max=Emax;
   parity = -1;						/* Now we scan for odd eigenfunctions */
   
   if (diff(Emin,parity)*diff(Emax,parity) > 0 )
   {
      //printf("\n No odd wavefunction in this energy bracket\n \n"); 
   } else {
      
     do
     {
        i++;  
        E=(max+min)/2.0;		                /* divide energy range */
        if (diff(max,parity)*diff(E,parity)>0) max=E;   /* the bisection algorithm */
        else min=E;
      }while(fabs(diff(E,parity))>eps);
   
      if (validate(E,parity) == 1)			/* Validate the eigenfunction */
      {
        printf("Odd eigenvalue E=%.10f\n", E);
        printf("after %d iterations\n", i);
        c--;
		if (c!=6) f << "E" << c << "\t" << E << endl;
		plot(E,parity, c);
		
      } else {
        //printf("\n No odd wavefunction in this energy bracket\n \n");
      }
      
    }		
	Emin-= 0.000005;
	}
	f.close();
	return 0;
}





