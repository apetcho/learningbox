#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#define READ    0
#define WRITE   1


int main(int argc, char **argv){
    pid_t pid;
    int fd[2], bytes;

    if(pipe(fd) == -1){
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    if((pid = fork()) == -1){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if(pid != 0){ // parent and writer
        close(fd[READ]);
        dup2(fd[WRITE], 1);
        close(fd[WRITE]);
        execlp(argv[1], argv[1], NULL);
        perror("execlp");
    }else{
        close(fd[WRITE]);
        dup2(fd[READ], 0);
        close(fd[READ]);
        execlp(argv[2], argv[2], NULL);
    }
}
