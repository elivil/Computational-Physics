#include<iostream>

using namespace std;

extern "C" { extern void dgesv_(int *, int *, double [], int *, 
			       int [], double [], int *, int *) ; }



int main()
{
	const int size = 100;
	int i,j,c1, c2, pivot[size], info;
	double A[size][size], b[size], AT[size*size];
 
  
   for (i=0; i<size; i++)
   {
	for (j=0; j<size; j++)
	{
		A[i][j] = 1.0/(i+j+1); //since indexation starts at 0, add 1 to i, j in the formula.
								// e.g. A[0][0] = a11 = 1
	}
	b[i] = 1.0/(i+1);
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
