#include "mpi.h"
#include <iostream>
#include <ctime>
#include <math.h>
using namespace std;





int getRowCount(int rowsTotal, int Rank, int Size) //returns the number of rows a process is responsible for
{
    return (rowsTotal / Size) + (rowsTotal % Size > Rank);
}


int main(int argc, char **argv)
{
	int rank, size, problemSize, arraySize; //initialize variables
	int n, n_local, n_slaveBound, n_masterBound; //these are the main variables used
	int x, y, z;
	double startTime, endTime, totalTime = 0.0;
	int* rad_ray = NULL; //initial matrix
	int* vector = NULL; //vector
	int* result = NULL; //result vector
	int* newResult = NULL;
	int* newMatrix = NULL;
	MPI_Status status; //gogo MPI stuff
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(rank == 0) //process 0, the master thread initializes problem size and array size
	{
		problemSize = atoi(argv[1]);
		arraySize = problemSize*problemSize;
		newResult = new int[problemSize];
		newMatrix = new int[arraySize];
	}

	MPI_Bcast(&problemSize, 1, MPI_INT, 0, MPI_COMM_WORLD); //broadcast the problemsize
	//MPI_Bcast(&arraySize, 1, MPI_INT, 0, MPI_COMM_WORLD);

	n_local = getRowCount(problemSize, rank, size); //determine number of rows each process responsible for
    	n_slaveBound = problemSize * n_local; //number of elements each process responsible for
	//arraySize -- master upper bound


	rad_ray = new int[n_slaveBound]; //each process initializes...
	vector = new int[n_local*size];
	result = new int[n_local*size];	
	
	for(int i = 0; i < n_slaveBound; i++) //and fills its own arrays
	{
		rad_ray[i] = (rand() % 1000) + 1;
		if(i < (n_local*size))
		{
			vector[i] = 1;
			result[i] = 0;
		}
	}

	if(rank == 0) //start clock for runtime
		startTime = clock();
	MPI_Barrier(MPI_COMM_WORLD); //barrier cause I like it
	doTheMath(rad_ray, vector, result, problemSize, n_local); //the magic happens here
	MPI_Barrier(MPI_COMM_WORLD); //and because it gurantees nothing happens when it shouldn't
	if(rank == 0)
	{
		totalTime = 0.0;
		endTime = clock(); //end get time
		totalTime = (endTime - startTime); //add time to total time	
	}
	MPI_Barrier(MPI_COMM_WORLD);
	
	if(!rank) //send matrix to master thread for verification
	{
       	x = n_slaveBound;
       	for (int i = 1; i < size; i++) 
		{
			cout << "Received 1st part from: " << i << endl;
			y =  problemSize * getRowCount(problemSize, i, size);
       		MPI_Recv(newMatrix + x, y, MPI_INT, i, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
       		x += y;
       	}
    }
    else /* Uncomment next line to see when each process sends */
	{ 
	cout << "Sending from: " << rank << endl;
       	MPI_Send(rad_ray, n_slaveBound, MPI_INT, 0, 2, MPI_COMM_WORLD);
    }
	MPI_Barrier(MPI_COMM_WORLD);

	if(!rank) //send results to master thread for verification
	{
       	x = n_local;
       	for (int i = 1; i < size; i++) 
		{
			cout << "Received 2nd part from: " << i << endl;
			y = getRowCount(problemSize, i, size);
       		MPI_Recv(newResult + x, y, MPI_INT, i, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
       		x += y;
       	}
    }
    else /* Uncomment next line to see when each process sends */
	{ 
	cout << "Sending from: " << rank << endl;
       	MPI_Send(result, n_local, MPI_INT, 0, 2, MPI_COMM_WORLD);
    }
	MPI_Barrier(MPI_COMM_WORLD);
	


	if(rank == 0) //process 0, the master thread, checks the results... 
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
		doTheMathSerial(rad_ray, vector, result, problemSize, arraySize); //serial function to check results
		
		for(int i = 0; i < problemSize; i++)
		{
			if(result[i] != newResult[i]) //if >0 results are not the same, the computation was a failure
			{	
				cout << "Failed" << endl;
				x = 0;
				break;
			}
			else
				x = 1;	
		}
		if(x == 1)
		{
			cout << "Passed!!" << endl;
			cout << "Time taken to compute parallel results: " << totalTime/1000000 << " seconds." << endl;
		}
	}

	//cout <<rank << "-" << size << " / " << n_local << " / " << n_slaveBound << endl;
	MPI_Finalize(); //FINALIZE dat stuff
	return 0;
}
