#include <iostream>
#include <ctime>
#include <math.h>
using namespace std;


void doTheMath(int* rad_ray, int* vector, int* result, int new_max, int max_number) //my matrixMatrix function
{
	int n = 0 - new_max;
	int y = 0;
	for(int i = 0; i < max_number; i++) //outer loop, for each position in result matrix
	{
		if(i % new_max == 0)
			n += new_max;
		for(int j = 0; j < new_max; j++) //this part does the matrix*matrix math
		{
			result[i] += (rad_ray[j+n] * vector[(i%new_max)+y]);
			y += new_max;
		}
		y = 0;
	}
}


int main()
{
	int* rad_ray = NULL; //initial matrix
	int* vector = NULL; //other matrix
	int* result = NULL; //result matrix
	int x = 0; //really cool variable
	int n = 0;
	int max_number = 0;
	int new_max = 0;
	double startTime, endTime, totalTime = 0.0;
	int runNumber = 0;
	double xx = 0.0;


	cout << "How big would you like a side to be? ";
	cin >> new_max;
	max_number = new_max*new_max;
	cout << "Range Size? (1 - n) ";
	cin >> n;
	cout << "\nGenerating Random List of Size " << max_number << " with elements ranging from 1 - " << n << "..." << endl;
	rad_ray = new int[max_number];	/*	Applying new max_size to array	*/

	vector = new int[max_number];
	result = new int[max_number];
	while(totalTime <= 31000000.0)
	{

		runNumber++;
		cout << "\nRun # " << runNumber << "\n[matrix]"; //this is for displaying the array
		for(x = 0; x < max_number; x++) //fill the matrix with random variables
		{
			/*if((x%new_max)==0 && x != 0)
				cout << "]" << endl << "["; //ALL OF THIS
			else
			{
				if(x != 0)
					cout << " "; //space inbetween values
			}
				*/
			rad_ray[x] = (rand() % n) + 1;
			vector[x] = (rand() % n) + 1;
			//cout << rad_ray[x]; //for debug
		   result[x] = 0;
		}
		cout << " * [matrix] = ";
		startTime = clock(); //only gets time while performing matrix*vector operation
		doTheMath(rad_ray, vector, result, new_max, max_number);
		endTime = clock(); //end get time
		totalTime += (endTime - startTime); //add time to total time
		cout << totalTime/1000000 << " seconds" << endl;
		xx = (max_number*(double)runNumber);
		xx = sqrt(xx);
		cout << (int)xx << " by " << (int)xx << " matrix equivalent" << endl; //displays the matrix equivalent of the work done so far
	}
/*
	for(int iii = 0; iii < max_number; iii++)
	{
		if(iii % new_max == 0)
			cout << endl;
		cout <<  rad_ray[iii] << " ";

	}
	cout << endl << "*";
	for(int iii = 0; iii < max_number; iii++)
	{
		if(iii % new_max == 0)
			cout << endl;
		cout <<  vector[iii] << " ";

	}
	cout << endl << "=";
	for(int iii = 0; iii < max_number; iii++)
	{
		if(iii % new_max == 0)
			cout << endl;
		cout <<  result[iii] << " ";

	}
*/
	cout << "\nOperation completed in " << runNumber << " times and took ~" << totalTime/1000000 << " seconds to complete." << endl;
	cout << "The amount of work done is equal to two matrices of " << (int)xx << " by " << (int)xx << "." << endl << endl;
//	system("pause"); //debug purposes
	return 0;
}
