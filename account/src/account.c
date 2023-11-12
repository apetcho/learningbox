#include<stdbool.h>
#include<stdio.h>

typedef enum {
    ZERO_BALANCE = 1,
    CREDIT_BALANCE,
    DEBIT_BLANCE,
    END
} Option;

typedef struct {
    int account;
    char lname[15];
    char fname[10];
    double balance;
}AccountData;


// -*-------------------------*-
// -*- M A I N   D R I V E R -*-
// -*-------------------------*-
int main(int argc, char **argv){
    FILE *fp = NULL;
    char* filename = NULL;
    if(argc > 1){
        filename = argv[1];
    }else{
        filename = "accounts.dat";
    }

    if((fp=fopen(filename, "wb"))==NULL){
        fprintf(stderr, "Unable to open file: \"%s\"\n", filename);
    }else{
        AccountData data = {
            .account=0,
            .lname="",
            .fname="",
            .balance=0.0,
        };
        // output 100 blank records to file
        for(int i=1; i <= 100; ++i){
            fwrite(&data, sizeof(data), 1, fp);
        }
        fclose(fp);
    }

    return 0;
}