#include <stdio.h>
#include <mpi.h>
#include "MyMPI.h"

typedef int dytpe;
#define MPI_TYPE MPI_INT

void compute_shortest_paths(int id, int p, dtype **a, int n)
{
	int i;
	int j;
	int k;
	int offset;
	int root;
	int* tmp;

	tmp = (dtype*) malloc(n * sizeof(dtype));
	for(k = 0; k < n; k++)
	{
		root = BLOCK_OWNER(k,p,n);
		if(root == id)
		{
			offset = k - BLOCK_LOW(id,p,n);
			for(j = 0; j < n; j++)
			{
				tmp[j] = a[offset][j];
			}
		}
		MPI_Bcast(tmp, n, MPI_TYPE, root, MPI_COMM_WORLD);
		for(i = 0; i < BLOCK_SIZE(id,p,n); i++)
		{
			a[i][j] = MIN(a[i][j], a[i][k] + tmp[j]);
		}
	}
	free(tmp);
}

int main (int argc, char *argv[])
{
	dytpe** a;			//
	dtype* storage;		//
	int i;				//
	int j;				//
	int k;				//
	int id;				//
	int m;				//
	int n;				//
	int p;				//

	void compute_shortest_paths(int, int, int**, int);

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	read_row_striped_matrix(argv[1], (void*) &a, (void*) &storage, MPI_TYPE, &m,&n, MPI_COMM_WORLD);

	if(m != n)
	{
		terminate(id, "Matrix must be square\n");
	}

	print_row_striped_matrix((void**) a, MPI_TYPE, m, n, MPI_COMM_WORLD);
	compute_shortest_paths(id, p, (dtype**) a, n);
	print_row_striped_matrix((void**) a, MPI_TYPE, m, n, MPI_COMM_WORLD);
	MPI_Finalize();

}