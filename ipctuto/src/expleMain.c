#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>

#define READ    0
#define WRITE   1


int main(int argc, char **argv){
    int fd1[2];
    int fd2[2];
    int filedesc1 = -1;
    char myinputparam[20];
    pid_t pid;

    /* create a number of file(s)/pipe(s)/etc*/
    if((filedesc1=open("MytestFile", O_WRONLY|O_CREAT, 0666)) == -1){
        perror("file creation");
        exit(EXIT_FAILURE);
    }
    if(pipe(fd1) == -1){
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    if(pipe(fd2)==-1){
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    if((pid=fork())==-1){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if(pid != 0){ // parent process - closes off everything
        close(filedesc1);
        close(fd1[READ]);
        close(fd1[WRITE]);
        close(fd2[READ]);
        close(fd2[WRITE]);
        if(wait(NULL) != pid){
            perror("Waiting for child\n");
            exit(EXIT_FAILURE);
        }
    }
    else{
        printf("filedesc1=%d\n", filedesc1);
        printf("fd1[READ]=%d, fd1[WRITE]=%d\n", fd1[READ], fd1[WRITE]);
        printf("fd2[READ]=%d, fd2[WRITE]=%d\n", fd2[READ], fd2[WRITE]);
        dup2(fd2[WRITE], 11);
        execlp(argv[1], argv[1], "11", NULL);
        perror("execlp");
    }

    return EXIT_SUCCESS;
}
