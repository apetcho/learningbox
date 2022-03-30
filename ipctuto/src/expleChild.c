#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

#define READ    0
#define WRITE   1


int main(int argc, char **argv){
    char message[] = "Hello there!";
    /* although the program is NOT aware of the logical names it can */
    /* access/manipulate the file descriptor !!! */
    puts("Operating after the execlp invocation!");
    if(write(3, message, strlen(message)+1)==-1){
        perror("Write to 3-file\n");
    }else{
        puts("Write to file with file descriptor 3 successed");
    }

    if(write(5, message, strlen(message)+1)==-1){
        perror("Write to 5-pipe\n");
    }else{
        puts("Write to pipe with file descriptor 5 successed");
    }
    if(write(7, message, strlen(message)+1)==-1){
        perror("Write to 7-pipe\n");
    }else{
        puts("Write to pipe file with file descriptor 7 successed");
    }
    if(write(11, message, strlen(message)+1)==-1){
        perror("Write to 11-dup2\n");
    }else{
        puts("Write to duped file with file descriptor 11 successed");
    }
    if(write(13, message, strlen(message)+1)==-1){
        perror("Write to 13-invalid\n");
    }else{
        puts("Write to file invalid file descriptor 13 not feasible");
    }

    return 1;
}
