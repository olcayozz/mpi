#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>

//Her işlemci de 4'er sayı
const int countOfNums = 4;

void init(int*, int);// Tum dugumlere baslangic sayilarini giriyoruz.
void print(int*, int);// sayilari ekrana yazdirir.
int min_index(int*);
int max_index(int*);
void oddEvensort(int*, int, int);//paralel siralama algoritması burada işletiliyor.


int main(int argc, char** argv) {
	int world_rank, world_size;
	int localNums[countOfNums];
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	init(localNums, world_rank);//Her işlemci initial local sayi dizisini doldurur.

	oddEvensort(localNums, world_rank, world_size);

	print(localNums, world_rank);
	MPI_Finalize();
	return 0;
}

void init(int* data, int world_rank) {
  if(world_rank==0){ 
    memcpy(data,(int [4]){45,27,3,6}, sizeof(int)*4);
  }
  if(world_rank==1){
    memcpy(data, (int [4]){12,48,1,7}, sizeof(int)*4);
  }
  if(world_rank==2)
  {
    memcpy(data, (int [4]){112,2,9,11}, sizeof(int)*4);
  }
  if(world_rank==3)
  {
    memcpy(data, (int [4]){13,29,36,41}, sizeof(int)*4);
  }
}

void print(int* localNums, int world_rank) {
	for (int i = 0; i < countOfNums; i++) {
		printf("[%d] \t-->\t data[%d] = %d \n",world_rank, i, localNums[i]);
	}
	printf("\n");
}

int min_index(int* data) {
	int i, min = data[0], mini = 0;

	for (i = 1; i < countOfNums; i++) {
		if (data[i] < min) {
			min = data[i];
			mini = i;
		}
	}
	return mini;
}

int max_index(int* data) {
	int i, max = data[0], maxi = 0;

	for (i = 1; i < countOfNums; i++) {
		if (data[i] > max) {
			max = data[i];
			maxi = i;
		}
	}
	return maxi;
}

int cmp(const void* ap, const void* bp) {
	int a = *((const int*)ap);
	int b = *((const int*)bp);

	if (a < b) return -1;
	else if (a > b) return 1;
	else return 0;
}

void oddEvensort(int* localNums, int world_rank, int world_size) {
	int i;
	int other[countOfNums];
	for (i = 0; i < world_size; i++) {
		qsort(localNums, countOfNums, sizeof(int), &cmp);
		int partener;
		if (i % 2 == 0) {
			if (world_rank % 2 == 0) {
				partener = world_rank + 1;
			}
			else {
				partener = world_rank - 1;
			}
		}
		else {
			if (world_rank % 2 == 0) {
				partener = world_rank - 1;
			}
			else {
				partener = world_rank + 1;
			}
		}
		if (partener < 0 || partener >= world_size) {
			continue;
		}

		if (world_rank % 2 == 0) {
			MPI_Send(localNums, countOfNums, MPI_INT, partener, 0, MPI_COMM_WORLD);
			MPI_Recv(other, countOfNums, MPI_INT, partener, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
		else {
			MPI_Recv(other, countOfNums, MPI_INT, partener, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Send(localNums, countOfNums, MPI_INT, partener, 0, MPI_COMM_WORLD);
		}

		if (world_rank < partener) {
			while (1) {
				int mini = min_index(other);
				int maxi = max_index(localNums);
				if (other[mini] < localNums[maxi]) {
					int temp = other[mini];
					other[mini] = localNums[maxi];
					localNums[maxi] = temp;
				}
				else break;
			}
		}
		else {
			while (1) {
				int maxi = max_index(other);
				int mini = min_index(localNums);

				if (other[maxi] > localNums[mini]) {
					int temp = other[maxi];
					other[maxi] = localNums[mini];
					localNums[mini] = temp;
				}
				else break;
			}
		}
	}
}
