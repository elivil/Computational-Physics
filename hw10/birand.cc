#include <iostream>
#include <fstream>
#include <random>


using namespace std;

int main(int argc, char* argv[])
{
   int seed = 10;
   default_random_engine generator (seed);
   uniform_int_distribution<int> distribution(1,255);
   int i;
   const int n = 1000;
   ofstream output;
   output.open("rand2.dat");
   
                        

   for (i=0; i<n; i++)              
   {
      
	  output << distribution(generator) << "\t" << distribution(generator) << endl;
	  
   }
   output.close();
   return 0;
}