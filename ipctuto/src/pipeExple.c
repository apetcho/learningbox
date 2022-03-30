#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

#define MSGSIZE 32


char *msg1 = "Guten Tag! #1";
char *msg2 = "Hello World! #2";
char *msg3 = "Bonjour le monde! #3";


int main(){
    char inbuf[MSGSIZE];
    int p[2];
    int i=0, rsize=0;
    pid_t pid;

    if(pipe(p) == -1){
        perror("pipe call");
        exit(EXIT_FAILURE);
    }

    write(p[1], msg1, MSGSIZE);
    write(p[1], msg2, MSGSIZE);
    write(p[1], msg3, MSGSIZE);

    for(i=0; i < 3; i++){
        rsize = read(p[0], inbuf, MSGSIZE);
        printf("[%d:%d] -> %s\n", i,  rsize, inbuf);
    }

    return EXIT_SUCCESS;
}
