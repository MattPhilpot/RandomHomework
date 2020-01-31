#include <iostream>
#include <ctime>
#include "mpi.h"
using namespace std;

void swap(int *myArray, int i, int j) 
{
	int temp = myArray[i];
	myArray[i] = myArray[j];
	myArray[j] = temp;
}

int partition(int *myArray, int start, int end) //do some partitioning
{
	if (start >= end) //MAGIC
		return 0;
	int pivotValue = myArray[start];
 	int low = start;
	int high = end - 1;
  
	while (low < high) 
	{
		while (myArray[low] <= pivotValue && low < end) 
			low++;
		while (myArray[high] > pivotValue && high > start) 
			high--;
		if (low < high) 
			swap(myArray, low, high);
	}
	swap(myArray, start, high);
	return high;
}

void quicksort(int *data, int start, int end) //this is where most of the quicksort magic happens.. but he's gotta call in his buddies to help get the job done
{
	if(end-start+1 < 2) 
		return;

	int pivot = partition(data, start, end);
	quicksort(data, start, pivot);
	quicksort(data, pivot+1, end);
}

int main(int argc, char *argv[]) 
{
	int rank, size; //initialize rank/size
	MPI_Init(&argc, &argv); //and everything that is needed for parallel
	MPI_Comm_rank (MPI_COMM_WORLD, &rank); //this
	MPI_Comm_size (MPI_COMM_WORLD, &size); //and this too
	MPI_Status status;
	double startTime, endTime, totalTime = 0.0; //timing variables
	if (argc < 2) //after initializing, since last time I did this... I got 20 points off. If the size isn't given as a parameter, it exits and is very angry.
	{
		if (rank == 0)
			cout << "Error! Please provide an the size of the problem via the arguments" << endl;
		exit(0); //assuming you made this this far, let's move on!
	}

	int length = atoi(argv[1]); //get the size from the arguments given!!!!!!!! YAY
	int localSize =  length; //set an additional variable that's = length but will be the local size eventually
	int *myArray = new int[length];	//this is the local sexy array. It's way better than a standard array.
	int i, s, pivot; //cool variables for my for loops and pivots
	for (i = 0; i < (length/size); i++) //randomly fill the array
		myArray[i] = rand(); //with awesome variables
	startTime = clock(); //starting the clock
	if (rank == 0) //send the random array to mister Big 0
	{   
		for (i = 1; i < size; i++)
			MPI_Recv(myArray + (i * length / size), length / size, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
	}
	else 
	{
		MPI_Send(myArray, length/size, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}

  	for (s=size; s > 1; s /= 2) //each process picks its pivot to begin the quicksort magic
	{
    	if (rank % s == 0) 
		{
			pivot = partition(myArray, 0, localSize);
			MPI_Send(myArray+pivot, localSize - pivot, MPI_INT, rank + s/2, 0, MPI_COMM_WORLD);
			localSize = pivot;
		}
		else if (rank % s == s/2) 
		{
      		MPI_Recv(myArray, length, MPI_INT, rank - s/2, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
      		MPI_Get_count(&status, MPI_INT, &localSize);
    	}
  	}
  	quicksort(myArray, 0, localSize);
	endTime = clock();
	totalTime = endTime - startTime;
	if (rank == 0)
		cout << "It took a good " << totalTime/1000000.00 << " seconds to sort that list. Good Job!" << endl;
  	MPI_Finalize();
}
