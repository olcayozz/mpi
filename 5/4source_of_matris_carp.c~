#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char** argv) {
  MPI_Init(NULL, NULL);
	
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  int val[4] = {0,0,0,0};

  if(world_rank==0){ 
    memcpy(val, (int [4]){45,27,3,6}, sizeof(int)*4);
  }
  if(world_rank==1){
    memcpy(val, (int [4]){12,48,1,7}, sizeof(int)*4);
  }
  if(world_rank==2)
  {
    memcpy(val, (int [4]){112,2,9,11}, sizeof(int)*4);
  }
  if(world_rank==3)
  {
    memcpy(val, (int [4]){13,29,36,41}, sizeof(int)*4);
   }
  printf("[%d] ; val = [%d] \n\n",world_rank,val[0]);

  MPI_Finalize();
}
