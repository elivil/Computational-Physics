#include <stdio.h>
#include <math.h>

#define steps 1000	 	     /* half width of potential well */
#define V -0.001		     /* depth of potential well */
#define eps 1E-6		     /* accuracy for eigenvalues */
#define Emin -0.00010		     /* set to find the third */
#define Emax -0.00098		     /* eigenfunction */

double k2(int i, double E);	         /* returns potential at x */
double diff(double E, int parity);       /* difference of derivatives */
int validate(double E, int parity);      /* difference of derivatives */
void plot(double E, int parity);         /* data for final plot */ 

main()
{
   double E, min, max;
   int i=0, parity=1;			     /* counter for iterations */
   min=Emin;				
   max=Emax;
  
   
   if (diff(Emin,parity)*diff(Emax,parity) > 0 ) 
   {
      printf("\n No even wavefunction in this energy bracket\n \n");
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
        plot(E,parity);
      } else {
	printf("\n No even wavefunction in this energy bracket\n \n");
      }
      
    }			
   
   min=Emin;				
   max=Emax;
   parity = -1;						/* Now we scan for odd eigenfunctions */
   
   if (diff(Emin,parity)*diff(Emax,parity) > 0 )
   {
      printf("\n No odd wavefunction in this energy bracket\n \n"); 
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
        plot(E,parity);
      } else {
        printf("\n No odd wavefunction in this energy bracket\n \n");
      }
      
    }			
}


/*----------------------- end of main program ------------------------*/ 

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

/* function returns k-vector at depending on position i */
double k2(int i, double E)		
{
   if (i<500) return(E);		/* outside the well */
   if (i>=500) return (E-(V));		/* inside the well */
}
/*--------------------------------------------------------------------*/

/* write data for eigenfuntion into files left.dat, right.dat */
void plot(double E,int parity)			
{					
   double one, two, three;
   int i;
   
   FILE *right, *left;			/* save data in files */
   if (parity == 1)
   {
     right=fopen("right_even.dat", "w");
     left=fopen("left_even.dat", "w");
   } else {
     right=fopen("right_odd.dat", "w");
     left=fopen("left_odd.dat", "w");
   } 
   
   one=0.0;
   two=0.00001;
   for (i=1; i<=1500; i++)		/* left side first */
   {
      three=(2*two*(1-5./12.*k2(i,E))-
      		(1+1./12.*k2(i-1,E))*one)/(1+1./12.*k2(i+1,E));
      fprintf(left, "%d\t%f\n", i-1000, three/2.8);
      
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
      fprintf(right, "%d\t%f\n", 1000-i, three/2.8);
      
      one=two;
      two=three;
   }
   fclose(left);
   fclose(right);
   if (parity == 1 )
   {
     printf("data saved in left_even.dat and right_even.dat\n");
   } else {
     printf("data saved in left_odd.dat and right_odd.dat\n");
   }
}
   
