
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BELUMREADY -1
#define READY 0
#define SIAP 1
#define MAXIMUM 100

struct shared{
    int status;
    int data[100];
};

int matA[4][2] , matB[2][5] , matC[4][5];
int row = 0; // untuk mengecek tiap baris pada matriksnya
int col = 0;
void* kali(void* arg) {
  if(col >= 5){
    col = 0;
    row++;
  }

  for (int i = 0; i < 2; i++) matC[row][col] += matA[row][i] * matB[i][col]; // Hasil kali matrix a dan b dijumlah ke matrix
col++;
}

//barisx
//A=4x2 B=SX5
int main() {
  srand(time(NULL));
  //menampilkan matriks A
  printf("A = \n");
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      matA[i][j] = rand()%20+1;
      printf("%3d", matA[i][j]);
    }
    printf("\n");
  }
  //menampilkan matriks B
  printf("B = \n");
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 5; j++) {
      matB[i][j] = rand()%20+1;
      printf("%3d", matB[i][j]);
    }
    printf("\n");
  }

  //declaring threads
  pthread_t tid[20]; // SIZE 20

  for (int i = 0; i < 20; i++) { // kalau i kurangdari 20 maka jalanin fungsi kali
    pthread_create(&(tid[i]), NULL, &kali, NULL);
  }

  for (int i = 0; i < 20; i++) { // buat wait
    pthread_join(tid[i], NULL);
  }

//Displaying hasil dari matrix
  printf("Hasil perkalian matriks A dan B :\n");
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 5; j++) {
      printf("%4d", matC[i][j]);
    }
    printf("\n");
  }

  key_t          ShmKEY;
  int            ShmID;
  struct shared  *ShmPTR;

  ShmKEY = ftok("key",100);
  ShmID = shmget(ShmKEY,sizeof(struct shared),IPC_CREAT|0666);
  if(ShmID < 0){
    printf("Shmget error\n");
    exit(1);
  }
  ShmPTR = (struct shared *) shmat(ShmID, NULL, 0);

  ShmPTR->status = BELUMREADY;
  int j = 0;
  int k = 0;

  for(int i = 0; i < 20; i++){
    /* code */
    if(k >= 5){
      /* code */
      j++;
      k = 0;
    }
    ShmPTR->data[i] = matC[j][k];
    k++;
  }
   ShmPTR->status = READY;

  printf("Jalanin yang B \n");
   while (ShmPTR->status != SIAP)
       sleep(1);
   printf("B sudah jalan\n");
   shmdt((void *) ShmPTR);
   printf("Proses kelar\n");
   shmctl(ShmID, IPC_RMID, NULL);
   exit(0);
   return 0;
}
