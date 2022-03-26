#ifndef _MY_BANK_H
#define _MY_BANK_H
#include<stddef.h>
#include<time.h>
#include "xvector.h"

#define BANKLEN         16
#define BANK_NAMELEN    32

// --------------------------
// Variant
// --------------------------
typedef enum BankEvent_ BankEvent_t;
typedef struct Transaction_ Transaction_t;
typedef struct UserInfo_ UserInfo_t;
typedef struct Account_ Account_t;

// ---------------------------
// Bank Object and operations
// ---------------------------
typedef struct Bank_ Bank_t;

Bank_t* load_bank_data();
void save_bank_data(const Bank_t*);

void add_bank_account(Bank_t*, const Account_t*);
void close_bank_account(Bank_t*, Account_t *);

void user_login(Bank_t *bank, const Account_t *account, const char *);

void make_withdraw(Bank_t*, Account_t*, double);
void make_deposit(Bank_t*, Account_t*, double);
void make_transfer(Bank_t*, const Account_t*, double, Account_t*);

void check_account_detail(Bank_t*, const Account_t*);
void show_bank_report(const Bank_t *bank);

double check_account_balance(const Account_t *account);
Transaction_t* get_account_transactions(const Account_t *account);
UserInfo_t* get_account_user_info(const Account_t *account);


#endif
