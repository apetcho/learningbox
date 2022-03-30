#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/wait.h>


#define SENTINEL    -1

int main(){
    pid_t pid;
    int fd=SENTINEL;

    puts("About to run who info a file (in a strang way!)\n");
    if((pid=fork()) == SENTINEL){
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if(pid==0){ // child
        close(1);
        fd = creat("userlist", 0644); // should get 1 as fd !!!
        // output to userlist because stdout is closed
        execlp("who", "who", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    if(pid != 0){ // parent
        wait(NULL);
        puts("Done running who - results in file \"userlist\"");
    }

    return EXIT_SUCCESS;
}
