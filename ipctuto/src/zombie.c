#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>


int main(){
    pid_t pid;
    pid = fork();

    if(pid == -1){
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if(pid != 0){
        while(1){sleep(60);}
    }else{ exit(37);}
}
