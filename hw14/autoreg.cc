#include<iostream>

using namespace std;

extern "C" { extern void dgesv_(int *, int *, double [], int *, 
			       int [], double [], int *, int *) ; }



				   
double power(double x, int k, double p)
{
	if ((x==0)&(k!=0)) return 0;
	if (x==1) return 1;
	if (k==0) return p;
	else if (k%2==0) return power(x*x, k/2, p);
	else return power(x, k-1, x*p);
}

				   
int main()
{
	const int size = 800;
	int i,j,c1, c2, pivot[size], info;
	double A[size][size], b[size], AT[size*size];
 
  
   for (i=0; i<size; i++)
   {
	for (j=0; j<size; j++)
	{
		A[i][j] = power(0.5, abs(i-j), 1.0); 
	}
	b[i] = i+1.0; //since index b starting from 0, add 1 to the formula
   }
	
   
   for (i=0; i<size; i++)	     	
   {                                            
     for(j = 0 ; j < size ; j += 1) AT[j + size*i] = A[j][i];           
   }                                                  
	
   c1 = size; 		                 
   c2 = 1;             

   dgesv_(&c1, &c2, AT, &c1, pivot, b, &c1, &info); 
   
      
   
   if (info==0)
   {                                             
      for (j=0; j<size; j++) cout << b[j] << endl;	
   }
   else cout << "An error occurred" << endl;
}
