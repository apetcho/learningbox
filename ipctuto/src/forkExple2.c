#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
    pid_t childpid;
    pid_t mypid;

    mypid = getpid();
    childpid = fork();
    if(childpid==-1){
        perror("Failed to fork");
        exit(EXIT_FAILURE);
    }

    if(childpid == 0){
        printf("I am the child process with ID: %lu -- %lu\n",
            (long)getpid(), (long)mypid);
    }else{
        printf("I am the parent process with ID: %lu -- %lu\n",
            (long)getpid(), (long)mypid);
    }

    return 0;
}
