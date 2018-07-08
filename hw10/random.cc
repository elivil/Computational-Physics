#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
   int i,r,ry;
   const int seed = 10;
   const int n = 1000;
   ofstream output;
   output.open("rand.dat");
   
   r = seed;                        

   for (i=0; i<n; i++)              
   {
      ry = (57*r+1) % 256;        
      output << r << "\t" << ry << endl;
	  r = (57*ry+1) % 256;
   }
   output.close();
   return 0;
}