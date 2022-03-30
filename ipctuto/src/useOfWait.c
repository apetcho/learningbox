#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>


int main(){
    pid_t pid;
    int status;
    int exitStatus;

    if((pid = fork())<0){
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if(pid == 0){
        sleep(4);
        exit(5); /* exit with non-zero value */
    }else{
        printf("Hello I am in parent process %d with child %d\n",
            getpid(), pid);
    }

    if((pid = wait(&status)) == -1){
        perror("wait failed");
        exit(2);
    }
    if(WIFEXITED(status)){
        exitStatus = WEXITSTATUS(status);
        printf("exit status from %d was %d\n", pid, exitStatus);
    }

    return EXIT_SUCCESS;
}
