#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<errno.h>
#include<tgmath.h>
#include<float.h>
#include<signal.h>

#define CALCBUFLEN  80
#define SENTINEL    -100000.0

char *input = "calcInput";
char *result = "calcResult";

void calcQuadratic(double a, double b, double c, double *x, double *y){
    double delta = b*b - 4.0*a*c;
    printf("calc> delta = %lf\n", delta);
    //double x[2], y[2];

    if(delta < 0.0){
        double complex z = delta + 0.0*I;
        double complex xs = sqrt(z);
        double complex z1 = (-b - xs)/(2.0*a);
        double complex z2 = (-b + xs)/(2.0*a);
        x[0] = creal(z1);
        x[1] = creal(z2);
        y[0] = cimag(z1);
        y[1] = cimag(z2);
        return;
    }else if(delta = 0.0){
        double xs = -b/(2.0*a);
        x[0] = xs;
        y[0] = xs;
        x[1] = SENTINEL;
        y[1] = SENTINEL;
        return;
    }else{
        double xs = sqrt(delta);
        x[0] = (-b - xs)/(2.0*a);
        y[0] = (-b + xs)/(2.0*a);
        x[1] = SENTINEL;
        y[1] = SENTINEL;
        return;
    }
}

void handler(int signo){
    if(signo == SIGINT || signo == SIGKILL){
        puts("CalcServer is quitting ....");
        sleep(5);
        puts("--------- GOOD BYE --------");
        exit(EXIT_SUCCESS);
    }
}

void header(){
    puts("--------------------------------------------------");
    puts("  WELCOME TO QUADRATIC EQUATION CALULATOR SERVER  ");
    puts("--------------------------------------------------");
    puts("");
}


// ----
int main(int argc, char **argv){
    signal(SIGINT, handler);
    signal(SIGKILL, handler);
    header();
    int ifd, ofd;
    int reader, writer;
    char inputbuf[CALCBUFLEN+1];
    char outputbuf[CALCBUFLEN+1];
    double a, b, c; //, x[2], y[2];
    double *x = calloc(2, sizeof(double));
    double *y = calloc(2, sizeof(double));
    int i = 0;

    if(argc > 2){
        printf("Usage: %s & \n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if(mkfifo(input, 0666) == -1){
        if(errno != EEXIST){
            perror("server: mkfifo");
            exit(EXIT_FAILURE);
        }
    }
    if(mkfifo(result, 0666) == -1){
        if(errno != EEXIST){
            perror("server: mkfifo");
            exit(EXIT_FAILURE);
        }
    }
    if((reader=open(input, O_RDONLY)) < 0){
        perror("fifo open problem");
        exit(20);
    }
    if((writer=open(result, O_WRONLY|O_NONBLOCK)) < 0){
        perror("fifo open problem");
        exit(21);
    }
    
    for(;;){
        
        if(read(reader, inputbuf, CALCBUFLEN+1) < 0){
            perror("problem in reading");
            exit(22);
        }
        sscanf(inputbuf, "%lf %lf %lf", &a, &b, &c);
        printf("[%03d]> Equation = %.1lfx^2 + %.1lfx + %.lf\n",
            ++i, a, b, c);
        
        if(a == 0.0){
            snprintf(outputbuf, CALCBUFLEN,
             "Result> Error. This is not a quadratic equation");
        }
        calcQuadratic(a, b, c, x, y);
        if(x[1]==SENTINEL || y[1]==SENTINEL){
            snprintf(outputbuf, CALCBUFLEN,
                "Result> x1 = %.1lf, x2 = %.1lf", x[0], y[0]);
        }else {
            snprintf(outputbuf, CALCBUFLEN,
                "Result> z1 = %.1lf + %.1lfi, z2 = %.1lf + %.1lf",
                x[0], y[0], x[1], y[1]);
        }
        
        
        if(write(writer, outputbuf, CALCBUFLEN) < 0){
            perror("problem in writing");
            exit(23);
        }
        
        fflush(stdout);
    }

    free(x);
    free(y);

    return EXIT_SUCCESS;
}
