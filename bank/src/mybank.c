#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#include "mybank.h"

#define BKFILENAME  "bkdatafile"

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


int load_bank_data(Bank_t *bk){}
int save_bank_data(Bank_t *bk){}
int close_bank(Bank_t *bk){}

Account create_account(Bank_t *bk){}
Account* account_login(Bank_t *bk){}
Account* account_update(Bank_t *bk){}

void print_acount_transactions(Account *acnt){}
double get_account_balance(Account *acnt){}
int add_fund(Account *acnt, double fund){}
int withdraw_fund(Account *acnt, double fund){}
int transfer_fund(Account *from, Account *to, double fund){}
