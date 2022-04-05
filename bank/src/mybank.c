#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<assert.h>

#include "mybank.h"

#define BKFILENAME  "bkdatafile"
#define BKBONUS     25.0
#define BKACCLEN    10

#define CHECK_POINTER(ptr, funcname)    \
    do{                                 \
        if(!(ptr)){                     \
            perror((funcname));         \
            return NULL;                \
        }                               \
    }while(0)

#define SET_ACCOUNT_FIELD(field, value, funname)        \
    do{                                                 \
        size_t len = strlen(value) + 1;                 \
        (field) = (char*)malloc(sizeof(char)*(len));    \
        CHECK_POINTER(field, funname);                  \
        snprintf((field), len, "%s", (value));          \
        (field)[len] = '\0';                            \
    }while(0)


typedef Transaction bktrans;
MAKE_CUSTOM_XVECTOR(bktrans)
typedef Account bkacc;
MAKE_CUSTOM_XVECTOR(bkacc)


// ---
Bank_t* open_bank(){
    Bank_t *bk = calloc(1, sizeof(Bank_t));
    CHECK_POINTER(bk, "open_bank()");
    static const char fname[] = BKFILENAME;
    bk->db = NULL;
    bk->dbfile = fname;
    bk->accounts = NULL;
    return bk;
}


int load_bank_data(Bank_t *bk){return 0;}
int save_bank_data(Bank_t *bk){return 0;}
int close_bank(Bank_t *bk){return 0;}

// ---
static void generate_accno(char acntbuf[]){
    srand((unsigned)time(NULL));
    int num[BKACCLEN];
    for(int i=0; i < BKACCLEN; i++){
        num[i] = rand() % 10;
    }
    size_t len = 2*BKACCLEN * 5;
    snprintf(
        acntbuf, len, "%d%d%d%d %d%d%d %d%d%d",
        num[0], num[1], num[2], num[3],
        num[4], num[5], num[6],
        num[7], num[8], num[9]
    );
}

Account* create_account(
    const char *fname, const char *lname, const char *email,
    const char *phone, const char *pword
){
    Account *acnt = calloc(1, sizeof(Account));
    CHECK_POINTER(acnt, "create_account()");
    SET_ACCOUNT_FIELD(acnt->fname, fname, "create_account()");
    SET_ACCOUNT_FIELD(acnt->lname, lname, "create_account()");
    SET_ACCOUNT_FIELD(acnt->email, email, "create_account()");
    SET_ACCOUNT_FIELD(acnt->phone, phone, "create_account()");
    SET_ACCOUNT_FIELD(acnt->pword, pword, "create_acounte()");

    acnt->balance = BKBONUS;
    acnt->created = time(NULL);
    acnt->transactions = NULL;
    static int const acnlen = 2*BKACCLEN+5;
    acnt->accno = (char*)malloc(sizeof(char)*(acnlen));
    memset(acnt->accno, '\0', acnlen);
    generate_accno(acnt->accno);

    return acnt;
}

// ----
Account* account_login(Bank_t *bk){return 0;}
Account* account_update(Bank_t *bk){return 0;}

void print_acount_transactions(Account *acnt){}
double get_account_balance(Account *acnt){return 0.;}
int add_fund(Account *acnt, double fund){return 0;}
int withdraw_fund(Account *acnt, double fund){return 0;}
int transfer_fund(Account *from, Account *to, double fund){return 0;}
