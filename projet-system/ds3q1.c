#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int pipe3(char *cmd1 , char *arg1, char *cmd2, char *arg2, char *cmd3, char *arg3)
{  
  int pid1, pid2, pid3, p1[2], p2[2];
  
  // création de deux pipes (hérités par les fils)
  if(pipe(p1) == -1) 
    { perror("pipe1"); exit(EXIT_FAILURE); }  
  
  if(pipe(p2) == -1) 
    { perror("pipe2"); exit(EXIT_FAILURE); }  


  // création du fils1
  if((pid1 = fork()) == -1) 
    { perror("fils1"); exit(EXIT_FAILURE); }

  // le fils1
  if(pid1 == 0) { 
    dup2(p1[1],1); 
    close(p1[0]); close(p1[1]);  
    close(p2[0]); close(p2[1]);  
    execlp("cmd1","cmd1","arg1",NULL);
    // read(0, ...) + write(p1[1], ...)
  }
    
  // création du fils2
  if((pid2 = fork()) == -1) 
    { perror("fils2"); exit(EXIT_FAILURE); }
  
  // le fils2
  if(pid2 == 0) { 
    dup2(p1[0],0); 
    dup2(p2[1],1); 
    close(p1[0]); close(p1[1]);  
    close(p2[0]); close(p2[1]);  
    execlp("cmd2","cmd2","arg2",NULL);
    // read(p1[0], ...) + write(p2[1], ...)
  }

  // création du fils3
  if((pid3 = fork()) == -1) 
    { perror("fils3"); exit(EXIT_FAILURE); }
  
  
  // le fils3
  if(pid3 == 0) { 
    dup2(p2[0],0); 
    close(p1[0]); close(p1[1]);
    close(p2[0]); close(p2[1]);
    execlp("cmd3","cmd3","arg3",NULL);
    // read(p2[0], ...) + write(1, ...)
  }
  
  // ne pas oublier les fermetures pour le père aussi !
  close(p1[0]); close(p1[1]);  
  close(p2[0]); close(p2[1]);  

  // attente des fils...
  wait(NULL); wait(NULL); wait(NULL); 
  
  return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
  pipe3(argv[1],argv[2],argv[3],argv[4],argv[5],argv[6]);
}
