#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>

int main(){
    pid_t childpid;

    childpid = fork();
    if(childpid == -1){
        perror("Faild to fork");
        exit(EXIT_FAILURE);
    }

    if(childpid == 0){
        printf("I am the child process with ID: %lu\n", (long)getpid());
    }else{
        printf("I am the parent process with ID: %lu\n", (long)getpid());
    }
}
