#include<stdlib.h>
#include<unistd.h>
#include<limits.h>
#include<signal.h>
#include<stdio.h>

int count = 0;
void alarm_action(int);

int main(){
    int p[2];
    int pipe_size;
    char c = 'x';

    static struct sigaction action;

    // set up the signal handler
    action.sa_handler = alarm_action;
    sigfillset(&(action.sa_mask));

    if(pipe(p) == -1){
        perror("pipe call");
        exit(EXIT_FAILURE);
    }

    pipe_size = fpathconf(p[0], _PC_PIPE_BUF);
    printf("Maximum size of (atomic) write to pipe: %d bytes\n", pipe_size);
    printf("The respective POSIX value %d\n", _POSIX_PIPE_BUF);

    sigaction(SIGALRM, &action, NULL);

    while(1){
        alarm(20);
        write(p[1], &c, 1);
        alarm(0);
        if(++count % 4096 == 0){
            printf("%d characters in pipe\n", count);
        }
    }

    return EXIT_SUCCESS;
}

void alarm_action(int signo){
    printf("write blocked after %d characters \n", count);
    exit(EXIT_SUCCESS);
}
