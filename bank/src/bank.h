#ifndef _MY_BANK_APP_H
#define _MY_BANK_APP_H

#include "xvector.h"
#define BANK_STRLEN 40

typedef struct Account {
    char *firstname;
    char *lastname;
    char *email;
    char *phone;
    char *accountNo;
    char *password;
    double balance;
    char *filename;
    XVector_t *history;
} Account;

typedef Account account;

MAKE_CUSTOM_XVECTOR(account)

typedef struct Bank_t {
    XVector_t accountlist;
} Bank_t;

typedef enum BankEnum_t{
    BK_ERR_INSUFICIENT_FUND=-3,
    BK_ERR_LOGIN=-2,
    BK_UNKNOWN=-1,
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
}BankEnum_t;

Bank_t* open_bank();
void close_banck(Bank_t *bank);

Account create_account();
BankEnum_t account_login(Account *account);
BankEnum_t account_update(Account *account);

BankEnum_t load_acount(Account *account);
void save_account(Account *account);
double get_account_balance();
void add_fund(Account *account, double fund);
BankEnum_t withdraw_fund(Account *account, double fund);
BankEnum_t transfer_fund(Account *from, Account *to, double fund);

#endif
