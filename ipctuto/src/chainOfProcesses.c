#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>


int main(int argc, char **argv){
    pid_t childpid = 0;
    int i, n;
    if(argc != 2){
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    n = atoi(argv[1]);
    for(i=1; i < n; i++){
        if((childpid=fork()) > 0){
            break; /* only the child carries on */
        }
    }
    printf("i:%d process ID:%ld parent ID:%ld child ID:%ld\n",
        i, (long)getpid(), (long)getppid(), (long)childpid);

    return 0;
}
