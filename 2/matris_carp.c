#include <mpi.h>
#include <stdio.h>


void load_matris_data_to_vec(int matris[16], int *matris_pointer[4][4]);


int *matris_A_vec[4][4];
int *matris_B_vec[4][4];

int matris_A[16] = 
{
  93,	3,	11,	27,
  82,	59,	8,	87,
  51,	3,	48,	88,
  40,	39,	53,	58
};

int matris_B[16] = {
  67,	25,	7,	68,
  41,	84,	66,	72,
  12,	48,	21,	46,
  84,	14,	52,	47
};



int main (int argc, char* argv[])
{
  load_matris_data_to_vec(matris_A, matris_A_vec);
  load_matris_data_to_vec(matris_B, matris_B_vec);

    // Initialize the MPI environment
    MPI_Init(NULL, NULL);


    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
/*
    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);
*/
if(world_rank==0) 
  for(int i = 0 ; i < world_size < i++)
  {
    MPI_Bcast(matris_A_vec[i][i], 1, MPI_INT, 0, MPI_COMM_WORLD)
  }

    // Print off a hello world message
    printf("Hello world from processor %s, rank %d"
           " out of %d processors\n",
           processor_name, world_rank, world_size);

   


    MPI_Finalize();// Finalize the MPI environment.


  return 0;
}


void load_matris_data_to_vec(int matris[16], int *matris_pointer[4][4]){
  int row = 4, columns=4;

  for(int i=0;i<row;i++){
    for(int j=0;j<columns;j++){
      matris_pointer[i][j] = & matris[(i*row)+j];
    }
  }
}

