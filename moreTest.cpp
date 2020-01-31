/*	Judy Nguyen
	CSCE 4110
	April 24, 2012
	Project - Kruskal's Algorithm with O(mlogn) time complexity.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <math.h>
#include <ctime>
#include <vector>
#include <algorithm>


using namespace std;

class graph
{
	public:
		int vertA, vertB, distance;

		graph(int a, int b, int d) : vertA(a), vertB(b), distance(d) {}
};
/*
void printvec(const vector<graph>& vec)
{
	for(int i = 0; i < vec.size(); i++)
			cout << vec[i] << " ";
}
*/

int main()
{
	double startTime, endTime, totalTime;
	string word = "";
	int dims = 0;

	int** myArray = NULL; // Initial array where the graph file gets read into.
	bool *actionArr = NULL; // Boolean action array...true == accept edge, false == reject edge b/c it will cause a cycle.
	int*** sortArr = NULL; // Stores sorted array.
	bool ** myArrayVisited = NULL; // myArrayVisited keeps track of the initial array and if each vertex has been visited and placed in the sortedArr (for sorting purposes).
	vector<graph> graphvec; // Creating a vector called graphvec.

	int i = 0, j = 0, pos = 0;
	int cost = 0;
	int vert;
	int min = 10000000; // Setting min to a random number.

	ifstream file;
	file.open("test.txt"); // Read in text file.
	
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
				sortArr = new int**[dims];
				myArrayVisited = new bool*[dims];
				
				for(int x = 0; x < dims; x++)
				{
					myArray[x] = new int[dims]; // Creating a 2d array for the initial array for reading in the graph file.
					myArrayVisited[x] = new bool[dims];
					sortArr[x] = new int*[dims];
					for(int y = 0; y < dims; y++)
					{
						sortArr[x][y] = new int[dims]; // Creating a 2d array for the minimum spanning tree array
					}
				}
//				graphvec.resize(dims); // Initialize the size of the vector, graphvec.
				actionArr = new bool[dims];
			}
			else // Otherwise, convert next word to int and place in myArray.
			{
				myArray[i][j] = atoi(word.c_str());
			//	cout << myArray[i][j] << " "; // Prints out myArray to verify the data is correct.
				j++;			
				if(j >= dims)
				{
					j = 0;
					i++;
					if(i >= dims)
						i = 0;
					cout << endl;
				}
			}
		}
	}
	//copy(myArray, myArray + dims, graphvec.begin()); // Copy the myArray into the vector, graphvec.
	//graphvec.at(i);
	//printvec(graphvec);

	/* Kruskal's Algorithm */
	startTime = clock();

	// Sorting myArray into the sorted array to keep track of the position without changing the vertices, i and j, of myArray. 
	for(int n = 0; n < dims; n++)
	{
		for(i = 0; i < dims; i++)
		{
			for(j = 0; j < dims, myArrayVisited[i][j] == false; j++)
			{
				if((myArray[i][j] <= min) && (myArrayVisited[i][j] != true))
				{
					cout << "I work here" << endl;
					min = myArray[i][j]; // Set new minimum to the value in myArray[i][j].
					cout << "I work here1 " << pos << " " <<  i << " " << j << endl;
					sortArr[pos][i][j] = min; // Place min value in the sorted array with position, pos, at vertices i and j.
					cout << "I work here2" << endl;
					pos++;
					cout << "I work here3" << endl;
					myArrayVisited[i][j] == true; // Set myArrayVisited at vertex i and j to true so that it will not get visited again for sorting.
					cout << "I work here4" << endl << "------" << endl;
					//cout << "sortArr["<< pos << "][" << i << "][" << j << "] = " << sortArr[pos][i][j] << endl;
				}
				else
					myArrayVisited[i][j] == false; // Set myArrayVisited at vertex i and j to true so that it will get visited again.
			}
		}
	}

		


	endTime = clock();
	totalTime = startTime; // Total time in milliseconds.
	totalTime = totalTime/1000000.00; // Finds the total time in seconds.
	cout << "Total running time of Prim's Algorithm: " << totalTime << " seconds" << endl;
	
	file.close();
	return 0;
}
