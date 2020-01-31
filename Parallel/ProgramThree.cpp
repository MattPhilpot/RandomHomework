#include <iostream>
#include <ctime>
using namespace std;

void doTheMath(int* theList, int sDex, int eDex) //quicksortFunction
{
	int i = sDex, j = eDex;
	int pivot = theList[(sDex + eDex) / 2];
	int x  = 0;

	while(i <= j)
	{
		while(theList[i] < pivot)
			i++;
		while(theList[j] > pivot)
			j--;
		if(i <= j)
		{
			x = theList[i];
			theList[i] = theList[j];
			theList[j] = x;
			i++;
			j--;
		}
	}

	if(sDex < j)
		doTheMath(theList, sDex, j);
	if(j < eDex)
		doTheMath(theList, i, eDex);
}

int main(void)
{
	int* theList = NULL;
	int size = 0, n = 0, x = 0;
	int eDex = 0, sDex = 0;
	double startTime, endTime, totalTime = 0.0;
	int runNumber = 0;

	cout << "How big would you like the list to be? ";
	cin >> size;
	cout << "Range Size? (1 - n) ";
	cin >> n;
	cout << "\nGenerating Random List of Size " << size << " with elements ranging from 1 - " << n << "..." << endl;
	theList = new int[size];	/*	Applying new max_size to array	*/

	while(totalTime <= 31000000.0)
	{
		runNumber++;
		for(x = 0; x < size; x++) //fill the matrix with random variables
			theList[x] = (rand() % n) + 1;

		startTime = clock(); //only gets time while performing matrix*vector operation
		doTheMath(theList, 0, size-1);
		endTime = clock(); //end get time		
		totalTime += (endTime - startTime); //add time to total time
		cout << "Run #" << runNumber << " -Time so far- " << totalTime/1000000 << endl;
		cout << "Size Equiv: " << (size*runNumber) << endl << endl;
	}
/*		for(x = 0; x < size; x++) 
			cout << theList[x] << " ";
*/

//	system("pause");
}
