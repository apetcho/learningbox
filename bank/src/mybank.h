#ifndef _MY_BANK_APP_H
#define _MY_BANK_APP_H

#include<time.h>
#include<ndbm.h>
#include "xvector.h"
#define BKBUFLEN 80

typedef enum BankEvent_t{
    BK_ERR_INSUFICIENT_FUND=-4,
    BK_ERR_LOGIN=-3,
    BK_UNKNOWN=-2,
    BK_FAILURE=-1,
    BK_SUCCESS=0,
    BK_REGISTER=1,      // register
    BK_LOGIN=2,         // login
    BK_OP_INQUIRE=10,   // inquire
    BK_OP_ADD_FUND=11,  // add
    BK_OP_WITHDRAW=12,  // withdraw
    BK_OP_TRANSFER=13,  // transfer
    BK_OP_UPDATE=14,    // update
    BK_UP_FNAME=20,     // update f
    BK_UP_LNAME=21,     // updade l
    BK_UP_EMAIL=22,     // update e
    BK_UP_PHONE=23,     // update p
    BP_UP_PASSORD=24    // update s
}BankEvent_t;

typedef struct Transaction{
    BankEvent_t type;       /* Transaction type */
    time_t when;            /* Time at which the transaction was made */
    char *info;             /* Name of the transaction type */
} Transaction;
typedef XVector_t TransList_t;

typedef struct Account {
    char *fname;                /* Account holder's first name */
    char *lname;                /* Account holder's last name */
    char *email;                /* Account holder's email */
    char *phone;                /* Account holder's phone number */
    char *accno;                /* Account holder's account number */          
    char *pword;                /* Account holder's password */
    time_t created;       /* Date of creation of this account */
    double balance;             /* Account's current balance */
    TransList_t *transactions;  /* Account transactions list */
} Account;

typedef XVector_t AccList_t;

typedef struct Bank_t {
    DBM *db;                    /* Pointer to bank database object */
    const char *dbfile;         /* Bank database filename */
    AccList_t *accounts;        /* Accounts opened at this bank */
} Bank_t;

/** Create a new empty bank object. Return a pointer to the bank object */
Bank_t* open_bank();

/**
 * @brief Load bank data
 * 
 * @param bk 
 * @return int Returns 0 if successful other return -1 
 */
int load_bank_data(Bank_t *bk);

/**
 * @brief Save bank data
 * 
 * @param bk 
 * @return int Returns 0 if successful other return -1
 */
int save_bank_data(Bank_t *bk);

/**
 * @brief Close bank object.
 * All pointers are freed and data.
 * @param bk 
 * @return int Returns 0 if successful other return -1
 */
int close_bank(Bank_t *bk);
int delete_bank_acount(Bank_t *bk, Account *acc);
int add_bank_acount(Bank_t *bk, const Account *acc);

Account* create_account(const char*, const char*, const char*,
 const char*, const char*);

Account* account_login(Bank_t *bk);
Account* account_update(Bank_t *bk);
void print_acount_transactions(Account *acnt);
double get_account_balance(Account *acnt);
int add_fund(Account *acnt, double fund);
int withdraw_fund(Account *acnt, double fund);
int transfer_fund(Account *from, Account *to, double fund);

#endif
