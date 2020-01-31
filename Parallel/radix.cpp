#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
#include <math.h>
using namespace std;

int main()
{
	int* rad_ray = NULL;
	int* queue = NULL;
	string input;
	int n = 0; 
	int x = 0;
	int position = 0;
	int numb = 0;
	int max_number = 0;
	int new_max = 0;
	int tmp = 0;
	double digits = 0;
	ifstream infile;

	cout << "Welcome to Philpot's Radix Sort\n\n";

	cout << "How big would you like the list to be? ";
	cin >> new_max;
	cout << "Range Size? (1 - n) ";
	cin >> n;
	cout << "Generating Random List of Size " << new_max << " with elements ranging from 1 - " << n << "..." << endl;
	rad_ray = new int[new_max];	/*	Applying new max_size to array	*/
	queue = new int[new_max];
	for(x = 0; x < new_max; x++)
	{
		rad_ray[x] = (rand() % n) + 1;
		queue[x] = rad_ray[x];
	}

/*	Determines the max number of digits (n)	*/
	for(x = 0; x < new_max; x++)
	{
		if(rad_ray[x] > max_number)
			max_number = rad_ray[x];
	}



/*Returns the number of digits of the max_number in Array. This allows Radix Sort to always make the _perfect_ # of passes	*/
	digits = (int) log10((double)max_number); 
	digits++;
	digits = pow(10, digits);

	/*	Starting timer at beginning of radix sort. Does not include user options at beginning of program	*/
	unsigned int start = clock();

/*	Radix Sort. Where most radix sorts call a recurring function, I avoid calling functions altogether to save on time, space, and overhead.	*/
	for(n = 10; n <= digits; n*=10) /*	Determines which position will be sorted. ie. 1's, 10's 100's, etc.	*/
	{
		cout << "\nSorting the " << (n/10) << "'s position" << endl;

		for(numb = 0; numb <= 9; numb++) /*		Determines which number sorted and put in the queue	*/
		{
			for(x = 0; x < new_max; x++) /*		Searches through the list for numb in the position determined by n	*/
			{
				tmp = rad_ray[x] % n;
				if(n >= 100)
				{
					tmp /= (n/10);
				}
				if(tmp == numb)	/*	If equal, place into queue. Then increase queue position by one(1)	*/
				{
					queue[position] = rad_ray[x];
					position++;
				}
			}
		}

/*		Copies partially (or fully) sorted queue back into original array	*/
		for(x = 0; x < new_max; x++) 
		{
			rad_ray[x] = queue[x];

		}

		/*	This is for debugging, to see if Radix sort was sorting properly every pass */
/*		for(int i = 0; i<new_max; i++) 
		{
			cout << rad_ray[i] << " ";
		} */
		position = 0;	/*	Resets queue position to 0	*/
	}

	/* This is for debugging, to see if final list is indeed sorted */
/*	cout << "\n\n\nFinal Sorted List" << endl;
	for(int i = 0; i<new_max; i++)
	{
		cout << rad_ray[i] << " ";
	} */
	cout << endl;
	cout << "Time taken to complete in seconds: " << (clock()-start) << endl;
//	system("Pause");

	return 0;
}
