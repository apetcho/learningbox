#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<errno.h>
#include<signal.h>
#include<ctype.h>

#define CALCBUFLEN  80

char *input = "calcInput";
char *result = "calcResult";

void handler(int signo){
    if(signo == SIGINT || signo == SIGKILL){
        puts("CalcClient is quitting ....");
        sleep(1);
        puts("--------- GOOD BYE --------");
        exit(EXIT_SUCCESS);
    }
}

void usage(const char *name){
    printf("\t%s [-h]\n", name);
    puts("Launch the application.\n");
    puts("Options:");
    puts("\t-h     Display tthis message\n");
    return;
}


// ---
int main(int argc, char **argv){
    int reader, writer;
    char inputbuf[CALCBUFLEN+1];
    char outputbuf[CALCBUFLEN+1];
    double a, b, c;

    if(argc == 2 && strcmp(argv[1], "-h") == 0){
        usage(argv[0]);
        return EXIT_SUCCESS;
    }else if (argc > 2){
        perror("calcClient: invalid command\n");
        return EXIT_FAILURE;
    }
    if((writer=open(input, O_WRONLY|O_NONBLOCK))< 0){
        perror("fifo open error");
        exit(31);
    }
    if((reader=open(result, O_RDONLY)) < 0){
        perror("fifo open error.");
        exit(32);
    }
    int LEN = 20;
    char buf[LEN+1];
    puts("Enter 'q' to quit the session.");
    for(;;){
        printf("a> ");
        while((fgets(buf, LEN, stdin)) == NULL && ferror(stdin)){ break;}
        if(buf[0] == 'q'){
            break;
        }
        sscanf(buf, "%lf", &a);
        printf("b> ");
        while((fgets(buf, LEN, stdin)) == NULL && ferror(stdin)){ break;}
        if(buf[0] == 'q'){
            break;
        }
        sscanf(buf, "%lf", &b);
        printf("c> ");
        while((fgets(buf, LEN, stdin)) == NULL && ferror(stdin)){ break;}
        if(buf[0] == 'q'){
            break;
        }
        sscanf(buf, "%lf", &c);
        snprintf(inputbuf, CALCBUFLEN, "%lf %lf %lf", a, b, c);
        
        if((write(writer, inputbuf, CALCBUFLEN+1)) == -1){
            perror("Error in writing");
            exit(33);
        }
        
        if((read(reader, outputbuf, CALCBUFLEN)) == -1){
            perror("Error in reading");
            exit(34);
        }
        
        puts(outputbuf);
        fflush(stdout);
        puts("Enter 'q' to quit the session.");
    }

    return EXIT_SUCCESS;
}
