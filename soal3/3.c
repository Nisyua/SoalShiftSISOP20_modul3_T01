#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <syslog.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <dirent.h>
#include <string.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <ctype.h>
#include <unistd.h>

char cwd[100];
pthread_t threads[100];
pid_t child;
char *split_file[4],*split_path[20],nama_file[100],path[100];
int n = 0, m = 0;

void* move(void *arg);

int main(int argc, char *argv[]) {
    if(getcwd(cwd, sizeof(cwd)) != NULL) {
        // printf("Current working dir: %s\n", cwd);
    }
    int i=0,k=0;
	int p;
    if (strcmp(argv[1],"-f") == 0) {
        for(k = 2 ; k < argc ; k++ ){
            int p;
            pthread_create(&(threads[i]),NULL,move,argv[k]);
            pthread_join(threads[i],NULL);
            i++;
        }
    }

    else if (strcmp(argv[1],"*") == 0 && argc == 2) {
        i = 0;
        DIR *fd, *fdo;
        struct dirent *folder;
        char pl1[100],pl2[100];

        fd = opendir(cwd);
        int isdir = 0;

        if(fd == NULL)
        {
            printf("error\n");
        }
        while( (folder=readdir(fd)) )
        {
            if ( !strcmp(folder->d_name, ".") || !strcmp(folder->d_name, "..") )
            continue;

            int p;
            strcpy(pl1,cwd);
            strcat(pl1,"/");
            strcat(pl1,folder->d_name);
            if(folder->d_type == 8){
            pthread_create(&(threads[i]),NULL,move,pl1); //membuat thread
            pthread_join(threads[i],NULL);
            i++;
            }
        }

    }
    else if (strcmp(argv[1],"-d") == 0 && argc == 3) {
        i = 0;
        DIR *fd, *fdo;
        struct dirent *folder;
        char pl1[100],pl2[100];

        fd = opendir(argv[2]);
        int isdir = 0;

        if(fd == NULL)
        {
            printf("error\n");
        }
        while( (folder=readdir(fd)) )
        {
            if ( !strcmp(folder->d_name, ".") || !strcmp(folder->d_name, "..") )
            continue;

            int p;
            strcpy(pl1,argv[2]);
            strcat(pl1,"/");
            strcat(pl1,folder->d_name);
            //is regular file
            if(folder->d_type == 8){
            pthread_create(&(threads[i]),NULL,move,pl1);
            pthread_join(threads[i],NULL);
            i++;
            }
        }
    }


    return 0;
}

void* move(void *arg) {
    strcpy(path,arg);
    char *temp,*temp1;

	unsigned long i=0;
	pthread_t id=pthread_self();
	int iter;

    temp1 = strtok(path, "/");
    while( temp1 != NULL ) {
        split_path[m] = temp1;
        m++;
        temp1 = strtok(NULL, "/");
    }
    strcpy(nama_file,split_path[m-1]);

    temp = strtok(split_path[m-1], ".");
    while( temp != NULL ) {

        split_file[n] = temp;
        n++;
        temp = strtok(NULL, ".");
    }

    char lowerall[100];
    strcpy(lowerall,split_file[n-1]);
    for(int i = 0; lowerall[i]; i++){
        lowerall[i] = tolower(lowerall[i]);
    }

    DIR *folder, *folderopen;
    struct dirent *entry;
    char place2[100],place3[100];
    folder = opendir(cwd);
    int isdir = 0;
    printf("n = %d\n",n);
    if( n > 1 ){

        if(folder == NULL)
        {
            printf("error\n");
        }
        while( (entry=readdir(folder)) )
        {

            if(strcmp(entry->d_name,lowerall) == 0 && entry->d_type == 4){
                isdir = 1;
                break;
            }
        }


        if(isdir == 0){

            strcpy(place2,cwd);
            strcat(place2,"/");
            strcat(place2,lowerall);
            mkdir(place2, 0777);

        }
    }
    else{
        strcpy(place2,cwd);
        strcat(place2,"/");
        strcat(place2,"Unknown");
        mkdir(place2, 0777);
    }


    char asal[1024], tujuan[1024];


    strcpy(asal,arg);
    strcpy(tujuan,cwd);
    strcat(tujuan,"/");
    if(n == 1 ){
        strcat(tujuan,"Unknown");
    }
    else{
        strcat(tujuan,lowerall);
    }
    strcat(tujuan,"/");
    strcat(tujuan,nama_file);
    rename(asal,tujuan);
    n = 0;
    m = 0;

	return NULL;
}
