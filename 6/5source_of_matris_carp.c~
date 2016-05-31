#include <stdio.h>
#include "mpi.h"
#include <time.h>
#include <stdlib.h>

void Oku(int *, int world_rank);
int findMax(int *);
const int MASTER_PROC=0;
const int sizeOfArray = 10;//Dosya okunduktan sonra bosluklardan ayrılan sayıların işlem sayısına bolumu sonrası yaklasik olarak 10'ar adet sayının işlemlere dagitalacagini varsaydim. Yani "10 işlem calisiyor ise toplamda dosyada 160 sayi var" varsayımıyla ilerliyorum.

int main(int argc, char* argv[]) {
    int world_size;
    int world_rank;
    int localSayilar[sizeOfArray];
    int localMax=0;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    Oku(localSayilar,world_rank); //dosyadaki veriler tum işlemlere dagitildigini varsaydim.
    localMax=findMax(localSayilar); //Her işlem kendi max değerini bulur.
    
    
    printf("[%d] \t-->\t localMaximum = %d \n",world_rank,localMax);//her işlemci kendi ekranına localMax değerlerini yazdırdı.
    if(world_rank!=MASTER_PROC) //Her işlem kendi max değerini master işleme gönderir.
    {
       MPI_Send(&localMax, 1, MPI_INT, MASTER_PROC, world_rank, MPI_COMM_WORLD);
    }
    else//Master işlem diğer işlemlerden gelen max değerleri toplar ve global Max'i bulur.
    {
      localSayilar[0]=localMax;
     for(int i=1;i<world_size-2;i++)
      {	 
	MPI_Recv(&localSayilar[i], 1, MPI_INT, i, i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      }
      printf("\nGlobal Maximum = %d\n\n",findMax(localSayilar));//Master işlem globalMax değerini kendi ekranına yazdırır.
    }

  MPI_Finalize();
  return 0;
}

//Dosyadan boşluklarla ayırarak sayıları list dizisine atar. Ve bu diziyi döndürür.
void Oku(int* data, int world_rank) {  
  srand(world_rank+1);
  for (int i = 0; i < sizeOfArray; i++) {
    data[i] = rand() % 100;  
  }
}

int findMax(int* data){
  int tmp = 0;
  for(int i=0;i<sizeOfArray;i++)
  {
    if(tmp<data[i])
      tmp=data[i];
  }  
  return tmp;
}
