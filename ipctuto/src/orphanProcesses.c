#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(){
    pid_t pid;

    printf("Original process: PID = %d, PPID = %d\n", getpid(), getppid());
    pid = fork();
    if(pid == -1){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if(pid != 0){
        printf("Parent process: PID = %d, PPID = %d, CPID = %d\n",
            getpid(), getppid(), pid);
    }else{
        sleep(2);
        printf("Child process: PID = %d, PPID = %d \n", getpid(), getppid());
    }

    printf("Process with PID = %d terminates \n", getppid());

    return 0;
}
