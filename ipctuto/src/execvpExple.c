#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>

int main(){
    int pid, status;
    char *buff[2];

    if((pid=fork()) == -1){
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if(pid != 0){ // parent
        printf("I am the parent process %d\n", getpid());
        if(wait(&status) != pid){ // check if child returns
            perror("wait");
            exit(EXIT_FAILURE);
        }

        printf("Child process terminated with exit code %d\n", status >> 8);
    }else{
        buff[0] = (char*)malloc(12);
        strcpy(buff[0], "date");
        printf("%s\n", buff[0]);
        buff[1] = NULL;

        printf("I am the child process %d ", getpid());
        printf("and will be replaced with 'date'\n");
        execvp("date", buff);
        exit(1);
    }

    return EXIT_SUCCESS; // never reached
}
