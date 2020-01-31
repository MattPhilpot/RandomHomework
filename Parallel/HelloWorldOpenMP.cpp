#include <iostream>
#include <omp.h>
using namespace std;
 
int main()
{
	int threadID;
  	#pragma omp parallel private(threadID)
  	{
    		threadID = omp_get_thread_num();
		#pragma omp critical
    		{
      			cout << "Hello World by Matthew Philpot from thread " << threadID  << '\n';
    		}
    		#pragma omp barrier	
  	}
  	return 0;
}
