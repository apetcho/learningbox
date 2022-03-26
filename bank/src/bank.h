#ifndef _MY_BANK_H
#define _MY_BANK_H
#include<time.h>

#define BANKLEN         16
#define BANK_NAMELEN    32

typedef enum BankEvent_{
    OP_SUCCESS = 0,
    OP_CREATE_ACCOUNT,
    OP_CLOSE_ACCOUNT,
    OP_VALIDATE_ACCOUNT,
    OP_WITHDRAW,
    OP_CONSULT,
    OP_DEPOSIT,
    OP_TRANSFER,
    OP_FAIL = 100,
} BankEvent_t;

void bank_event_handler(int );
void bank_exception(BankEvent_t);

typedef struct Transaction_ Transaction_t;
struct Transaction_{
    BankEvent_t type;
    time_t when;
    char* (*to_string)(const Transaction_t *self);
};

Transaction_t *create_transaction(BankEvent_t event);
void delete_transaction(Transaction_t *self);
void print_transaction(const Transaction_t *self);

typedef struct TransactionList_ TransactionList_t;
TransactionList_t *create_transaction_list();
void delete_transaction_list(TransactionList_t *self);
void print_transaction_list(const TransactionList_t *self);


// ----------
// User Info
// ----------
typedef struct UserInfo_ UserInfo_t;
UserInfo_t* create_user();
void delete_user(UserInfo_t *user);

// -------------
// Account Info
// -------------
typedef struct Account_ Account_t;
Account_t *create_account();
void delete_account(Account_t *);

// -------------
// Account List
// -------------
typedef struct AccountList_ AccountList_t;

// ---------------------------
// Bank Object and operations
// ---------------------------
typedef struct Bank_ Bank_t;

Bank_t* load_bank_data();
void save_bank_data(const Bank_t*);
void set_new_account(Bank_t*, const Account_t*);
void close_account(Bank_t*, Account_t *);
void user_login(Bank_t *bank, const Account_t *account, const char *);
double make_withdraw(Bank_t*, const Account_t*, double);
double make_deposit(Bank_t*, const Account_t*, double);
void make_transfer(Bank_t*, const Account_t*, double, Account_t*);
void check_account_detail(Bank_t*, const Account_t*);
void show_bank_report(const Bank_t *bank);
#endif
