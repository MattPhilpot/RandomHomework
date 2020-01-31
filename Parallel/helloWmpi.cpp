#include "mpi.h"
#include <iostream>
#include <ctime>
#include <math.h>
using namespace std;


void doTheMath(int* rad_ray, int* vector, int* result, int problemSize, int local) //my matrixVector function
{
	int n = 0;
	for(int i = 0; i < local; i++) //outer loop, for each position in result vector
	{
		for(int j = 0; j < problemSize; j++) //this part does the matrix*vector math
		{
			result[i] += (rad_ray[j+n]*vector[j]);
		}
		n += problemSize;
	}
}

int getRowCount(int rowsTotal, int Rank, int Size) 
{
    return (rowsTotal / Size) + (rowsTotal % Size > Rank);
}

void doTheMathSerial(int* rad_ray, int* vector, int* result, int new_max, int max_number) //my matrixVector function
{
	int n = 0;
	for(int i = 0; i < new_max; i++) //outer loop, for each position in result vector
	{
		for(int j = 0; j < new_max; j++) //this part does the matrix*vector math
		{
			result[i] += (rad_ray[j+n]*vector[j]);
		}
		n += new_max;
	}
}

int main(int argc, char **argv)
{
	int rank, size, problemSize, arraySize;
	int n, n_local, n_slaveBound, n_masterBound;
	int x, y, z;
	double startTime, endTime, totalTime = 0.0;
	int* rad_ray = NULL; //initial matrix
	int* vector = NULL; //vector
	int* result = NULL; //result vector
	int* newResult = NULL;
	int* newMatrix = NULL;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(rank == 0)
	{
		problemSize = atoi(argv[1]);
		arraySize = problemSize*problemSize;
		newResult = new int[problemSize];
		newMatrix = new int[arraySize];

	}

	MPI_Bcast(&problemSize, 1, MPI_INT, 0, MPI_COMM_WORLD);
	//MPI_Bcast(&arraySize, 1, MPI_INT, 0, MPI_COMM_WORLD);

	n_local = getRowCount(problemSize, rank, size);
    	n_slaveBound = problemSize * n_local;
	//arraySize -- master upper bound


	rad_ray = new int[n_slaveBound];
	vector = new int[n_local*size];
	result = new int[n_local*size];	
	
	for(int i = 0; i < n_slaveBound; i++)
	{
		rad_ray[i] = (rand() % 1000) + 1;
		if(i < (n_local*size))
		{
			vector[i] = 1;
			result[i] = 0;
		}
	}

	if(rank == 0)
		startTime = clock();
	MPI_Barrier(MPI_COMM_WORLD);
	doTheMath(rad_ray, vector, result, problemSize, n_local);
	MPI_Barrier(MPI_COMM_WORLD);
	if(rank == 0)
	{
		endTime = clock(); //end get time
		totalTime += (endTime - startTime); //add time to total time	
	}
	MPI_Barrier(MPI_COMM_WORLD);
	
	if(!rank) 
	{
       	x = n_slaveBound;
       	for (int i = 1; i < size; i++) 
		{
			cout << "Received from: " << i << endl;
			y =  problemSize * getRowCount(problemSize, i, size);
       		MPI_Recv(newMatrix + x, y, MPI_INT, i, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
       		x += y;
       	}
    	}
    	else 
	{ 
		cout << "Sending from: " << rank << endl;
        	MPI_Send(rad_ray, n_slaveBound, MPI_INT, 0, 2, MPI_COMM_WORLD);
    	}
	MPI_Barrier(MPI_COMM_WORLD);

	if(!rank) 
	{
       	x = n_local;
       	for (int i = 1; i < size; i++) 
		{
			cout << "Received from: " << i << endl;
			y = getRowCount(problemSize, i, size);
       		MPI_Recv(newResult + x, y, MPI_INT, i, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
       		x += y;
       	}
    	}
    	else 
	{ 
		cout << "Sending from: " << rank << endl;
        	MPI_Send(result, n_local, MPI_INT, 0, 2, MPI_COMM_WORLD);
    	}
	MPI_Barrier(MPI_COMM_WORLD);
	


	if(rank == 0)
	{
		cout << endl << "Checking Results!" << endl;
		rad_ray = NULL;
		vector = NULL;
		result = NULL;
		rad_ray = new int[arraySize];
		vector = new int[problemSize];
		result = new int[problemSize];

		for(int i = 0; i < arraySize; i++)
		{
			rad_ray[i] = newMatrix[i];
			if(i < problemSize)
			{
				vector[i] = 1;
				result[i] = 0;
			}
		}
		doTheMathSerial(rad_ray, vector, result, problemSize, arraySize);
		
		for(int i = 0; i < problemSize; i++)
		{
			if(result[i] != newResult[i])
			{
				cout << "Check Failed" << endl;
				break;
			}
			else
			{
				cout << "Passed!!" << endl;
				cout << "Time taken to compute parallel results: " << totalTime/1000000 << " seconds." << endl;
				
				break;
			}		
		}	
	}

	//cout <<rank << "-" << size << " / " << n_local << " / " << n_slaveBound << endl;
	MPI_Finalize();
	return 0;
}
