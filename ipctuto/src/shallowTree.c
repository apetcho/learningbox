#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc, char **argv){
    pid_t childpid;
    pid_t mypid;
    int i, n;

    if(argc != 2){
        printf("Usage: %s <number-of-processes>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    n = atoi(argv[1]);
    for(i=0; i < n; i++){
        if((childpid=fork()) <= 0){ break;}
    }
    printf("i: %d process ID: %ld parent ID: %ld child ID: %ld\n", 
        i, (long)getpid(), (long)getppid(), (long)childpid);

    return 0;
}
