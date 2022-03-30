#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>


#define MSGSIZE 32


char *msg1 = "Guten Tag! #1";
char *msg2 = "Hello World! #2";
char *msg3 = "Bonjour le monde! #3";


int main(){
    char inbuf[MSGSIZE];
    int p[2], i=0, rsize=0;
    pid_t pid;

    if(pipe(p) == -1){
        perror("pipe call");
        exit(EXIT_FAILURE);
    }

    switch(pid=fork()){
    case -1:
        perror("fork call");
        exit(2);
    case 0: // child process
        close(p[0]); // child process will only write.
        write(p[1], msg1, MSGSIZE);
        write(p[1], msg2, MSGSIZE);
        write(p[1], msg3, MSGSIZE);
        break;
    default: // parent process
        close(p[1]); // parent will only read
        for(i=0; i < 3; i++){
            rsize = read(p[0], inbuf, MSGSIZE);
            printf("%.*s", rsize, inbuf);
        }
        wait(NULL);
    }

    putchar('\n');

    return EXIT_SUCCESS;
}
