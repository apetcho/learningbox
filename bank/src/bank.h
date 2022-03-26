#ifndef _MY_BANK_H
#define _MY_BANK_H
#include<time.h>

// --------------------------
// Types Object 
// --------------------------
typedef enum BankEvent_ BankEvent;
typedef struct Transaction_ Transaction;
typedef struct UserInfo_ UserInfo;
typedef struct Account_ Account;
typedef struct Bank_ Bank;

// ---------------------------
// Bank Object and operations
// ---------------------------
Bank* load_bank_data();
void save_bank_data(const Bank*);
const Account* get_all_accounts(const Bank *bank);
void print_all_accounts(const Bank *bank);

void add_bank_account(Bank*, const Account*);
void close_bank_account(Bank*, Account *);

void user_login(Bank *bank, const Account *account, const char *);

void make_withdraw(Bank*, Account*, double);
void make_deposit(Bank*, Account*, double);
void make_transfer(Bank*, const Account*, double, Account*);

void check_account_detail(Bank*, const Account*);
void print_bank_report(const Bank *bank);

double check_account_balance(const Account *account);
Transaction* get_account_transactions(const Account *account);
UserInfo* get_account_user_info(const Account *account);


#endif
