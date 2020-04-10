#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <ncurses.h>

//Input % rate of positive chance
//Output whether positive or no
int chance(int posRate){
  time_t t;
  srand((unsigned) time(&t));
  int fate = (rand() % 100) + 1;
  return fate <= posRate;
}

void *pokemonFinder(void *vargp){
  while(true){
    printf("Looking for a pokemon, please wait...\n");
    sleep(10);
    if(chance(60)){
        printf("A wild Pokemon appeared!\n");
        time_t t;
        srand((unsigned) time(&t));
        int fate = (rand() % 100) + 1;
        int pokemonType = rand() % 4;
        const char * normal[] = {"Bulbasaur","Charmander","Squirtle","Rattata","Caterpie"};
        const char * rare[] = {"Pikachu","Eevee","Jigglypuff","Snorlax","Dragonite"};
        const char * legend[] = {"Mew","Mewtwo","Moltres","Zapdos","Articuno"};
        if (fate <= 80) {
          printf("A wild %s is appeared!\n",normal[pokemonType]);
        }
        else if (fate <= 95){
          printf("A wild %s is appeared!\n",rare[pokemonType]);
        }
        else {
          printf("A wild %s is appeared!\n",legend[pokemonType]);
        }


    }
    else {
        printf("10 seconds passes, no pokemon found. Search again..\n");
    }
  }

}


int main(){
  int state = 0;
  pthread_t pokemonFinderThread;

  while(true){
    if (state == 0){
      printf("[1] Cari Pokemon\n");
    }
    else {
      printf("[1] Stop Cari Pokemon\n");
    }
    printf("[2] Pokedex\n");
    printf("[3] Shop\n");
    printf("> : ");
    int option;
    scanf("%d",&option);
    if (option == 1) {
      if (state == 0 ) {
        state = 1;
        pthread_create(&pokemonFinderThread,NULL,pokemonFinder,NULL);
      }
      else if (state == 1) {
        pthread_cancel(pokemonFinderThread);
        printf("Pokemon finding is stopped..\n");
        state = 0;
      }

    }
  }

  return 0;
}
