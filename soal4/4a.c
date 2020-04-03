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
int step = 0;

void* kali(void* arg) {
  int i = step++;

  for (int k = 0; k < 4; k++)
    for (int j = 0; j < 5; j++)
      matC[i][j] += matA[i][k] * matB[k][j];
}

//barisx
//A=3X2 , B=2X3
int main() {
  srand(time(NULL));
  printf("A = \n");
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      matA[i][j] = rand()%20;
      printf("%3d", matA[i][j]);
    }
    printf("\n");
  }
  printf("B = \n");
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 5; j++) {
      matB[i][j] = rand()%20;
      printf("%3d", matB[i][j]);
    }
    printf("\n");
  }

  //declaring threads
  pthread_t tid[20];

  for (int i = 0; i < 20; i++) {
    pthread_create(&(tid[i]), NULL, &kali, NULL);
  }

  for (int i = 0; i < 20; i++) {
    pthread_join(tid[i], NULL);
  }


  printf("Hasil perkalian matriks A dan B :\n");
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 5; j++) {
      printf("%4d", matC[i][j]);
    }
    printf("\n");
  }

}
