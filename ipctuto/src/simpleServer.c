#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<errno.h>

#define MSGSIZE 65

char *fifo = "myfifo";

int main(int argc, char **argv){
    int fd;
    int i;
    int nwrite;
    char msgbuf[MSGSIZE+1];

    if(argc > 2){
        printf("Usage: %s &\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if(mkfifo(fifo, 0666) == -1){
        if(errno != EEXIST){
            perror("server: mkfifo");
            exit(6);
        }
    }
    if((fd=open(fifo, O_RDWR)) < 0){
        perror("fifo open problem");
        exit(3);
    }
    /* server mainloop */
    for(;;){
        if(read(fd, msgbuf, MSGSIZE+1) < 0){
            perror("problem in reading");
            exit(5);
        }
        printf("\nMessage Received: %s\n", msgbuf);
        fflush(stdout);
    }

    return EXIT_SUCCESS;
}
