#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#include "mybank.h"

#define BKFILENAME  "bkdatafile"
typedef Transaction bktrans;
MAKE_CUSTOM_XVECTOR(bktrans)
typedef Account bkacc;
MAKE_CUSTOM_XVECTOR(bkacc)


// ---
Bank_t* open_bank(){
    Bank_t *bk = calloc(1, sizeof(Bank_t));
    if(bk == NULL){
        perror("calloc()");
        exit(EXIT_FAILURE);
    }
    static const char fname[] = BKFILENAME;
    bk->db = NULL;
    bk->dbfile = fname;
    bk->accounts = NULL;

    return bk;
}


int load_bank_data(Bank_t *bk){return 0;}
int save_bank_data(Bank_t *bk){return 0;}
int close_bank(Bank_t *bk){return 0;}

//Account create_account(Bank_t *bk){}
Account* account_login(Bank_t *bk){return 0;}
Account* account_update(Bank_t *bk){return 0;}

void print_acount_transactions(Account *acnt){}
double get_account_balance(Account *acnt){return 0.;}
int add_fund(Account *acnt, double fund){return 0;}
int withdraw_fund(Account *acnt, double fund){return 0;}
int transfer_fund(Account *from, Account *to, double fund){return 0;}
