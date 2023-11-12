#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<signal.h>

// -*-
void handle_interrupt(int sig);
// -*-
void prompt();
void show(int account, const char* name, double balance);
void readata(int *account, char *name, double *balance);
// -*-

// -*-------------------------*-
// -*- M A I N   D R I V E R -*-
// -*-------------------------*-
int main(int argc, char **argv){
    signal(SIGINT, handle_interrupt);
    signal(SIGKILL, handle_interrupt);
    signal(SIGTERM, handle_interrupt);
    FILE *fp = NULL;
    char *filename = NULL;
    if(argc > 1){
        filename = argv[1];
    }else{
        filename = "account.txt";
    }

    fp = fopen(filename, "r");
    if(fp == NULL){
        fprintf(stderr, "Error opening file '%s'\n", filename);
    }else{
        // puts("Enter the account, name, and balance.");
        // puts("Enter EOF to end input.");
        // prompt();
        int account = 0;
        size_t len = 30;
        char *name = calloc(len, sizeof(char));
        double balance = 0.0;
        memset(name, 0, len);
        printf("%-10s%-13s%s\n", "Account", "Name", "Balance");
        // readata(&account, name, &balance);
        fscanf(fp, "%d%29s%lf", &account, name, &balance);
        while(!feof(fp)){
            // show(account, name, balance);
            // fprintf(fp, "%d %s %.2lf\n", account, name, balance);
            // prompt();
            // memset(name, 0, len);
            // readata(&account, name, &balance);
            printf("%-10d%-13s%7.2lf\n", account, name, balance);
            fscanf(fp, "%d%29s%lf", &account, name, &balance);
        }
        free(name);
        fclose(fp);
    }

    return 0;
}

// -*-
void prompt(){
    printf(">> ");
}

// -*-
void show(int account, const char* name, double balance){
    printf("(%d, \"%s\", %.2lf)\n", account, name, balance);
}

// -*-
void readata(int *account, char *name, double *balance){
    char buffer[80];
    memset(buffer, '\0', sizeof(buffer));
    fgets(buffer, sizeof(buffer), stdin);
    const char *sep = " ,";
    char *next = NULL;
    char *data = NULL;

    data = strtok_r(buffer, sep, &next);
    *account = atoi(data);
    data = strtok_r(NULL, sep, &next);
    strncpy(name, data, 30);
    data = strtok_r(NULL, sep, &next);
    *balance = strtod(data, NULL);
}

// -*-
void handle_interrupt(int sig){
    if(sig==SIGINT || sig==SIGKILL || sig==SIGTERM){
        exit(EXIT_SUCCESS);
    }
}