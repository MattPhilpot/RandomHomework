#include <iostream>
#include <ctime>
#include <math.h>
#include "mpi.h"
using namespace std;



void doTheMathSerial(double * rad_ray, double * vector, double * result, int new_max) //my matrixVector function
{
	int n = 0;
	#pragma omp parallel for
	for(int i = 0; i < new_max; i++) //outer loop, for each position in result vector
	{
		for(int j = 0; j < new_max; j++) //this part does the matrix*vector math
		{
			result[i] += (rad_ray[j+n]*vector[j]);
		}
		n += new_max;
	}
}
#define EPSILON 1.0e-3
int main(int argc, char **argv)
{
	double * rad_ray = NULL; //initial matrix
	double * vector = NULL; //vector
	double * result = NULL; //result vector
	double * Ax = NULL;
	double * Ap = NULL;
	double * r = NULL;
	double * p = NULL;
	double alpha = 0;
	double rsOLD = 0.0;
	double rsNEW = 0.0;
	int x = 0; //really cool variable
	int y = 0;
	int n = 0;
	int max_number = 0;
	int new_max = 0;
	double temp = 0;
	double* xx = NULL;
	int rank, size;
	MPI_Status status; //gogo MPI stuff
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if(rank == 0)
	{
		cout << "How big would you like a side to be? ";
		cin >> new_max;
		max_number = new_max*new_max;
		cout << "Range Size? (1 - n) ";
		cin >> n;
		cout << "\nGenerating Random List of Size " << max_number << " with elements ranging from 1 - " << n << "..." << endl;
		rad_ray = new double [max_number];	/*	Applying new max_size to array	*/
		vector = new double [new_max];
		result = new double [new_max];
		Ax = new double [new_max];
		Ap = new double [new_max];
		r = new double [new_max];
		p = new double [new_max];
		xx = new double [new_max];

		for(x = 0; x < max_number; x++) //fill the matrix with random variables
		{
			rad_ray[x] = (rand() % n) + 1;
			if (x < new_max)
			{
				vector[x] = 1;
				result[x] = 0;
			}
		}
		#pragma omp parallel for
		for(x = 0; x < new_max; x++) //fill the matrix with random variables
		{
			for(y = 0; y < new_max; y++)
			{
				if(x > y)
					rad_ray[(x * new_max) + y] = x;
				if(y > x)
					rad_ray[(x * new_max) + y] = y;
				if(x == y)
					rad_ray[(x * new_max) + y] = 1;
			}
		}	


		doTheMathSerial(rad_ray, vector, Ax, new_max);

		for(x = 0; x < new_max; x++)
		{
			r[x] = 1 - Ax[x];
			rsOLD += r[x] * r[x];
			p[x] = r[x];
		}
	
		for(x = 0; x < new_max; x++)
		{
			doTheMathSerial(rad_ray, p, Ap, new_max);
	
			temp = 0;
			for(y = 0; y < new_max; y++)
				temp -= (p[y] * Ap[y]);
			alpha = rsOLD / temp;

			for(y = 0; y < new_max; y++)
				vector[y] -= (alpha*p[y]);

			for(y = 0; y < new_max; y++)
				r[y] -= (alpha * Ap[y]);

			rsNEW = 0;
			for(y = 0; y < new_max; y++)
				rsNEW += r[y] * r[y];

			if (sqrt(rsNEW)  > EPSILON)
			{
				cout << "Exiting: SUCCESS!" << endl;
				break;
			}
			#pragma omp parallel for
			for(y = 0; y < new_max; y++)
				p[y] = r[y] + ((rsNEW/rsOLD)* p[y]);

			rsOLD = rsNEW;
		}
	}
	MPI_Finalize(); //FINALIZE dat stuff
}
