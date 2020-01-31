/*	Judy Nguyen
	CSCE 4110
	April 24, 2012
	Project - Prims's Algorithm with O(n^2) time complexity.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <cstring>
#include <math.h>
#include <ctime>


using namespace std;


int main()
{
	double startTime, endTime, totalTime = 0.0; 
       double totalTimeTaken;
	string word = "";
	int dims = 0;

	int** myArray = NULL; // Initial array where the graph file gets read into.
	bool *visitedArr = NULL; // Boolean visited array...true == visited, false == not visited.
	int** mstArr = NULL; // Minium spanning tree array.

	int i = 0, j = 0;
	int cost = 0;
	int vert = 0;
	int min = 100000; // Setting min to a random number.

	ifstream file;
	file.open("densegraph15.txt"); // Read in text file.
	
	if(!file) // If the file cannot be read, then terminate the program.
	{
		cerr << "Error: Cannot open file. Quitting program..." << endl;
		exit(1);
	}
	
	while(file.good())
	{
		while(getline(file, word, ' '))
		{
			if(word == "----") // If the string word starts with "----", then the string word after it would be converted to an int for the size, dims, of the myArray.
			{
				i = 0;
				j = 0;
				myArray = NULL;
				getline(file, word, ' ');
				dims = atoi(word.c_str());	
				myArray = new int*[dims];
				visitedArr = new bool[dims];
				for(int x = 0; x < dims; x++)
					myArray[x] = new int[dims];
			}
			else // Otherwise, convert next word to int and place in myArray.
			{
				myArray[i][j] = atoi(word.c_str());
				//cout << myArray[i][j] << " "; // Prints out myArray to verify the data is correct.
				j++;			
				if(j >= dims)
				{
					j = 0;
					i++;
					if(i >= dims)
						i = 0;
					//cout << endl;
				}
			}
		}
	}
	
		// Creating a 2d array for the minimum spanning tree array
	mstArr = new int*[dims];
	for(int x = 0; x < dims; x++)
		mstArr[x] = new int[dims];


	/* Prim's Algorithm */
	startTime = clock();
	for(i = 0; i < dims; i++)
	{
		for(j = 0; j < dims; j++)
		{
			//cout << i << ", " << j << endl;

			if((visitedArr[j] == false) && (myArray[i][j] < min))
			{
				if(myArray[i][j] != 0) // If the element in myArray[i][j] position is 0, go to the next element.
				{
					min = myArray[i][j]; // Set the distance of myArray[i][j] as the min.
					mstArr[i][j] = min; // Place the min in the mstArr[i][j]
					//cout << "Minimum distance between vertex " << i << " and " << j << " = " << min << endl;
					vert = j; // Set vertex to index j value.
				}
			}
		}
		visitedArr[vert] = true; // Set visited vertex array to true.
		cost += min; // Add minimum distance to the cost.
		cout << "Cost = " << cost << endl;
	}

	endTime = clock();
	totalTime = endTime - startTime; // Total time in milliseconds.
	//totalTime = totalTime; // Finds the total time in seconds.
	cout << "Total running time of Prim's Algorithm: " << totalTime << " seconds" << endl;
	file.close(); // Close the file. 


	return 0;
}
