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

    if((fp=fopen(filename, "rb"))==NULL){
        fprintf(stderr, "Unable to open file: \"%s\"\n", filename);
    }else{
        printf("%-6s%-16s%-11s%10s\n", "Acct", "Last Name", "First Name", "Balance");
        // read all records from file (until eof)
        while(!feof(fp)){
            AccountData data = {
                .account=0, .lname="", .fname="", .balance=0.0,
            };
            size_t result = fread(&data, sizeof(data), 1, fp);
            if(result !=0 && data.account != 0){
                printf(
                    "%-6d%-16s%-11s%10.2lf\n",
                    data.account, data.lname, data.fname, data.balance
                );
            }
        }
        
        fclose(fp);
    }

    return 0;
}