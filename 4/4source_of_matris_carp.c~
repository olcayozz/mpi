#include <mpi.h>
#include <stdio.h>

int komsuGetir(int proc, int komsu);

int main(int argc, char** argv) {

  int world_rank;
  int world_size;
  int val=-1;

  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  if(world_rank==10)
  {
    val=9;
  }
int iterator = 0;
do{
  int h[4];//herkes kendi komsularini ogreniyor.
    h[0] = komsuGetir(world_rank,1);
    h[1] = komsuGetir(world_rank,2);
    h[2] = komsuGetir(world_rank,3);
    h[3] = komsuGetir(world_rank,4);

    for(int i=0; i < sizeof(h)/sizeof(h[0]); i++)
    {
      MPI_Send(&val, 1, MPI_INT, h[i], 0, MPI_COMM_WORLD);
    }
    for(int i=0; i < sizeof(h)/sizeof(h[0]); i++)
    { 
      int tmpVal = -1;
      MPI_Recv(&tmpVal, 1, MPI_INT, h[i], 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      if(val == -1) 
        val=tmpVal;
    }
iterator++;
}while(iterator<4);
  
  if(val!=-1)
    printf("[%d] \t-->\t val = %d \n",world_rank,val);

  MPI_Finalize();
}

int komsuGetir(int proc, int komsu){
  int bit[4];
  komsu--;
  bit[0] = (int) proc/8;
  bit[1] = (int) (proc-(bit[0]*8))/4;
  bit[2] = (int) (proc-(bit[0]*8)-(bit[1]*4))/2;
  bit[3] = (int) (proc-(bit[0]*8)-(bit[1]*4)-(bit[2]*2));
  if(bit[komsu]==0)
    bit[komsu]=1;
  else
    bit[komsu]=0;

  int rS= bit[0]*8+bit[1]*4+bit[2]*2+bit[3];
  return rS; 
}
