#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
#include <math.h>
#include <mpi.h>
using namespace std;

#define TAG0 0
#define TAG1 1
#define TAG2 2
#define TAG3 3

int main(int argc, char *argv[])
{
	int* rad_ray = NULL;
	int* queue = NULL;
	string input;
	double t1, t2; /*	For timing how long sort takes in seconds	*/
	int rank, comm_size, dest, source, tag = 1;
	int n = 0; 
	int x = 0;
	int position = 0;
	int numb = 0;
	int max_number = 0;
	int new_max = 0;
	int tmp = 0;
	double digits = 0;
	ifstream infile;

	MPI_Status Stat;
	MPI_Init(&argc, &argv);	/*	Initialize MPI	*/
	MPI_Comm_size(MPI_COMM_WORLD, &comm_size);	/*	Get the number of processes	*/
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);	/*	Get the rank, between 0 and (comm_size-1)	*/


	cout << "Welcome to Philpot's Radix Sort with MPI\n\n";
	
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

/*	For debugging, makes sure file is being read correctly	*/
/*	for(int i = 0; i<new_max; i++)
	{
		cout << rad_ray[i] << " ";
	} */

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
//	unsigned int start = clock();
	t1 = MPI_Wtime();

/*	Radix Sort. Where most radix sorts call a recurring function, I avoid calling functions altogether to save on time, space, and overhead.	*/

	int i, j;
	for(n = 10; n <= digits; n*=10) /*	Determines which position will be sorted. ie. 1's, 10's 100's, etc.	*/
	{
		cout << "\nSorting the " << (n/10) << "'s position" << endl;

		for(numb = 0; numb <= 9; numb++) /*		Determines which number sorted and put in the queue	*/
		{
			if(rank == 0)
			{
				source = 1;
			//	for(dest = 1; dest < comm_size; dest++)
				MPI_Send(&numb, 1, MPI_INT, dest, TAG0, MPI_COMM_WORLD); /*	If Process 0, distribute numb to other processes	*/
				for(dest = 1; dest < comm_size; dest++)
				{
					i = MPI_Recv(&i, 1, MPI_INT, dest, TAG1, MPI_COMM_WORLD, &Stat);
					j = MPI_Recv(&j, 1, MPI_INT, dest, TAG2, MPI_COMM_WORLD, &Stat);
					queue[i] = rad_ray[j];
				}
			/*	for(x = 0; x < new_max; x++) 
				{
					rad_ray[x] = queue[x];

				}*/
			}
			else
			{
				dest = 0;
				source = 0;
				numb = MPI_Recv(&numb, 1, MPI_INT, 0, TAG0, MPI_COMM_WORLD, &Stat);	/*	If !Process 0, receive numb and begin sort	*/
				for(x = 0; x < new_max; x++) /*		Searches through the list for numb in the	*/
				{
					tmp = rad_ray[x] % n;
					if(n >= 100)
					{
						tmp /= (n/10);
					}
					if(tmp == numb)	/*	If equal, place into queue.*/
					{
				//		queue[position] = rad_ray[x];
						MPI_Send(&position, 1, MPI_INT, 0, TAG1, MPI_COMM_WORLD);
						MPI_Send(&x, 1, MPI_INT, 0, TAG2, MPI_COMM_WORLD);
						position++;
					}
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
	t2 = MPI_Wtime();

	/* This is for debugging, to see if final list is indeed sorted */
	cout << "\n\n\nFinal Sorted List" << endl;
	for(int i = 0; i<new_max; i++)
	{
		cout << rad_ray[i] << " ";
	} 
	cout << endl;
	cout << "Time taken to complete in seconds: " << (t2 - t1) << endl;
//	system("Pause");
	MPI_Finalize(); /*	Finish with MPI	*/
	return 0;
}
