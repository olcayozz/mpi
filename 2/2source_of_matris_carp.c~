#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  int A[16],cols1[4],cols2[4],cols3[4],cols4[4];
  MPI_Init(NULL, NULL);
	
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  
  if (world_rank == 0) { /* MASTER */ 
    int matris_A[4][4] = 
	{
	  {93,	3,	11,	27},
	  {82,	59,	8,	87},
	  {51,	3,	48,	88},
	  {40,	39,	53,	58}
	}, matris_B[4][4] = {
	  {67,	25,	7,	68},
	  {41,	84,	66,	72},
	  {12,	48,	21,	46},
	  {84,	14,	52,	47}
	}; 
//Cols B matrisinin kolonları. Rows ise A matrisinin Carpanlarini temsil ediyor.
    for(int i = 0; i < 4 ; i++)/* Kolonlar ayristirildi */
    {
      cols1[i]=matris_B[i][0];
      cols2[i]=matris_B[i][1];
      cols3[i]=matris_B[i][2];
      cols4[i]=matris_B[i][3];
    }
    
    for(int i=0;i<4;i++)
      for(int j=0;j<4;j++)
        A[i+j*4] = matris_A[j][i];   

    for(int i = 1 ; i<4 ; i++) 
 //Her Kolon'u bir proses'e dagittik. 0'inci kolonu bu proseste cozecegiz.
    {
      MPI_Send(&cols2, 4, MPI_INT, 1, 1, MPI_COMM_WORLD);
      MPI_Send(&cols3, 4, MPI_INT, 2, 1, MPI_COMM_WORLD);
      MPI_Send(&cols4, 4, MPI_INT, 3, 1, MPI_COMM_WORLD);
    }

  
  } //else if (world_rank>0)
  { /* WORKERS */
    int local_matris_C[4][4],
	local_cols[4], 
	local_rows[4], 
	local_cols_C[4]={0,0,0,0}, 
     	carpanA = 0;
    
    MPI_Bcast(&A, 16, MPI_INT, 0, MPI_COMM_WORLD);
    //carpanA=rows[world_rank];
    //printf("\n[%d] : carpan = %d\n",world_rank, carpanA);

    if(world_rank>0)
        MPI_Recv(&local_cols, 4, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    else 
      for(int i=0;i<4;i++)
          local_cols[i]=cols1[i];
    
    //for(int i=0;i<4;i++)
      //printf("\n[%d] : Local_B[%d] = %d\n",world_rank, i, local_cols[i]);

    for(int m=0;m<4; m++) //m fazları temsil ediyor. Total'de 4 kez shift yapilacak.
    {
      for(int i=0;i<4;i++)//C'ler hesaplandi ;i kolon içerisindeki satırları temsil ediyor.
        {
          //int aShifter=(i+i*world_size+m)%16;
	  int aShifter=(i+i*world_size+m)%16;
          local_cols_C[i]+=A[aShifter]*local_cols[i];//A'nin shift'i burada.

if(world_rank==2 && i==1) printf("[%d] : Local_C[%d] = %d * %d = %d --> %d\n",world_rank, i, A[aShifter], local_cols[i],A[aShifter]*local_cols[i],local_cols_C[i]);

//if(world_rank==2 && i==1) printf("\n[%d] : Local_C[%d] = %d = %d * %d \n",world_rank, i, local_cols_C[i], A[aShifter], local_cols[i]);
        }
      int tmp = local_cols[0];//shift local B      
      for(int i=0; i<3 ;i++)
      { 
        //local_cols_C[i]+=local_rows[i] * local_cols [i];
        local_cols[i]=local_cols[i+1];
      }
      local_cols[3]=tmp;  
      //if(world_rank==1 && m==3) printf("\n[%d] Local_C[%d] = %d\n\n",world_rank,m,local_cols_C[2]);  
    }
  
    //for(int i=0;i<4;i++) printf("\n[%d] : Local_C[%d] = %d\n",world_rank, i, local_cols_C[i]);
  
      //printf("\n[%d] Local_C[%d] = %d\n\n",world_rank,1,local_cols_C[1]);
   }
  MPI_Finalize();
}
