#include<stdbool.h>
#include<stdio.h>

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

    if((fp=fopen(filename, "rb+"))==NULL){
        fprintf(stderr, "Unable to open file: \"%s\"\n", filename);
    }else{
        AccountData data = {
            .account=0,
            .lname="",
            .fname="",
            .balance=0.0,
        };
        printf("%s", "Enter account number (1 to 100, 0 to end input): ");
        scanf("%d", &data.account);

        while(data.account!=0){
            printf("%s", "Enter lastname, firstname, balance: ");
            fscanf(stdin, "%14s%9s%lf", data.lname, data.fname, &data.balance);
            // seek position in file to user-specified record
            fseek(fp, (data.account - 1)*sizeof(data), SEEK_SET);
            // write user-specified information in file
            fwrite(&data, sizeof(data), 1, fp);
            // enable user to input another account
            printf("%s", "Enter account number: ");
            scanf("%d", &data.account);
        }
        fclose(fp);
    }

    return 0;
}