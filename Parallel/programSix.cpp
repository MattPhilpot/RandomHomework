#include <iostream>
#include <ctime>
#include <math.h>
#include "mpi.h"

using namespace std;


void doTheMath(int* rad_ray, int* vector, int* result, int new_max, int max_number) //my matrixMatrix function
{
	int n = 0 - new_max;
	int y = 0;
	#pragma omp parallel for
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


int main(int argc, char **argv)
{
	int rank, size, problemSize, arraySize; //initialize variables
	int* rad_ray = NULL; //initial matrix
	int* vector = NULL; //other matrix
	int* result = NULL; //result matrix
	int x = 0; //really cool variable
	int n = 0;
	int max_number = 0;
	int new_max = 0;
	double startTime, endTime, totalTime = 0.0;
	double xx = 0.0;

	MPI_Status status; //gogo MPI stuff (AGAIN)
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(rank == 0){
	cout << "How big would you like a side to be? ";
	cin >> new_max; new_max /= size;
	max_number = new_max*new_max;
	cout << "Range Size? (1 - n) ";
	cin >> n;
	cout << "\nGenerating Random List of Size " << max_number << " with elements ranging from 1 - " << n << "..." << endl;
	rad_ray = new int[max_number];	/*	Applying new max_size to array	*/
	vector = new int[max_number];
	result = new int[max_number];
	#pragma omp parallel for
	for(x = 0; x < max_number; x++) //fill the matrix with random variables
	{
		rad_ray[x] = (rand() % n) + 1;
		vector[x] = (rand() % n) + 1;
	   	result[x] = 0;
	}
	cout << "User Time = ";
	startTime = clock(); //only gets time while performing matrix*vector operation
	doTheMath(rad_ray, vector, result, new_max, max_number);
	endTime = clock(); //end get time
	totalTime += (endTime - startTime); //add time to total time
	cout << totalTime/1000000 << " seconds" << endl;
	}
	MPI_Finalize(); //FINALIZE dat stuff
	return 0;
}
