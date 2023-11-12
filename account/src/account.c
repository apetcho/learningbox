#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<signal.h>
#include<math.h>
#include<time.h>

#include "swzrandom.h"

#define PROPERNAMES         "/usr/share/dict/propernames"
#define ACCOUNT_BINFILE     "accounts.dat"
#define ACCOUNT_TXTFILE     "accounts.txt"
#define ACCOUNT_MAX         100
#define MAX_NAMES           300
#define NAMELEN             15

#define PRINTLN(stream, data)                                   \
    fprintf(                                                    \
        stream, "%-6d%-16s%-16s%10.lf\n",                       \
        data.account, data.lname, data.fname, data.balance      \
    )

// -*-
static char* Names[MAX_NAMES];
// -*-
typedef struct {
    int account;
    char lname[NAMELEN];
    char fname[NAMELEN];
    double balance;
}AccountData;

enum Option {
    OPT_WRITE = 1,
    OPT_UPDATE,
    OPT_CREATE,
    OPT_DELETE,
    OPT_DISPLAY,
    OPT_END
};

// -*-
void handle_interrupt(int sig){
    if(sig==SIGINT){
        puts("");
        exit(EXIT_SUCCESS);
    }
}
//! @todo -
int read_int(){
    char buffer[64];
    fgets(buffer, sizeof(buffer), stdin);
    int result = atoi(buffer);
    return result;
}

// -
int random_index(){
    return swzrng_randInt() % MAX_NAMES;
}

// -
double random_balance(){
    double x = (double)(swzrng_randInt() % 10000) + swzrng_randFloat();
    double a = (double)(swzrng_randInt() % 10) * cos((swzrng_randFloat())*M_PI);
    //double b = (double)(swzrng_randInt() % 10)* sin((swzrng_randFloat())*M_PI);
    double balance = a*x + swzrng_randInt() % 30;
    return balance;
}


double random_transaction(){
    double r = (double)swzrng_randInt() / swzrng_max();
    double val = fabs(random_balance());
    double x = -0.5 + (double)(swzrng_randInt() / swzrng_max());
    double rc = cos(r*M_PI) > 0 ? 1.0 : -1.0;
    return log(val) * exp(x) * rc;
}

// -
void generate_random_names();
void make_random_data();
// -*- prototypes
enum Option get_choice(void);
void create_text_file(FILE *fp);
void display(FILE *fp);
void update_record(FILE *fp);
void create_new_record(FILE *fp);
void delete_record(FILE *fp);
// -*-
// static AccountData Accounts[ACCOUNT_MAX];

// -*-------------------------*-
// -*- M A I N   D R I V E R -*-
// -*-------------------------*-
int main(int argc, char **argv){
    signal(SIGINT, handle_interrupt);
    srand((unsigned int)time(NULL));
    generate_random_names();
    make_random_data();

    FILE *fp = NULL;
    char* filename = NULL;
    if(argc > 1){
        filename = argv[1];
    }else{
        filename = ACCOUNT_BINFILE;
    }

    if((fp=fopen(filename, "rb"))==NULL){
        fprintf(stderr, "Unable to open file: \"%s\"\n", filename);
    }else{
        int choice = 0;
        while((choice=get_choice())!=OPT_END){
            switch(choice){
            case OPT_WRITE:
                create_text_file(fp);
                break;
            case OPT_UPDATE:
                update_record(fp);
                break;
            case OPT_CREATE:
                create_new_record(fp);
                break;
            case OPT_DISPLAY:
                display(fp);
                break;
            case OPT_DELETE:
                delete_record(fp);
                break;
            default:
                fprintf(stderr, "Invalid choice\n");
                break;
            }
        }
        fclose(fp);
    }

    // -
    for(size_t i=0; i < MAX_NAMES; i++){
        free(Names[i]);
    }

    return 0;
}

// -
void generate_random_names(){
    FILE* fp = fopen(PROPERNAMES, "r");
    char buffer[15];
    if(fp==NULL){
        fprintf(stderr, "Error opening file: \"%s\"\n", PROPERNAMES);
        exit(EXIT_FAILURE);
    }
    size_t numlines = 1000;
    rewind(fp);
    size_t index = 0;
    static char names[1000][NAMELEN];
    int idx = 0;
    while(1){
        fgets(buffer, NAMELEN, fp);
        if(strlen(buffer) <= 5){ continue;}
        if(buffer[strlen(buffer)-1]=='\n'){
            buffer[strlen(buffer)-1] = '\0';
        }
        strncpy(names[idx++], buffer, NAMELEN);
        if(idx >= 1000){ break; }
    }
    while(index < MAX_NAMES){
        int pos = swzrng_randInt() % numlines + 1;
        Names[index] = calloc(NAMELEN, sizeof(char));
        strncpy(Names[index], names[pos], NAMELEN);
        index++;
    }
    fclose(fp);
}

// -
void create_text_file(FILE *fp){
    FILE *wfp = NULL;
    char *filename = ACCOUNT_TXTFILE;
    if((wfp = fopen(filename, "w"))==NULL){
        fprintf(stderr, "Error opening file: '%s'\n", filename);
    }else{
        rewind(fp);
        fprintf(
            wfp, "%-6s%-16s%-16s%10s\n",
            "Acct", "Last Name", "First Name", "Balance"
        );

        // copy all records from random-access file into text file
        while(!feof(fp)){
            // create account data with default information
            AccountData data = {
                .account=0, .lname="", .fname="", .balance=0.0
            };
            size_t rc = fread(&data, sizeof(data), 1, fp);
            if(rc != 0 && data.account != 0){
                PRINTLN(wfp, data);
            }
        }
        fclose(wfp);
    }
}

// -
void update_record(FILE *fp){
    printf("%s", "Enter account to update (1 - 100): ");
    int account = 0;
    // scanf("%d", &account);
    account = read_int();
    fseek(fp, (account-1)*sizeof(AccountData), SEEK_SET);
    AccountData data = {
        .account=0, .lname="", .fname="", .balance=0.0
    };
    fread(&data, sizeof(AccountData), 1, fp);
    if(data.account==0){
        printf("Account #%d has no information.\n", account);
    }else{
        PRINTLN(stdout, data);
        data.balance += random_transaction();
        PRINTLN(stdout, data);
        // move file pointer to correct record in file
        fseek(fp, (account-1)*sizeof(AccountData), SEEK_SET);
        // write updated record over old record in file
        fwrite(&data, sizeof(AccountData), 1, fp);
    }
}

// -
void display(FILE *fp){
    printf("%s", "Enter new account number (1 - 100): ");
    int account = read_int();
    AccountData data = {};
    fseek(fp, (account - 1)*sizeof(AccountData), SEEK_SET);
    fread(&data, sizeof(AccountData), 1, fp);
    PRINTLN(stdout, data);
}

// -
void create_new_record(FILE *fp){
    // - obtain number of account to create
    printf("%s", "Enter new account number (1 - 100): ");
    int account = 0;
    // scanf("%d", &account);
    account = read_int();
    // move file pointer to correcot record in file
    fseek(fp, (account-1)*sizeof(AccountData), SEEK_SET);
    // read record from file
    AccountData data = {
        .account=0, .lname="", .fname="", .balance=0.0
    };
    fread(&data, sizeof(AccountData), 1, fp);

    // display error if account already exists
    if(data.account!=0){
        fprintf(stderr, "Account #%d already contains information.\n", data.account);
    }else{
        // create record
        int idx = random_index();
        strncpy(data.lname, Names[idx], sizeof(data.lname));
        idx = random_index();
        strncpy(data.fname, Names[idx], sizeof(data.fname));
        data.balance = random_balance();
        data.account = account;

        fseek(fp, (data.account - 1)*sizeof(AccountData), SEEK_SET);
        fwrite(&data, sizeof(AccountData), 1, fp);
    }
}

// -*-
void delete_record(FILE *fp){
    printf("%s", "Enter account number to delete (1 - 100): ");
    int account = 0;
    // scanf("%d", &account);
    account = read_int();
    // move file pointer to correct record in file
    fseek(fp, (account - 1)*sizeof(AccountData), SEEK_SET);
    // read record from file
    AccountData data = {0};
    fread(&data, sizeof(AccountData), 1, fp);
    if(data.account == 0){
        fprintf(stderr, "Account %d does not exist.\n", account);
    }else{
        // delete record
        // move ...
        fseek(fp, (account-1)*sizeof(AccountData), SEEK_SET);
        AccountData bank = {.account=0, .lname="", .fname="", .balance=0.0};
        // replace existing record with blank record
        fwrite(&bank, sizeof(AccountData), 1, fp);
    }
}

// -*-
enum Option get_choice(void){
    char* choices =
        "1 - store a formatted text file of accounts called\n"
        "    \"accounts.txt\" for printing\n"
        "2 - update an account\n"
        "3 - add new account\n"
        "4 - delete an account\n"
        "5 - display\n"
        "6 - end program\n? ";
    
    puts("\nEnter your choice");
    printf("%s", choices);
    int opt = 0;
    // scanf("%d", &opt);
    opt = read_int();
    switch(opt){
    case 1:
        return OPT_WRITE;
    case 2:
        return OPT_UPDATE;
    case 3:
        return OPT_CREATE;
    case 4:
        return OPT_DELETE;
    case 5:
        return OPT_DISPLAY;
    case 6:
        return OPT_END;
    default:
        return OPT_WRITE;
    }
}

// -*-
void make_random_data(){
    puts("Making random data ...");
    char lname[NAMELEN];
    char fname[NAMELEN];
    double balance = 0;
    FILE *fp = fopen(ACCOUNT_BINFILE, "wb");
    if(fp == NULL){
        fprintf(stderr, "Unable to open file: %s\n", ACCOUNT_BINFILE);
    }else{
        AccountData data; // = {};
        for(int i=0; i < ACCOUNT_MAX; i++){
            strncpy(
                data.lname, Names[swzrng_randInt()%MAX_NAMES],
                sizeof(data.lname)
            );
            strncpy(
                data.fname, Names[swzrng_randInt()%MAX_NAMES],
                sizeof(data.fname)
            );
            data.account = (i+1);
            data.balance = 1000.0 * swzrng_randFloat();
            PRINTLN(stdout, data);
            fwrite(&data, sizeof(AccountData), 1, fp);
        }
        fclose(fp);
    }
}