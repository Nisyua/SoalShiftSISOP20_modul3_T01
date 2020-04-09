#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX 100
//source gfg

int matA[4][2] , matB[2][5] , matC[4][5];
int step = 0; // untuk mengecek tiap baris pada matriksnya

void* kali(void* arg) {
  int i = step++;

  for (int k = 0; k < 4; k++)
    for (int j = 0; j < 5; j++)
      matC[i][j] += matA[i][k] * matB[k][j]; // Hasil kali matrix a dan b dijumlah ke matrix c
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

}
