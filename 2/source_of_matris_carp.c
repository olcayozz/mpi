#include <mpi.h>
#include <stdio.h>



int *matris_A_vec[4][4];
int *matris_B_vec[4][4];
void load_matris_data_to_vec(int matris[4*4], int *matris_pointer[4][4]);

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
  MPI_Status status;
  int tmp;
  
  load_matris_data_to_vec(matris_A, matris_A_vec);
  load_matris_data_to_vec(matris_B, matris_B_vec);

    
  MPI_Init(NULL, NULL);// Initialize the MPI environment

  int world_size;// Get the number of processes
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    
  int world_rank;// Get the rank of the process
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

if(world_rank==0) 
{
  *matris_A_vec[1][1]=95;
} else
{ 
  printf("\nREC Basladi");
  printf("\nmatris 1,1 = %d\n",*matris_A_vec[1][1]);
  
  MPI_Bcast(matris_A_vec, 1, MPI_INT, 0, MPI_COMM_WORLD);
  
  for(int i = 0 ; i < world_size ; i++)
  {
    printf("\nBroadcastedA = %d ve proc = %d",*matris_A_vec[i][i],world_rank);
  }
  printf("\nREC Bitti");
}
  
  

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

