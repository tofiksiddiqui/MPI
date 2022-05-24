#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {

	int root_rank = 0, size, my_rank, i;
	int send_buf[4]={10,20,30,40};
	int recv_buf[2];
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(size != 2)
	{
		printf("This application is meant to be run with 2 MPI processes.\n");
		MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
	}

	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    /*Root process will scatter the data to other processes including itself.*/
	MPI_Scatter(send_buf, 2, MPI_INT, &recv_buf, 2, MPI_INT, root_rank, MPI_COMM_WORLD);
	printf("Data in process [%d] is: \n", my_rank);
	for( i=0; i<2; i++)
		printf("%d \n", recv_buf[i]);
	MPI_Finalize();
	return 0;
}