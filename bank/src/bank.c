#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

#include "bank.h"

static const int DEFAULT_CAPACITY = 10;
static const double GROWTH_RATE = 1.5;
static const char* CUSTOMER_FILE = "BankCustomers.txt";

// fname-lname-phone-id.txt
#define TRANS_FORMAT    "%s-%s-%s-%d.txt"

// ---------------
//  Transaction
// ---------------
//! @todo
typedef struct Transaction_ Transaction_t;
Transaction_t *create_transaction(BankEvent_t event){}
void delete_transaction(Transaction_t *self){}
void print_transaction(const Transaction_t *self){}
static char* transaction_string(const Transaction_t *self){}

// --------------------
//   Transaction List
// --------------------
//! @todo
typedef struct TransactionList_ TransactionList_t;
struct TransactionList_{
    int size;
    int capacity;
    Transaction_t *list;
    void (*print)(const TransactionList_t *list);
};
TransactionList_t *create_transaction_list(){}
void delete_transaction_list(TransactionList_t *slist){}
void print_transaction_list(const TransactionList_t *list){}
static void add_transaction(
    TransactionList_t *list, const Transaction_t *trans){}
static void discard_transaction(TransactionList_t *list, Transaction_t *trans){}

// ------------
// User Info
// -----------
struct UserInfo_{
    char *fname;
    char *lname;
    char *email;
    char *phone;
    char* (*to_string)(const UserInfo_t *user);
};

//! @todo
static char* user_string(const UserInfo_t *user){}
UserInfo_t* create_user(){}
void delete_user(UserInfo_t* info){}

// --------------
//  Account Info
// --------------
struct Account_{
    UserInfo_t *user;
    char *password;
    double balance;
    int id;
    TransactionList_t *transactions;
    char* (*to_string)(const Account_t *self);
    void (*add_transaction)(Account_t *self, Transaction_t *transaction);
};

static void _set_password(Account_t *self, const char *password){}
static char* account_string(const Account_t *self){}
Account_t *create_account();
void delete_account(Account_t *);

// --------------
//  Account List
// --------------
typedef struct AccountList_ AccountList_t;
struct AccountList_{
    int size;
    int capacity;
    Account_t *list;
    void (*print)(const Account_t*);
};

static void add_account(){}
static AccountList_t* create_account_list();
void destroy_account_list(AccountList_t *);

// -------------
//  Bank Object
// -------------
// customerfile
// for each customer: transactionfile
typedef struct Bank_ Bank_t;
void load_bank_data(Bank_t *bank){}
void save_bank_data(const Bank_t *bank){}
void set_new_account(Bank_t *bank, const Account_t *account){}
void close_account(Bank_t *bank, Account_t *account){}
void user_login(Bank_t *bank, const Account_t *account){}
double make_withdraw(Bank_t *bank, const Account_t *account, double amnt){}
double make_deposit(Bank_t *bank, const Account_t *account, double amnt){}
void make_transfer(
    Bank_t *bank, const Account_t *sendAcc, double amnt, Account_t *recvAcc){}
void check_account_detail(Bank_t *bank, const Account_t *account){}
void show_bank_report(const Bank_t *bank){}
