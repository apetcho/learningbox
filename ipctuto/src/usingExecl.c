#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
    int retval;

    printf("I am process %lu and I will execude an 'ls -l .;\n'",
        (long)getpid());

    retval = execl("/bin/ls", "ls", "-l", ".", NULL);
    if(retval == -1){ // do we ever get here?
        perror("execl");
    }

    return EXIT_SUCCESS;  // not reached if operation when successfully.
}
