#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<errno.h>

#define MSGSIZE     65

char *fifo = "myfifo";

//
int main(int argc, char **argv){
    int fd;
    int i;
    int nwrite;
    char msgbuf[MSGSIZE+1];

    if(argc < 2){
        printf("Usage: %s ...\n", argv[0]);
        exit(EXIT_SUCCESS);
    }
    if((fd=open(fifo, O_WRONLY|O_NONBLOCK)) < 0){
        perror("fifo open error");
        exit(EXIT_FAILURE);
    }

    for(i=1; i < argc; i++){
        if(strlen(argv[i]) > MSGSIZE){
            printf(
                "Message with Prefix %*.s Too long - Ignored\n", 10, argv[i]);
            fflush(stdout);
            continue;
        }
        strcpy(msgbuf, argv[i]);
        if((nwrite=write(fd, msgbuf, MSGSIZE+1))==-1){
            perror("Error in Writing");
            exit(2);
        }
    }

    return EXIT_SUCCESS;
}
