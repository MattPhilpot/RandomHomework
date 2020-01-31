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
	
using namespace std;


int** matrixVectorMultiply(int **A, int **x, int row, int col)
{
	int **initResults; // Creates a new initial results array for matrixArr * vectArr
	int **results; // Creates a results array

#pragma omp parallel for private (n)
	for(int m = 0; m < row; m++) // Outer loop to access the rows.
	{
		for(int n = 0; n < col; n++) // Inner loop to access the columns.
		{
			initResults[m][n] = A[m][n] * x[m][0]; // First multiply the matrix to the vector and store the results in an initial results array.
			results[m][0] = results[m][0] + initResults[m][n]; // Then add each element that are in the same row and store the results in the results vector.
		} // End inner for loop
	} // End outer for loop

/* Uncomment to check results by printing them.
	cout << "Matrix x vector results ouput: " << endl;
	
	for(int m = 0; m < row; m++) // Loops through each row in the results vector and prints the value of the matrix x vector results.
	{							
		cout << results[m][0] << endl;
	}
*/
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

#define EPSILON 1.0e-10

int main(int argc, char *argv[])
{
	double startT, stopT, finalT;	// Start, stop, and final time variables for timing user time
	double overallT = 0.0;	// Initialized overall user time of the program set to 0.0
	int row = 750;		// Initialize the number of rows
	int col = 750;		// Initialize the number of columns
	int **A;			// Create a new matrix A
	int **ax;			// Holds the result of matrix A * vector x 
	int **ap;			// Holds the result of matrix A * the residual matrix p
	int **b;			// Constant vector
	int **x;			// Solution vector
	int **r;			// result vector
	int **rt;			// Result vector, r, transposed
	double **rsold;		// 
	double **rsnew;		//
	int **p2;			// Holds the residual matrix p	
	int **pt;			// Holds the residual matrix p, transposed.
	int alpha;			// 
	int p;				// MPI Processes
	int id;				// Process Rank
	int m;				// Rows in A
	int n;				// Columns in A


	startT = clock();

// First initializing values for matrix A and vector x.
#pragma omp parallel for
	for(int m = 0; m < row; m++) //Outer for loop to access the rows.
	{
		x[m][0] = m; //Initializing the values of the vector array to have the same values as the row number.

#pragma omp parallel for
		for(int n = 0; n < col; n++) // Inner for loop to access the columns in the current row.
		{
			A[m][n] = 1; // Setting the matrix m row and n column to 1.
		}// End inner for loop.
	} // End outer for loop.
	
/*
	// Second initializing values for the matrix and vector.
	for(int m = 0; m < row; m++) //Outer for loop to access the rows.
	{
		x[m][0] = 1; //Initializing the values of the vector array to all be 1.

		for(int n = 0; n < col; n++) // Inner for loop to access the columns in the current row.
		{
			A[m][n] = m + n; // Setting the matrix m row and n column to have values equal to m + n + 1.
		}// End inner for loop.
	} // End outer for loop.
*/

	ax = matrixVectorMultiply(A, x, row, col); // A*x results are in ax.

	for (m = 0; m < row; m++)
		r[m][0] = b[m][0] - ax[m][0];
	
	p2 = r;
	rt = transpose(r, row, 0);
	pt = transpose(p2, row, 0);
	
	for (m = 0; m < row; m++)
		rsold[m][0] = rt[m][0] * r[m][0];

	ap = matrixVectorMultiply(A, p2, row, col); // A * p2 results are in ap.
	
	for (m = 0; m < row; m++)
	{
		alpha = (int)(rsold[m][0]/(p2[m][0] * ap[m][0]));
		x = x + alpha * p2[m][0];
		r = r - alpha * ap[m][0];
		rsnew[m][0] = (double)(rt[m][0]* r[m][0]);

		if(sqrt(double(rsnew[m][0])) < EPSILON)
			break;

		p2 = r + (int)rsnew[m][0]/((int)rsold[m][0] * p2[m][0]);
		rsold = rsnew;
	}

	stopT = clock();
	overallT = stopT - startT;
	finalT = overallT/1000000;
	cout << "Total user time: " << finalT << endl;

	return 0;
}

