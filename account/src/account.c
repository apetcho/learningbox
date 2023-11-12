#include<stdbool.h>
#include<stdio.h>

typedef enum {
    ZERO_BALANCE = 1,
    CREDIT_BALANCE,
    DEBIT_BLANCE,
    END
} Option;

// -*-
bool showable(Option opt, double balance);

// -*-------------------------*-
// -*- M A I N   D R I V E R -*-
// -*-------------------------*-
int main(int argc, char **argv){
    FILE *fp = NULL;
    char *filename = NULL;
    if(argc > 1){
        filename = argv[1];
    }else{
        filename = "account.txt";
    }
    if((fp=fopen(filename, "r"))==NULL){
        fprintf(stderr, "Unable to open file: '%s'\n", filename);
    }else{
        const char *menu = 
            "Enter request\n"
            " 1 - List accounts with zero balances\n"
            " 2 - List accounts with credit balances\n"
            " 3 - List accounts with debit balances\n"
            " 4 - End of runt\n";
        printf("%s", menu);
        int request = 0;
        scanf("%d", &request);

        // - display records
        while(request != END){
            switch(request){
            case ZERO_BALANCE:
                puts("\nAccounts with zero balances:");
                break;
            case CREDIT_BALANCE:
                puts("\nAccounts with credit balances:");
                break;
            case DEBIT_BLANCE:
                puts("\nAccounts with debit balances:");
                break;
            }
            // -
            int account = 0;
            char name[30] = "";
            double balance = 0.0;

            // read account, name and balance from file
            fscanf(fp, "%d%29s%lf", &account, name, &balance);
            // read file contents (until eof)
            while(!feof(fp)){
                // output only if balance is 0
                if(showable(request, balance)){
                    printf("%-10d%-13s%7.2lf\n", account, name, balance);
                }
                // read account, name and balance from file
                fscanf(fp, "%d%29s%lf", &account, name, &balance);
            }
            // return fp to beginning of file
            rewind(fp);
            printf("\n>> ");
            scanf("%d", &request);
        }
        puts("End of run.");
        fclose(fp);
    }
    
    return 0;
}

// -*-
bool showable(Option opt, double balance){
    if((opt==ZERO_BALANCE) && (balance==0)){
        return true;
    }
    if((opt==CREDIT_BALANCE) && (balance < 0)){
        return true;
    }
    if((opt==DEBIT_BLANCE) && (balance > 0)){
        return true;
    }
    return false;
}