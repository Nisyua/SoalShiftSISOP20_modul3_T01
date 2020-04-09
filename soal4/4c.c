#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

int main() {
  int filedeskriptor[2]; // ada 2 ujung

  pid_t pid;

  pipe(filedeskriptor);
//  pipe(fd+2);

  pid = fork();
  if (pid == 0) {
    dup2(filedeskriptor[1], 1);
    close(filedeskriptor[0]);
    close(filedeskriptor[1]);
    // close(fd[2]);
    // close(fd[3]);
    char *argv[] = {"ls", NULL};
    execv("/bin/ls", argv);
  }
  while(wait(NULL) > 0);

  pid = fork();
  if (pid == 0) {
    dup2(filedeskriptor[0], 0);
    close(filedeskriptor[0]);
    close(filedeskriptor[1]);
    // close(fd[2]);
    // close(fd[3]);
    char *argv[] = {"wc" ,"-l", NULL};
    execv("/usr/bin/wc", argv);
  }
}
  // while(wait(NULL) > 0);
  //
  // dup2(fd[2], 0);
  // close(fd[0]);
  // close(fd[1]);
  // close(fd[2]);
  // close(fd[3]);
  // char *argv[] = {"tail", NULL};
  // execv("/usr/bin/tail", argv);
