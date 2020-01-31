/*	Judy Nguyen
	CSCE 3030
	Goodrum
	April 17, 2012
	Program 5 - Implement the Conjugate Gradient Method code from section 18.2. Determine the minimum problem size to require 32 seconds of user
	execution time on one processor. Produce a chart similar to Figure 18.2 for 1 to 16 processors using two cores per node under OpenMP. If your 
	implementation would take less than 32 seconds of user execution time, then place an outer loop which repeats the process enough times to use 
	32 seconds.
*/

#include <iostream>
#include <math.h>
#include <ctime>
#include <stdio.h>
#include "mpi.h"	
using namespace std;



struct beginEndCoords
{
	int beginX;
	int endX;
	int beginY;
	int endY;
	int X;
	int Y;
};

int* matrixVectorMultiply(int **A, int *x, int row, int col)
{
	int **initResults; // Creates a new initial results array for matrixArr * vectArr
	initResults = new int *[row];
	for(int i = 0; i < col; i++)
		initResults[i] = new int[col];

	int *results; // Creates a results array
	results = new int[col];
	for(int m = 0; m < row; m++) // Outer loop to access the rows.
	{
		for(int n = 0; n < col; n++) // Inner loop to access the columns.
		{
			initResults[m][n] = A[m][n] * x[m]; // First multiply the matrix to the vector and store the results in an initial results array.
			results[m] = results[m] + initResults[m][n]; // Then add each element that are in the same row and store the results in the results vector.
		} // End inner for loop
	} // End outer for loop
	return results;
}


// Transpose function will transpose a matrix.
int** transpose(int **mat, int row, int col)
{
	int **newMat;	// New matrix
	int m, n;	// row, m, and col, n, index variables

	for(m = 0; m < row; m++)
	{
		for(n = 0; n < col; n++)
			newMat[m][n] = mat[n][m]; // Transpose the columns and rows of mat into a new matrix called newMat.
	}

	return newMat;
}

beginEndCoords getCoords(int rowsTotal, int Rank, int Size) //returns the number of rows a process is responsible for
{
	int y = Rank / sqrt(Size);
	int x = Rank - (sqrt(Size)*y);
	int z = rowsTotal / (sqrt(Size));
	beginEndCoords returnMe;

	returnMe.beginX = x * z;
	returnMe.endX = (x+1) * z;
	returnMe.beginY = y * z;
	returnMe.endY = (y+1) * z;
	returnMe.Y = y;
	returnMe.X = x;

	return returnMe;
}


#define EPSILON 1.0e-10

int main(int argc, char *argv[])
{
	double startT, stopT, finalT;	// Start, stop, and final time variables for timing user time
	double overallT = 0.0;	// Initialized overall user time of the program set to 0.0
	int row = 900;		// Initialize the number of rows
	int col = 900;		// Initialize the number of columns
	int oldValue = 900;
	int **A = NULL;			// Create a new matrix A
	int *ax = NULL;;			// Holds the result of matrix A * vector x 
	int *ap = NULL;			// Holds the result of matrix A * the residual matrix p
	int *b = NULL;;			// Constant vector
	int *x = NULL;;			// Solution vector
	int *r;			// result vector
	int *rt;			// Result vector, r, transposed
	int *rsold;		// 
	int *rsnew;		//
	int *p2;			// Holds the residual matrix p	
	int *pt;			// Holds the residual matrix p, transposed.
	int alpha;			// 
	int p;				// MPI Processes
	int id;			// Process Rank
	int m;				// Rows in A
	int n;				// Columns in A

	int *mainAX = NULL;
	int *mainAP = NULL;

	beginEndCoords idCoords;

	startT = clock();
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);

// First initializing values for matrix A and vector x.
	idCoords = getCoords(row, id, p);
	
	row = idCoords.endY - idCoords.beginY;
	col = idCoords.endX - idCoords.beginX;

	
	if(id == 0)		
	{
		A = new int*[oldValue];
		for(int i = 0; i < oldValue; i++)
			A[i] = new int[oldValue];
		x = new int[oldValue];
		ax = new int[oldValue];
		b = new int[oldValue];
		ap = new int[oldValue];
		mainAX = new int[col];
		mainAP = new int[col];
	}
	else
	{
		A = new int*[col];
		for(int i = 0; i < col; i++)
			A[i] = new int[col];
		x = new int[col];
		ax = new int[col];
		b = new int[col];
		ap = new int[col];
	}
	
	cout << "Process: " << id << "(" << idCoords.X << ", " << idCoords.Y << ") -- " << row << " -- " << col << endl;

	for(int i = 0; i < row; i++) //Outer for loop to access the rows.
	{	
		x[i] = i; //Initializing the values of the vector array to have the same values as the row number.
		b[i] = 1;
		for(int j = 0; j < col; j++) // Inner for loop to access the columns in the current row.
		{
			if(i > j)
			{
				A[i][j] = m;
			}
			if(j > i)
			{
				A[i][j] = n;
			}
			if(i == j)
			{
				A[i][j] = 1;
			}
		}// End inner for loop. 
	} // End outer for loop.


	if(id == 0)
	{
		mainAX = matrixVectorMultiply(A, x, row, col); // A*x results are in ax.
	}
	else
	{
		ax = matrixVectorMultiply(A, x, row, col); // A*x results are in ax.
	}
	

	cout << "Process: " << id << " also reached end of this loop" << endl;
	for (int i = 0; i < row; i++)
		r[i] = b[i] - ax[i];
	
	p2 = r;
	rt = r;
	pt = p2;
	
	for (m = 0; m < row; m++)
		rsold[m] = rt[m] * r[m];


	if(id == 0)
	{
		mainAP = matrixVectorMultiply(A, p2, row, col); // A * p2 results are in ap.
	}
	else
	{
		ap = matrixVectorMultiply(A, p2, row, col); // A * p2 results are in ap.
	}


	
	
	MPI_Barrier(MPI_COMM_WORLD);
	if(!id) //send results to master thread
	{
		beginEndCoords temp;
       	for (int i = 1; i < p; i++) 
		{
			cout << "Received part from: " << i << endl;
			temp = getCoords(oldValue, i, p);
       		MPI_Recv(p2 + (i*row), row, MPI_INT, i, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Recv(ap + (i*row), row, MPI_INT, i, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Recv(rt + (i*row), row, MPI_INT, i, 4, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Recv(r + (i*row), row, MPI_INT, i, 5, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
       	}
    }
    else /* Uncomment next line to see when each process sends */
	{ 
	cout << "Sending from: " << id << endl;
       	MPI_Send(p2, row, MPI_INT, 0, 2, MPI_COMM_WORLD);
		MPI_Send(ap, row, MPI_INT, 0, 3, MPI_COMM_WORLD);
		MPI_Send(rt, row, MPI_INT, 0, 4, MPI_COMM_WORLD);
		MPI_Send(r, row, MPI_INT, 0, 5, MPI_COMM_WORLD);
    }

	if(id == 0)
	{
		for (m = 0; m < row; m++)
		{
			alpha = rsold[m]/(p2[m] * ap[m]);
			x = x + alpha * p2[m];
			r = r - alpha * ap[m];
			rsnew[m] = (double)(rt[m]* r[m]);

			if(sqrt(double(rsnew[m])) < EPSILON)
				break;

			p2 = r + (int)rsnew[m]/((int)rsold[m] * p2[m]);
			rsold = rsnew;
		}
	}
	

	MPI_Finalize();
	stopT = clock();
	overallT = stopT - startT;
	finalT = overallT/1000000;
	cout << "Total user time: " << finalT << endl;

	return 0;
}

